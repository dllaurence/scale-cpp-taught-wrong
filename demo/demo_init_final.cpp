#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include "openssl/Crypto.hpp"


// Ensure the tests are called
openssl::Init init;
