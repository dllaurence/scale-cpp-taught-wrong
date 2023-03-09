#pragma once

/*
  Copyright Dustin Laurence 2023. All rights reserved. Licensed under the
  FreeBSD license (BSD 2-clause)

  Part of the dl::c demo library.

  Provides utilities for using unique_ptr with C strings.
*/


#include <cstring> // For C strdup & friends

#include "dl/c/Malloc.hpp"


namespace dl::c {


using CString = char*;
using CStringConst = const char*;
using UniqueCString = std::unique_ptr<CString, CDeleter>;


inline UniqueCArray<char>
CStrDup(const char* str)
{
    UniqueCArray<char> newStr(strdup(str));

    if (!newStr) {

        throw std::bad_alloc();
    }

    return newStr;
}


inline UniqueCArray<char>
CStrDup(const UniqueCArray<char>& str)
{
    return CStrDup(str.get());
}


} // namespace dl::c
