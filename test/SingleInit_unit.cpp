/*
  Copyright Dustin Laurence 2023. All rights reserved. Licensed under the
  FreeBSD license (BSD 2-clause)

  Part of the dl::ssl demo C++ interface to the OpenSSL cryptographic
  library.

  Run the SingleInit tests.

  Placed here to allow other external tests in other programs, as it can only
  run once per program.
*/


#include "doctest/doctest.h"

#include <stdexcept>

#include "dl/ssl/ScopedInit.hpp"
#include "dl/ssl/SingleInit.hpp"


// Using directive is OK in tests
using namespace dl::ssl;


TEST_CASE("testing dl::ssl::SingleInit: one object")
{
    auto singleInit = SingleInit::CreateOnce(); // Initialize OpenSSL

    CHECK(singleInit);

    CHECK_THROWS_AS(SingleInit::CreateOnce(), std::runtime_error);
    CHECK_THROWS_WITH(SingleInit::CreateOnce(),
                      "dl::ssl::SingleInit::CreateOnce called again.");

    /*
      1. unique_ptr ties us back to the surrounding scope
      2. Again, don't ever write "new XXX" -- and if you must, only write
      it once.
    */
}
