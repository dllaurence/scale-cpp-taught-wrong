/*
 Copyright Dustin Laurence 2023. All rights reserved. Licensed under the
 FreeBSD license (BSD 2-clause)

 Part of the dl::ssl demo C++ interface to the OpenSSL cryptographic
 library.

 Provides a scoped object to initialize and finalize the OpenSSL library

 OpenSSL code cribbed from https://wiki.openssl.org/index.php/Libcrypto_API
 on 2023/03/06.
*/

#include "dl/ssl/ScopedInit.hpp"

#include <stdexcept>

#include <openssl/conf.h>
#include <openssl/err.h>
#include <openssl/evp.h>

#include "doctest/doctest.h"


namespace dl::ssl {


ScopedInit::ScopedInit()
{
    /* Load the human readable error strings for libcrypto */
    ERR_load_crypto_strings();

    /* Load all digest and cipher algorithms */
    OpenSSL_add_all_algorithms();

    /* Load config file, and other important initialisation

    "The OPENSSL_no_config() and OPENSSL_config() functions were deprecated in
    OpenSSL 1.1.0 by OPENSSL_init_crypto()."
    https://www.openssl.org/docs/man1.1.1/man3/OPENSSL_config.html

    "As of version 1.1.0 OpenSSL will automatically allocate all resources that
    it needs so no explicit initialisation is required. Similarly it will also
    automatically deinitialise as required."
    https://www.openssl.org/docs/man1.1.1/man3/OPENSSL_init_crypto.html
    */

    // OPENSSL_config(NULL);
    // OPENSSL_init_crypto
}


ScopedInit::~ScopedInit()
{
    /* Removes all digests and ciphers */
    EVP_cleanup();

    /* if you omit the next, a small leak may be left when you make use of
     * the BIO (low level API) for e.g. base64 transformations */
    CRYPTO_cleanup_all_ex_data();

    /* Remove error strings */
    ERR_free_strings();
}


TEST_CASE("testing dl::ssl::ScopedInit: stack object")
{
    ScopedInit scopedInit; // Initialize OpenSSL

    /* Why?

       1. Tied init/finalize to a scope.
       2. Avoided a static object and made the initialization and finalization
       predictable.

       Also, didn't use a using statement.
    */
}


TEST_CASE("testing dl::ssl::ScopedInit: heap object")
{
    auto scopedInit = new ScopedInit(); // Initialize OpenSSL

    CHECK(scopedInit != nullptr);

    delete scopedInit;
    scopedInit = nullptr;
    /*
      1. Not tied to a scope any more
      2. Back to our original problem
      3. Will leak if an exception is thrown.
      4. Just avoid "new XXX" almost completely.

    */
}


TEST_CASE("testing dl::ssl::ScopedInit: unique object")
{
    auto scopedInit =
        std::make_unique<dl::ssl::ScopedInit>(); // Initialize OpenSSL

    CHECK(scopedInit);

    /*
      1. unique_ptr ties us back to the surrounding scope
      2. Again, don't ever write "new XXX"
    */
}


} // namespace dl::ssl
