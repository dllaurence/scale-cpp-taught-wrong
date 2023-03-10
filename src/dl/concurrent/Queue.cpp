/*
  Copyright Dustin Laurence 2023. All rights reserved. Licensed under the
  FreeBSD license (BSD 2-clause)

  Part of the dl::concurrent demo library.

  Provides an abstract interface to an underlying queue implementation. The
  base implementation wraps the Williams locking queue from C++ Concurrency In
  Action because it's so simple and transparent that it is very useful for
  baseline testing.
*/


#include "dl/concurrent/Queue.hpp"

#include <iostream> // Only for testing

#include "doctest/doctest.h"

#include "dl/concurrent/WilliamsLockingQueue6.2.hpp"


namespace dl::concurrent {


TEST_CASE_TEMPLATE("testing dl::concurrent::Queue",
                   Q,
                   WilliamsQueue<int>,
                   MaximQueue<int>)
{
    Q queue(100);

    auto pHandle = queue.GetProducerHandle();
    auto cHandle = queue.GetConsumerHandle();

    SUBCASE("Blocking I/O")
    {

        for (int i = 0; i < 10; ++i) {
            pHandle.BlockingPush(i);
        }

        for (int i = 0; i < 10; ++i) {
            int el = 0;
            cHandle.BlockingPop(el);
            CHECK(el == i);
        }
    }

    SUBCASE("Nonblocking I/O")
    {

        for (int i = 0; i < 10; ++i) {
            bool err = pHandle.TryPush(i);
            CHECK(!err);
        }

        for (int i = 0; i < 10; ++i) {
            int el = 0;
            bool err = cHandle.TryPop(el);
            CHECK(!err);
            CHECK(el == i);
        }
    }
}


} // namespace dl::concurrent
