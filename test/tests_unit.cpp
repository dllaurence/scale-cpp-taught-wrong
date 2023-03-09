/*
  Copyright Dustin Laurence 2023. All rights reserved. Licensed under the
  FreeBSD license (BSD 2-clause)

  Part of the dl::ssl demo C++ interface to the OpenSSL cryptographic
  library.

  Run the doctest test suite.
*/


#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include "dl/util/Deleter.hpp"


// Using directive is OK in tests
using namespace dl;


TEST_CASE("dummy calls")
{
    // Ensure the tests are called
    // TODO: Find out why this is necessary
    util::DeleterDummy();

    CHECK(true);
}


// Ensure the tests are called
// TODO: Find out why this is necessary
// c::CDeleter deleter;
// auto create_once = SingleInit::CreateOnce;
