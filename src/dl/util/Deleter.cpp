/*
  Copyright Dustin Laurence 2023. All rights reserved. Licensed under the
  FreeBSD license (BSD 2-clause)

  Part of the dl::util demo library.

  Provides a deleter for any object from any memory pool that has a free()
  function.

  Code based on
  https://stackoverflow.com/questions/19053351/how-do-i-use-a-custom-deleter-with-a-stdunique-ptr-member
*/


#include "dl/util/Deleter.hpp"

#include <cstdlib>

#include <memory>

#include "doctest/doctest.h"


namespace dl::util {


TEST_CASE("testing dl::util::Deleter: Basic deletion")
{
    const std::size_t size = 100;

    std::unique_ptr<void, Deleter<std::free>> mem(std::malloc(size));

    CHECK(mem);

    // The Sanitizers will verify that it does not leak.
}


} // namespace dl::util
