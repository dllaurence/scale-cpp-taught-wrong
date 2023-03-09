/*
  Copyright Dustin Laurence 2023. All rights reserved. Licensed under the
  FreeBSD license (BSD 2-clause)

  Part of the dl::c demo library.

  Provides utilities for using unique_ptr with C strings.
*/


#include "dl/c/String.hpp"

#include <cstring>


#include "doctest/doctest.h"


namespace dl::c {


} // namespace dl::c


using namespace dl::c;


TEST_CASE("testing dl::c::String: CStrDup")
{

    CStringConst cString = "Here is a C string.";

    auto cStringCopy = CStrDup(cString);

    CHECK(cStringCopy);

    CHECK(0 == strcmp(cStringCopy.get(), cString));

    auto cStringCopy2 = CStrDup(cStringCopy);

    CHECK(0 == strcmp(cStringCopy2.get(), cStringCopy.get()));

    // The Sanitizers will verify that it does not leak.
}
