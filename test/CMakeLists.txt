# SCALE 2023 demos
#
# Consider splitting into unit tests and so on

set(TESTS_UNIT_SOURCES
  tests_unit.cpp
  SingleInit_unit.cpp
)
add_executable(tests_unit ${TESTS_UNIT_SOURCES})
target_link_libraries(tests_unit sslwrapper doctest stdc++ m)
