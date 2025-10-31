/**
 * Write a simple program that allocates memory using malloc()but
 * forgets to free it before exiting. What happens when this program
 * runs? Can you use gdb to find any problems with it? How about
 * valgrind(again with the --leak-check=yesflag)?
 *
 * Answer:
 * - No support for leak detection in macOS
 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int* x = (int*) malloc(3*sizeof(int)); // 3-element int array
    x = 0; 
    printf("Hello leak\n");
    return 0;
}

/**********
 * OUTPUT - Q4
 **********
 leaks -atExit -- ./q4
q4(36447) MallocStackLogging: could not tag MSL-related memory as no_footprint, so those pages will be included in process footprint - No such file or directory (2)
q4(36447) MallocStackLogging: zone[0] is not the normal default zone so can't turn on lite mode.
Hello leak
Can't examine target process's malloc zone asan_0x105f769d8, so memory analysis will be incomplete or incorrect.
Reason: failed to resolve canonical path for % in dyld shared cache./Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/clang/15.0.0/lib/darwin/libclang_rt.asan_osx_dynamic.dylib

Process 36447 is not debuggable. Due to security restrictions, leaks can only show or save contents of readonly memory of restricted processes.

Process:         q4 [36447]
Path:            /Users/USER/Documents/asterisk/q4
Load Address:    0x104d8c000
Identifier:      q4
Version:         0
Code Type:       ARM64
Platform:        macOS
Parent Process:  leaks [36446]
Target Type:     live task

Date/Time:       2025-11-01 14:20:14.630 -0700
Launch Time:     2025-11-01 14:20:13.694 -0700
OS Version:      macOS 26.0.1 (25A362)
Report Version:  7
Analysis Tool:   /usr/bin/leaks

Physical footprint:         14.7M
Physical footprint (peak):  14.7M
Idle exit:                  untracked
----

leaks Report Version: 4.0
leaks[36446]: [fatal] unable to inspect heap ranges of target process; it may be using a malloc replacement library without the required support
*/