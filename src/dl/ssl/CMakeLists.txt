#  Copyright Dustin Laurence 2023. All rights reserved. Licensed under the
#  FreeBSD license (BSD 2-clause)
#
#  The dl::ssl demo library.


add_library(dl_ssl)

# SOURCES
set(SSL_SOURCES
  ScopedInit.cpp
  SingleInit.cpp
)
target_sources(dl_ssl
  PRIVATE
  ${SSL_SOURCES}
)

# INCLUDE DIRECTORIES
# Public, as users of our library will need them too
target_include_directories(dl_ssl
  PUBLIC
  "${CMAKE_SOURCE_DIR}/include"
  "${doctest_SOURCE_DIR}"
)

# LIBRARY DEPENDENCES
find_package(OpenSSL REQUIRED)
target_link_libraries(dl_ssl
  PUBLIC
  dl_util
  dl_c
  OpenSSL::Crypto
)
