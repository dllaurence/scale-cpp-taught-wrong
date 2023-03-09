#pragma once

/*
  Copyright Dustin Laurence 2023. All rights reserved. Licensed under the
  FreeBSD license (BSD 2-clause)

  Part of the dl::util demo library.

  Provides a deleter for any object from any memory pool that has a free()
  function.

  Code based on
  https://stackoverflow.com/questions/19053351/how-do-i-use-a-custom-deleter-with-a-stdunique-ptr-member
*/


namespace dl::util {


// Turns an arbitrary free() function into a deleter.
template<auto Func>
struct Deleter
{
    template<typename T>
    constexpr void operator()(T* arg) const
    {
        Func(arg);
    }
};


void
DeleterDummy();


} // namespace dl::util
