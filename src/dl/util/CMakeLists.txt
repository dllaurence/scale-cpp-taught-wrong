#  Copyright Dustin Laurence 2023. All rights reserved. Licensed under the
#  FreeBSD license (BSD 2-clause)
#
#  The dl::util demo library.


# Make an automatic library - will be static or dynamic based on user setting

add_library(dl_util)

# SOURCES
set(SSL_SOURCES
  Deleter.cpp
)
target_sources(dl_util
  PRIVATE
  ${SSL_SOURCES}
)

# INCLUDE DIRECTORIES
# Public, as users of our library will need them too
target_include_directories(dl_util
  PUBLIC
  "${CMAKE_SOURCE_DIR}/include"
  "${doctest_SOURCE_DIR}"
)

# LIBRARY DEPENDENCES
#find_package(OpenSSL REQUIRED)
#target_link_libraries(dl_util
#  PUBLIC
#  OpenSSL::Crypto
#  #GSL
#)
