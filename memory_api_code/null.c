/**
 * Q1: First, write a simple program called null.cthat creates a pointer
 * to an integer, sets it to NULL, and then tries to dereference it. Com-
 * pile this into an executable called null. What happens when you
 * run this program?
 * 
 * Answer:
 * - Segmentation fault due dereferencing a null pointer
 * 
 * Q2: Next, compile this program with symbol information included (with
 * the -g flag). Doing so let’s put more information into the exe-
 * cutable, enabling the debugger to access more useful information
 * about variable names and the like. Run the program under the de-
 * bugger by typing gdb nulland then, once gdbis running, typing
 * run. What does gdb show you?
 * 
 * Answer:
 * - EXC_BAD_ACCESS exception
 * 
 * Q3: Finally, use the valgrindtool on this program. We’ll use memcheck
 * that is a part of valgrind to analyze what happens. Run this by
 * typing in the following: valgrind --leak-check=yes null.
 * What happens when you run this? Can you interpret the output
 * from the tool?
 * 
 * Answer:
 * - No valgrind in macos. Built with Address Sanitizer and -g
 * - image lookup at the program counter
 */

#include <stdlib.h>
#include <stdio.h>

int main()
{
    int* x = NULL;
    printf("Dereferencing x\n");
    printf("%d", *x);
    return 0;
}

/**********
 * OUTPUT - Q1
 **********
 * Dereferencing x
 * [1]    29796 segmentation fault  ./null
 */


/**********
 * OUTPUT - Q2
 **********
 * (lldb) target create "null"
 * Current executable set to '/Users/addyvenkat/Documents/JobPrep/OS-TEP/ostep-hw-code/memory_api_code/build/null' (arm64).
 * (lldb) r
 * Process 29961 launched: '/Users/addyvenkat/Documents/JobPrep/OS-TEP/ostep-hw-code/memory_api_code/build/null' (arm64)
 * Dereferencing x
 * Process 29961 stopped
 * * thread #1, queue = 'com.apple.main-thread', stop reason = EXC_BAD_ACCESS (code=1, address=0x0)
 *     frame #0: 0x0000000100003f5c null`main + 44
 * null`main:
 * ->  0x100003f5c <+44>: ldr    w9, [x8]
 *     0x100003f60 <+48>: mov    x8, x9
 *     0x100003f64 <+52>: mov    x9, sp
 *     0x100003f68 <+56>: str    x8, [x9]
 * Target 0: (null) stopped.
 * (lldb)
 */


/**********
 * OUTPUT - Q3
 **********
Dereferencing x
AddressSanitizer:DEADLYSIGNAL
=================================================================
==31311==ERROR: AddressSanitizer: SEGV on unknown address 0x000000000000 (pc 0x000100fafcc0 bp 0x00016ee52db0 sp 0x00016ee52d70 T0)
==31311==The signal is caused by a READ memory access.
==31311==Hint: address points to the zero page.
    #0 0x100fafcc0 in main+0x90 (null:arm64+0x100003cc0)
    #1 0x187cfdd50 in start+0x1c0c (dyld:arm64e+0x3d50)

==31311==Register values:
 x[0] = 0x0000000000000010   x[1] = 0x0000000000000000   x[2] = 0x00000000000120a8   x[3] = 0x000000000000000f
 x[4] = 0x0000000108a02980   x[5] = 0x0000000000000000   x[6] = 0x000000016e658000   x[7] = 0x0000000000000001
 x[8] = 0x0000000000000000   x[9] = 0x0000000000000000  x[10] = 0x0000000000000002  x[11] = 0x0000010000000000
x[12] = 0x00000000fffffffd  x[13] = 0x0000000000000000  x[14] = 0x0000000000000000  x[15] = 0x0000000000000000
x[16] = 0x000000018807a608  x[17] = 0x00000001f609ded8  x[18] = 0x0000000000000000  x[19] = 0x00000001f47bc060
x[20] = 0x00000001f4a669c8  x[21] = 0x00000001f47bcdd0  x[22] = 0xfffffffffffffff0  x[23] = 0x00000001f4a6a0e0
x[24] = 0x0000000000000001  x[25] = 0x000000016ee52fb0  x[26] = 0x00000001f4a6a0f0  x[27] = 0x0000000000000000
x[28] = 0x0000000000000000     fp = 0x000000016ee52db0     lr = 0x0000000100fafc60     sp = 0x000000016ee52d70
AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV (null:arm64+0x100003cc0) in main+0x90
==31311==ABORTING
[1]    31311 abort      ./null
*/