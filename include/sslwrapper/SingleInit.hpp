#pragma once

/*
  Copyright Dustin Laurence 2023. All rights reserved. Licensed under the
  FreeBSD license (BSD 2-clause)

  Part of the sslwrapper demo C++ interface to the OpenSSL cryptographic
  library.

  Provides an *owned* singleton to initialize and finalize the OpenSSL library

  OpenSSL code cribbed from https://wiki.openssl.org/index.php/Libcrypto_API
  on 2023/03/06.
*/


#include <memory>

namespace sslwrapper {

class SingleInit;
using UniqueSingleInit = std::unique_ptr<SingleInit>;

class SingleInit final
{
public:

    static UniqueSingleInit CreateOnce();

    ~SingleInit(); // non-virtual is safe for final classes

private:

    explicit SingleInit();
};


} // namespace sslwrapper
