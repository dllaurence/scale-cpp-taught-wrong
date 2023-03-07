# SCALE 2023 demos
#
# Consider splitting into unit tests and so on

add_executable(demo_init_final demo_init_final.cpp)
target_link_libraries(demo_init_final openssl_wrapper doctest stdc++ m)
