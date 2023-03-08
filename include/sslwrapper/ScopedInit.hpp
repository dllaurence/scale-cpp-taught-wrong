#pragma once

/*
  Copyright Dustin Laurence 2023. All rights reserved. Licensed under the
  FreeBSD license (BSD 2-clause)

  Provides a scoped object to initialize and finalize the OpenSSL library

  Part of the sslwrapper demo C++ interface to the OpenSSL cryptographic
  library.
*/


#include <memory>


namespace sslwrapper {


class ScopedInit;
using UniqueScopedInit = std::unique_ptr<ScopedInit>;


class ScopedInit final
{
public:

    explicit ScopedInit();

    ~ScopedInit(); // non-virtual is safe for final classes

private:
};


} // namespace sslwrapper
