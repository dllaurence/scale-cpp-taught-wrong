#pragma once

/*
  Copyright Dustin Laurence 2023. All rights reserved. Licensed under the
  FreeBSD license (BSD 2-clause)

  Part of the dl::concurrent demo library.

  Provides an abstract interface to an underlying queue implementation. The
  base implementation wraps the Williams locking queue from C++ Concurrency In
  Action because it's so simple and transparent that it is very useful for
  baseline testing.
*/


#include "atomic_queue/atomic_queue.h"
#include "dl/concurrent/WilliamsLockingQueue6.2.hpp"


namespace dl::concurrent {


// Main template--Works with the Williams locking queue
template<typename T, typename Q>
class Queue
{
public:

    class ProducerHandle
    {
        friend Queue; // Only the Queue may create handles

    private:

        Queue* mQueue;

    public:

        ~ProducerHandle() = default;

        void BlockingPush(T el) { mQueue->BlockingPush(el); };
        bool TryPush(T el) { return mQueue->TryPush(el); };

        // Standard operations
        ProducerHandle(const ProducerHandle&) = default;
        ProducerHandle(ProducerHandle&&) = default;
        ProducerHandle& operator=(const ProducerHandle&) = default;
        ProducerHandle& operator=(ProducerHandle&&) = default;

    private:

        // Only the queue may create handles
        explicit ProducerHandle(Queue<T, Q>& queue)
            : mQueue(&queue){};
    };

    class ConsumerHandle
    {
        friend Queue; // Only the Queue may create handles

    private:

        Queue* mQueue;

    public:

        ~ConsumerHandle() = default;

        void BlockingPop(T& el) { mQueue->BlockingPop(el); };
        bool TryPop(T& el) { return mQueue->TryPop(el); };

        // Standard operations
        ConsumerHandle(const ConsumerHandle&) = default;
        ConsumerHandle(ConsumerHandle&&) = default;
        ConsumerHandle& operator=(const ConsumerHandle&) = default;
        ConsumerHandle& operator=(ConsumerHandle&&) = default;

    private:

        // Only the queue may create handles
        explicit ConsumerHandle(Queue<T, Q>& queue)
            : mQueue(&queue){};
    };

private:

    Q mQueue;

public:

    explicit Queue(unsigned size)
        : mQueue(size){};
    ~Queue() = default;

    auto GetProducerHandle() { return ProducerHandle(*this); };
    auto GetConsumerHandle() { return ConsumerHandle(*this); };

    // Expose only the queue operations we want with the signature we want.
    // NEGATIVE LOGIC because we'll probably use error codes someday
    // For this queue, push never fails unless memory runs out
    // Consider if we want to pass by value like this
    void BlockingPush(T el) { mQueue.push(el); };
    bool TryPush(T el)
    {
        mQueue.push(el);
        return false;
    };

    void BlockingPop(T& el) { mQueue.wait_and_pop(el); };
    bool TryPop(T& el) { return !mQueue.try_pop(el); };

    // Standard operations
    Queue(const Queue&) = delete;
    Queue(Queue&&) = delete;
    Queue& operator=(const Queue&) = delete;
    Queue& operator=(Queue&&) = delete;
};

template<class T>
using WilliamsQueue = Queue<T, cppcia::threadsafe_queue<T>>;


// Specialize for AtomicQueueB2
template<class T>
class Queue<T, atomic_queue::AtomicQueueB2<T>>
{
public:

    class ProducerHandle
    {
        friend Queue; // Only the Queue may create handles

    private:

        Queue* mQueue;

    public:

        ~ProducerHandle() = default;

        void BlockingPush(T el) { mQueue->BlockingPush(el); };
        bool TryPush(T el) { return mQueue->TryPush(el); };

        // Standard operations
        ProducerHandle(const ProducerHandle&) = default;
        ProducerHandle(ProducerHandle&&) = default;
        ProducerHandle& operator=(const ProducerHandle&) = default;
        ProducerHandle& operator=(ProducerHandle&&) = default;

    private:

        // Only the queue may create handles
        explicit ProducerHandle(
            Queue<T, atomic_queue::AtomicQueueB2<T>>& queue)
            : mQueue(&queue){};
    };

    class ConsumerHandle
    {
        friend Queue; // Only the Queue may create handles

    private:

        Queue* mQueue;

    public:

        ~ConsumerHandle() = default;

        void BlockingPop(T& el) { mQueue->BlockingPop(el); };
        bool TryPop(T& el) { return mQueue->TryPop(el); };

        // Standard operations
        ConsumerHandle(const ConsumerHandle&) = default;
        ConsumerHandle(ConsumerHandle&&) = default;
        ConsumerHandle& operator=(const ConsumerHandle&) = default;
        ConsumerHandle& operator=(ConsumerHandle&&) = default;

    private:

        // Only the queue may create handles
        explicit ConsumerHandle(
            Queue<T, atomic_queue::AtomicQueueB2<T>>& queue)
            : mQueue(&queue){};
    };

private:

    atomic_queue::AtomicQueueB2<T> mQueue;

public:

    explicit Queue(unsigned size)
        : mQueue(size){};
    ~Queue() = default;

    auto GetProducerHandle() { return ProducerHandle(*this); };
    auto GetConsumerHandle() { return ConsumerHandle(*this); };

    // Expose only the queue operations we want with the signature we want.
    // Negative logic because we'll probably use error codes someday

    void BlockingPush(T el) { mQueue.push(el); };
    // Experiment: interface for a value-oriented queue
    // void BlockingPush(T&& el) { mQueue.push(std::forward<T>(el)); };
    // void BlockingPush(const T& el) { mQueue.push(el); };

    bool TryPush(T el) { return !mQueue.try_push(el); };
    // Experiment: interface for a value-oriented queue
    // bool TryPush(T&& el) { return !mQueue.try_push(std::forward<T>(el)); };
    // bool TryPush(const T& el) { return !mQueue.try_push(el); };

    void BlockingPop(T& el) { el = mQueue.pop(); };
    bool TryPop(T& el) { return !mQueue.try_pop(el); };

    // Standard operations
    Queue(const Queue&) = delete;
    Queue(Queue&&) = delete;
    Queue& operator=(const Queue&) = delete;
    Queue& operator=(Queue&&) = delete;
};

template<class T>
using MaximQueue = Queue<T, atomic_queue::AtomicQueueB2<T>>;


} // namespace dl::concurrent
