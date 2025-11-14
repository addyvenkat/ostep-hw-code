cmake_minimum_required(VERSION 3.10)
project(paging_tlb_hw_code)
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

add_executable(tlb tlb.c)
