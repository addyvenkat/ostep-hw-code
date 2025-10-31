
/**
 * Now pass a funny value to free (e.g., a pointer in the middle of the
 * array you allocated above). What happens? Do you need tools to
 * find this type of problem?
 * 
 * Answer:
 * - With address sanitizer, there's a failure of attempting free on an address which was mot malloc-ed
 * 
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
    printf("Freeing a specific heap memory\n");
    free(&data[50]);
    return 0;
}

/**********
 * OUTPUT - Q7
 **********
 *
 * ./q7
all data initialized to 0.
Freeing a specific heap memory
=================================================================
==40097==ERROR: AddressSanitizer: attempting free on address which was not malloc()-ed: 0x000109615b08 in thread T0
    #0 0x102c43260 in wrap_free+0x98 (libclang_rt.asan_osx_dynamic.dylib:arm64e+0x53260)
    #1 0x10252bc28 in main q7.c:24
    #2 0x187cfdd50 in start+0x1c0c (dyld:arm64e+0x3d50)

0x000109615b08 is located 200 bytes inside of 400-byte region [0x000109615a40,0x000109615bd0)
allocated by thread T0 here:
    #0 0x102c43124 in wrap_malloc+0x94 (libclang_rt.asan_osx_dynamic.dylib:arm64e+0x53124)
    #1 0x10252b978 in main q7.c:17
    #2 0x187cfdd50 in start+0x1c0c (dyld:arm64e+0x3d50)

SUMMARY: AddressSanitizer: bad-free (libclang_rt.asan_osx_dynamic.dylib:arm64e+0x53260) in wrap_free+0x98
==40097==ABORTING
[1]    40097 abort      ./q7
 */