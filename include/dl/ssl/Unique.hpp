#pragma once

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


#include <cstdlib> // For C free()
#include <cstring> // For C strdup & friends

#include <memory>

#include <openssl/bn.h> // For OPENSSL_free


namespace dl::ssl {


// Turns an arbitrary free() function into a deleter for unique_ptr.
template<auto Func>
struct Deleter
{
    template<typename T>
    constexpr void operator()(T* arg) const
    {
        Func(arg);
    }
};


/*
  For use with libc's malloc and free
 */


using CDeleter = Deleter<free>;
template<class T>
using UniqueCObject = std::unique_ptr<T, CDeleter>;
template<class T>
using UniqueCArray = std::unique_ptr<T[], CDeleter>;


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


} // namespace dl::ssl
