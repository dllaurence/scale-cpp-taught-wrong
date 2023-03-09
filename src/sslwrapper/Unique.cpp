/*
  Copyright Dustin Laurence 2023. All rights reserved. Licensed under the
  FreeBSD license (BSD 2-clause)

  Part of the sslwrapper demo C++ interface to the OpenSSL cryptographic
  library.

  Provides utilities for using unique_ptr with any object from any memory pool
  that has a free() function.

  Code based on
  https://stackoverflow.com/questions/19053351/how-do-i-use-a-custom-deleter-with-a-stdunique-ptr-member
*/


#include "sslwrapper/Unique.hpp"

#include <cstring>

//#include <stdexcept>
//
//#include <openssl/conf.h>
//#include <openssl/err.h>
//#include <openssl/evp.h>

#include "doctest/doctest.h"


namespace sslwrapper {


template<class T>
UniqueCObject<T>
CMalloc()
{
    T* ptr = static_cast<T*>(std::malloc(sizeof(T)));

    if (!ptr) {

        throw std::bad_alloc();
    }

    return UniqueCObject<T>(ptr);
}


TEST_CASE("testing sslwrapper::Unique: C object deletion")
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


template<class T>
UniqueCArray<T>
CMalloc(size_t elementCount)
{
    T* ptr = static_cast<T*>(std::malloc(sizeof(T) * elementCount));

    if (!ptr) {
        throw std::bad_alloc();
    }

    return UniqueCArray<T>(ptr);
}


TEST_CASE("testing sslwrapper::Unique: C array deletion")
{

    const char cString[] = "Here is a C string.";
    const size_t cStringSize = strlen(cString) + 1;

    auto cStringCopy = CMalloc<char>(cStringSize);

    CHECK(cStringCopy);

    strncpy(cStringCopy.get(), cString, cStringSize);

    CHECK(strlen(cStringCopy.get()) + 1 == cStringSize);

    // The Sanitizers will verify that it does not leak.
}


} // namespace sslwrapper
