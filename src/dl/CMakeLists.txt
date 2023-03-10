#  Copyright Dustin Laurence 2023. All rights reserved. Licensed under the
#  FreeBSD license (BSD 2-clause)
#
#  The dl demo library.

# For building as separate libraries
# add_subdirectory(c)
# add_subdirectory(ssl)
# add_subdirectory(util)


add_library(dl)

# SOURCES
set(DL_SOURCES

  util/Deleter.cpp

  c/Malloc.cpp
  c/String.cpp

  concurrent/Queue.cpp

  ssl/ScopedInit.cpp
  ssl/SingleInit.cpp
)
target_sources(dl
  PRIVATE
  ${DL_SOURCES}
)

# INCLUDE DIRECTORIES
# Public, as users of our library will need them too
target_include_directories(dl
  PUBLIC
  "${CMAKE_SOURCE_DIR}/include"
  "${doctest_SOURCE_DIR}"
)

# LIBRARY DEPENDENCES
find_package(OpenSSL REQUIRED)
target_link_libraries(dl
  PUBLIC
  OpenSSL::Crypto
)
