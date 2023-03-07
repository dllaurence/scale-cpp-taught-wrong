#pragma once

/*
 Copyright Dustin Laurence 2023. All rights reserved. Licensed under the
 FreeBSD license (BSD 2-clause)

 C++ interface to the OpenSSL cryptographic library.
*/


/*
  Private final helper class to initialize and finalize the OpenSSL library.
  Singleton usage must be enforced.

  TODO: enforce singleton nature
*/

#include <memory>

namespace openssl {


class Init final
{
public:

    explicit Init();

    ~Init(); // non-virtual is safe for final classes

private:
};

using UniqueInit = std::unique_ptr<Init>;


} // namespace openssl
