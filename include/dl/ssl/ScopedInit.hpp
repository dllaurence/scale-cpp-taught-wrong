#pragma once

/*
  Copyright Dustin Laurence 2023. All rights reserved. Licensed under the
  FreeBSD license (BSD 2-clause)

  Provides a scoped object to initialize and finalize the OpenSSL library

  Part of the dl::ssl demo C++ interface to the OpenSSL cryptographic
  library.
*/


#include <memory>


namespace dl::ssl {


class ScopedInit;
using UniqueScopedInit = std::unique_ptr<ScopedInit>;


class ScopedInit final
{
public:

    explicit ScopedInit(); // Should be private!

    ~ScopedInit(); // non-virtual is safe for final classes

    static UniqueScopedInit New()
    {
        return std::make_unique<dl::ssl::ScopedInit>();
    }

private:
};


} // namespace dl::ssl
