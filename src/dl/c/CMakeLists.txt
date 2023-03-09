#  Copyright Dustin Laurence 2023. All rights reserved. Licensed under the
#  FreeBSD license (BSD 2-clause)
#
#  The dl::c demo library.


add_library(dl_c)

# SOURCES
set(SSL_SOURCES
  Malloc.cpp
  String.cpp
)
target_sources(dl_c
  PRIVATE
  ${SSL_SOURCES}
)

# INCLUDE DIRECTORIES
# Public, as users of our library will need them too
target_include_directories(dl_c
  PUBLIC
  "${CMAKE_SOURCE_DIR}/include"
  "${doctest_SOURCE_DIR}"
)

# LIBRARY DEPENDENCES
target_link_libraries(dl_c
  PUBLIC
  dl_util
)
