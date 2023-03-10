#pragma once

/*
  Thread-safe Locking Queue by Anthony Williams.

  Straight from the code in the book C++ Concurrency In Action by Anthony
  Williams. Used as a simple, completely documented locking queue to use for
  comparison tests.

  shared_ptr method variants removed.

  Downloaded from:
  https://github.com/anthonywilliams/ccia_code_samples/blob/main/listings/listing_6.2.cpp
  Licensed under the Boost Software License.
 */


#include <condition_variable>
#include <mutex>
#include <queue>
//#include <memory>


namespace cppcia {


template<typename T>
class threadsafe_queue
{
private:

    mutable std::mutex mut;
    std::queue<T> data_queue;
    std::condition_variable data_cond;

public:

    threadsafe_queue(unsigned) {}

    void push(T new_value)
    {
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(std::move(new_value));
        data_cond.notify_one();
    }

    void wait_and_pop(T& value)
    {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, [this] { return !data_queue.empty(); });
        value = std::move(data_queue.front());
        data_queue.pop();
    }

    bool try_pop(T& value)
    {
        std::lock_guard<std::mutex> lk(mut);
        if (data_queue.empty())
            return false;
        value = std::move(data_queue.front());
        data_queue.pop();

        return true; // BUGFIX: was missing return value
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> lk(mut);
        return data_queue.empty();
    }
};


} // namespace cppia
