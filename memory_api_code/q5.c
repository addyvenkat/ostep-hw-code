/**
 * Write a program that creates an array of integers called data of size
 * 100 using malloc; then, set data[100] to zero. What happens
 * when you run this program? What happens when you run this
 * program using valgrind? Is the program correct?
 * 
 * Answer:
 * - No valgrind in macos. Built with Address Sanitizer and -g
 * - Indicates heap-buffer overflow at address 0x...5bd0
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
    printf("data[100] initialized to 0.\n");
    data[100] = 0; // Illegal
    return 0;
}

/**********
 * OUTPUT - Q5
 **********
 * 
 * ./q5
data[100] initialized to 0.
=================================================================
==38485==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x000107915bd0 at pc 0x0001007c7c74 bp 0x00016f63ace0 sp 0x00016f63acd8
WRITE of size 4 at 0x000107915bd0 thread T0
    #0 0x1007c7c70 in main q5.c:23
    #1 0x187cfdd50 in start+0x1c0c (dyld:arm64e+0x3d50)

0x000107915bd0 is located 0 bytes after 400-byte region [0x000107915a40,0x000107915bd0)
allocated by thread T0 here:
    #0 0x100f93124 in wrap_malloc+0x94 (libclang_rt.asan_osx_dynamic.dylib:arm64e+0x53124)
    #1 0x1007c7938 in main q5.c:17
    #2 0x187cfdd50 in start+0x1c0c (dyld:arm64e+0x3d50)

SUMMARY: AddressSanitizer: heap-buffer-overflow q5.c:23 in main
Shadow bytes around the buggy address:
  0x000107915900: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x000107915980: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x000107915a00: fa fa fa fa fa fa fa fa 00 00 00 00 00 00 00 00
  0x000107915a80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x000107915b00: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
=>0x000107915b80: 00 00 00 00 00 00 00 00 00 00[fa]fa fa fa fa fa
  0x000107915c00: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x000107915c80: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x000107915d00: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x000107915d80: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x000107915e00: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
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
==38485==ABORTING
[1]    38485 abort      ./q5
 */