#pragma once

/*
  Copyright Dustin Laurence 2023. All rights reserved. Licensed under the
  FreeBSD license (BSD 2-clause)

  Part of the dl::c demo library.

  Provides utilities for using unique_ptr with malloc/free.
*/


#include <cstdlib> // For C malloc/free

#include <memory>

#include "dl/util/Deleter.hpp"


namespace dl::c {


using CDeleter = util::Deleter<std::free>;
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


} // namespace dl::c
