/*
  Copyright Dustin Laurence 2023. All rights reserved. Licensed under the
  FreeBSD license (BSD 2-clause)

  Part of the dl::ssl demo C++ interface to the OpenSSL cryptographic
  library.

  Provides utilities for using unique_ptr with any object from any memory pool
  that has a free() function.

  Code based on
  https://stackoverflow.com/questions/19053351/how-do-i-use-a-custom-deleter-with-a-stdunique-ptr-member
*/


#include "dl/ssl/Unique.hpp"

#include <cstring>

//#include <stdexcept>
//
//#include <openssl/conf.h>
//#include <openssl/err.h>
//#include <openssl/evp.h>

#include "doctest/doctest.h"


namespace dl::ssl {


TEST_CASE("testing dl::ssl::Unique: C object deletion")
{

    struct CObj
    {
        double d;
        long l;
        char c;
    };

    CObj cObj = { 3.14, 1024, 'a' };

    auto cObjCopy = CMalloc<CObj>();

    CHECK(cObjCopy);

    cObjCopy->d = cObj.d;
    cObjCopy->l = cObj.l;
    cObjCopy->c = cObj.c;

    CHECK(cObjCopy->d == cObj.d);
    CHECK(cObjCopy->l == cObj.l);
    CHECK(cObjCopy->c == cObj.c);

    // The Sanitizers will verify that it does not leak.
}


TEST_CASE("testing dl::ssl::Unique: C array deletion")
{

    const char cString[] = "Here is a C string.";
    const size_t cStringSize = strlen(cString) + 1;

    auto cStringCopy = CMalloc<char>(cStringSize);

    CHECK(cStringCopy);

    strncpy(cStringCopy.get(), cString, cStringSize);

    CHECK(strlen(cStringCopy.get()) + 1 == cStringSize);

    CHECK(0 == strcmp(cStringCopy.get(), cString));

    // The Sanitizers will verify that it does not leak.
}


TEST_CASE("testing dl::ssl::Unique: CStrDup")
{

    const char cString[] = "Here is a C string.";

    auto cStringCopy = CStrDup(cString);

    CHECK(cStringCopy);

    CHECK(0 == strcmp(cStringCopy.get(), cString));

    auto cStringCopy2 = CStrDup(cStringCopy);

    CHECK(0 == strcmp(cStringCopy2.get(), cStringCopy.get()));

    // The Sanitizers will verify that it does not leak.
}


} // namespace dl::ssl
