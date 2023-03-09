# SCALE 2023 source
#
# Make an automatic library - will be static or dynamic based on user setting

add_library(sslwrapper)

# SOURCES
set(SSLWRAPPER_SOURCES
  ScopedInit.cpp
  SingleInit.cpp
  Unique.cpp
)
target_sources(sslwrapper
  PRIVATE
  ${SSLWRAPPER_SOURCES}
)

# INCLUDE DIRECTORIES
# Public, as users of our library will need them too
target_include_directories(sslwrapper
  PUBLIC
  "${CMAKE_SOURCE_DIR}/include"
  "${doctest_SOURCE_DIR}"
)

# LIBRARY DEPENDENCES
find_package(OpenSSL REQUIRED)
target_link_libraries(sslwrapper
  PUBLIC
  OpenSSL::Crypto
  #GSL
)

# FIXME: do we still need this?
# We need these header files in the wrapper projects, so copy the contents
# of include into the build directory.
#file(COPY ${CMAKE_SOURCE_DIR}/include DESTINATION .)
