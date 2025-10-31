cmake_minimum_required(VERSION 3.24)
project(memory_api_hw_code)
add_compile_options(
    -g
    -O0
    -fno-omit-frame-pointer
    -fsanitize=address,undefined
    -fsanitize-address-use-after-scope
)
add_link_options(
    -fsanitize=address,undefined
)

add_executable(null null.c)
add_executable(q4 q4.c)
add_executable(q5 q5.c)
add_executable(q6 q6.c)
add_executable(q7 q7.c)
add_executable(q8 q8.c)
