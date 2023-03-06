# OpenSSL wrapper library
#

# Make an automatic library - will be static or dynamic based on user setting

add_library(openssl_wrapper)

# SOURCES
target_sources(openssl_wrapper
  PRIVATE
  Crypto.cpp
)

# INCLUDE DIRECTORIES
# Public, as users of our library will need them too
target_include_directories(openssl_wrapper
  PUBLIC
  "${CMAKE_SOURCE_DIR}/include"
)

# LIBRARY DEPENDENCES
find_package(OpenSSL REQUIRED)
target_link_libraries(openssl_wrapper
  PUBLIC
  OpenSSL::Crypto
  #GSL
)

# FIXME: do we still need this?
# We need these header files in the wrapper projects, so copy the contents
# of include into the build directory.
#file(COPY ${CMAKE_SOURCE_DIR}/include DESTINATION .)
