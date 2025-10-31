/**
 * Create a program that allocates an array of integers (as above), frees
 * them, and then tries to print the value of one of the elements of
 * the array. Does the program run? What happens when you use
 * valgrind on it?
 * 
 * Answer:
 * - No valgrind support on macos
 * - Indicates heap-use-after-free at address 0x...5b08
 */


#include <stdio.h>
#include <stdlib.h>

int main()
{
    int * data = (int*) malloc (100 * sizeof(int)); // data[100]
    for(int i=0; i < 100; i++)
    {
        data[i] = 0;
    }
    printf("all data initialized to 0.\n");
    free(data);
    printf("Freed heap memory\n");
    data[50] = 0; // Illegal
    return 0;
}

/**********
 * OUTPUT - Q6
 **********
 *
 * ./q6
all data initialized to 0.
Freed heap memory
=================================================================
==39431==ERROR: AddressSanitizer: heap-use-after-free on address 0x000107215b08 at pc 0x0001002b7c20 bp 0x00016fb4ace0 sp 0x00016fb4acd8
WRITE of size 4 at 0x000107215b08 thread T0
    #0 0x1002b7c1c in main q6.c:26
    #1 0x187cfdd50 in start+0x1c0c (dyld:arm64e+0x3d50)

0x000107215b08 is located 200 bytes inside of 400-byte region [0x000107215a40,0x000107215bd0)
freed by thread T0 here:
    #0 0x10077b260 in wrap_free+0x98 (libclang_rt.asan_osx_dynamic.dylib:arm64e+0x53260)
    #1 0x1002b7ae0 in main q6.c:24
    #2 0x187cfdd50 in start+0x1c0c (dyld:arm64e+0x3d50)

previously allocated by thread T0 here:
    #0 0x10077b124 in wrap_malloc+0x94 (libclang_rt.asan_osx_dynamic.dylib:arm64e+0x53124)
    #1 0x1002b78d0 in main q6.c:18
    #2 0x187cfdd50 in start+0x1c0c (dyld:arm64e+0x3d50)

SUMMARY: AddressSanitizer: heap-use-after-free q6.c:26 in main
Shadow bytes around the buggy address:
  0x000107215880: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x000107215900: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x000107215980: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x000107215a00: fa fa fa fa fa fa fa fa fd fd fd fd fd fd fd fd
  0x000107215a80: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
=>0x000107215b00: fd[fd]fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x000107215b80: fd fd fd fd fd fd fd fd fd fd fa fa fa fa fa fa
  0x000107215c00: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x000107215c80: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x000107215d00: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x000107215d80: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
==39431==ABORTING
[1]    39431 abort      ./q6
 */