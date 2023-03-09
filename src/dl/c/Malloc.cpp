/*
  Copyright Dustin Laurence 2023. All rights reserved. Licensed under the
  FreeBSD license (BSD 2-clause)

  Part of the dl::c demo library.

  Provides utilities for using unique_ptr with malloc/free.
*/


#include "dl/c/Malloc.hpp"

#include <cstring>

#include "doctest/doctest.h"


namespace dl::c {


TEST_CASE("testing dl::c::Malloc: C object deletion")
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


TEST_CASE("testing dl::c::Malloc: C array deletion")
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


} // namespace dl::c
