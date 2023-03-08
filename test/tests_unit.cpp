/*
  Copyright Dustin Laurence 2023. All rights reserved. Licensed under the
  FreeBSD license (BSD 2-clause)

  Part of the sslwrapper demo C++ interface to the OpenSSL cryptographic
  library.

  Run the doctest test suite.
*/


#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include "sslwrapper/ScopedInit.hpp"
#include "sslwrapper/SingleInit.hpp"


// Using directive is OK in tests
using namespace sslwrapper;


// Ensure the tests are called
// auto create_once = SingleInit::CreateOnce;
