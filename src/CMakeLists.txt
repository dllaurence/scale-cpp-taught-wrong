# SCALE 2023 source
#
# Make an automatic library - will be static or dynamic based on user setting

add_library(openssl_wrapper)

# SOURCES
set(OPENSSL_WRAPPER_SOURCES
  Crypto.cpp
)
target_sources(openssl_wrapper
  PRIVATE
  ${OPENSSL_WRAPPER_SOURCES}
)

# INCLUDE DIRECTORIES
# Public, as users of our library will need them too
target_include_directories(openssl_wrapper
  PUBLIC
  "${CMAKE_SOURCE_DIR}/include"
  "${doctest_SOURCE_DIR}"
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

# Add local tidy files
list(TRANSFORM OPENSSL_WRAPPER_SOURCES PREPEND "src/")
#set(CLANG_TIDY_SOURCES "${CLANG_TIDY_SOURCES} ${OPENSSL_WRAPPER_SOURCES}" PARENT_SCOPE)
set(TEST_SOURCES "${TEST_SOURCES} ${OPENSSL_WRAPPER_SOURCES}" PARENT_SCOPE)
