/*
 Copyright Dustin Laurence 2023. All rights reserved. Licensed under the
 FreeBSD license (BSD 2-clause)

 C++ interface to the OpenSSL cryptographic library.
*/

#include "openssl/Crypto.hpp"

#include <openssl/conf.h>
#include <openssl/err.h>
#include <openssl/evp.h>


/*
  Private final helper class to initialize and finalize the OpenSSL library.
  Singleton usage must be enforced.

  Code cribbed from https://wiki.openssl.org/index.php/Libcrypto_API
  on 2023/03/06.
*/

namespace openssl {


Init::Init()
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
};


Init::~Init()
{
    /* Removes all digests and ciphers */
    EVP_cleanup();

    /* if you omit the next, a small leak may be left when you make use of
     * the BIO (low level API) for e.g. base64 transformations */
    CRYPTO_cleanup_all_ex_data();

    /* Remove error strings */
    ERR_free_strings();
};


} // namespace OpenSSL
