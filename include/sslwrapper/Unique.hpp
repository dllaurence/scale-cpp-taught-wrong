#pragma once

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


#include <cstdlib> // For C free()

#include <memory>

#include <openssl/bn.h> // For OPENSSL_free


namespace sslwrapper {


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
CMalloc();

template<class T>
UniqueCArray<T>
CMalloc(size_t elementCount);


} // namespace sslwrapper
