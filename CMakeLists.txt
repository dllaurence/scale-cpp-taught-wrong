# Copyright Dustin Laurence 2023. All rights reserved. Licensed under the
# FreeBSD license (BSD 2-clause)
#
# Useful advice: https://cliutils.gitlab.io/modern-cmake/


cmake_minimum_required(VERSION 3.22)

project(
  CPPTaughtWrong
  VERSION 0.1
  DESCRIPTION "Source for SCALE 2023 talk: C++ Things You Were Taught To Do Wrong"
  LANGUAGES CXX)

######################################################################
# Misc options
######################################################################

### Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

message(STATUS "Building with ${CMAKE_CXX_COMPILER_ID} ${CMAKE_C_COMPILER_VERSION} on ${CMAKE_SYSTEM_NAME}")

# For tooling (e.g. clang-tidy)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

######################################################################
# C++ flags and build types
#
# Useful information on creating build types:
# https://stackoverflow.com/questions/11437692/how-to-add-a-custom-build-type-to-cmake-targeting-make
#
# For GCC 12 and higher, set _THREAD_SANITIZER to 3. See
# https://fedoraproject.org/wiki/Changes/Add_FORTIFY_SOURCE%3D3_to_distribution_build_flags
#
# Sanitizer recommendations here:
# https://developers.redhat.com/blog/2021/05/05/memory-error-checking-in-c-and-c-comparing-sanitizers-and-valgrind
# N.B.: optimization makes the santitizers more likely to find errors--leave -O3 in
# Everything gets -ggdb so we get file and line numbers in error messages.
#
# It's not clear if the thread sanitizer is compatible with the other sanitizers, and in
# any case the greater the performance penalty the more it seems likely
# to change thread contention. Thus we essentially do a release build
# plus the thread sanitizer and location information only.
#
# More info:
# https://github.com/google/sanitizers/wiki/ThreadSanitizerCppManual
######################################################################

# Language standards

set(CMAKE_CXX_STANDARD 17)

# GLOBAL (settings for all objects)
set(FLAGS_ALL "$ENV{CXXFLAGS} -Wall -Wextra -Werror -Wundef -Wp,-D_FORTIFY_SOURCE=2 -fPIC -pthread")

# RELEASE
set(CMAKE_CXX_FLAGS_RELEASE "${FLAGS_ALL} -DNDEBUG -O3")

set(FLAGS_DEBUG_INFO "-fno-omit-frame-pointer -ggdb")
set(LINKER_FLAGS_DEBUG_INFO "-fno-omit-frame-pointer")

# DEBUG
set(CMAKE_CXX_FLAGS_DEBUG "${FLAGS_ALL} ${FLAGS_DEBUG_INFO} -Og")

# ALL SANITIZER TARGETS
set(FLAGS_SANITIZE "${FLAGS_DEBUG_INFO} -O3")
#set(LINKER_FLAGS_SANITIZE "${LINKER_FLAGS_DEBUG_INFO} -v")

# THREAD SANITIZER
set(CMAKE_CXX_FLAGS_THREADSAN "${FLAGS_ALL} ${FLAGS_SANITIZE} -fsanitize=thread")
#set(CMAKE_LINKER_FLAGS_THREADSAN "${LINKER_FLAGS_SANITIZE} -fsanitize=thread")

# ALL OTHER SANITIZERS
# Note: FORTIFY_SOURCE shut off because it interferes with the address
# sanitizer.
set(CMAKE_CXX_FLAGS_SANITIZE "${FLAGS_ALL} ${FLAGS_SANITIZE} -fsanitize=address -Wp,-U_FORTIFY_SOURCE -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment")
#set(CMAKE_LINKER_FLAGS_SANITIZE "${LINKER_FLAGS_SANITIZE} -fsanitize=address -sanitize=undefined -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow")

######################################################################
# Globally used libraries
######################################################################

# DOCTEST
include(FetchContent)
FetchContent_Declare(doctest
    URL https://github.com/doctest/doctest/archive/refs/tags/v2.4.10.tar.gz
)
FetchContent_MakeAvailable(doctest)

# ATOMIC_QUEUE
# include atomic_queue
FetchContent_Declare(atomic_queue
    #URL https://github.com/max0x7ba/atomic_queue/archive/refs/tags/v1.0.tar.gz
    URL https://github.com/max0x7ba/atomic_queue/archive/refs/tags/v1.1.tar.gz
)
FetchContent_MakeAvailable(atomic_queue)

######################################################################
# SUBDIRECTORIES
######################################################################

add_subdirectory(src/dl)
add_subdirectory(test)
