#include <stdlib.h>

void f(void)
{
   int* x = malloc(10 * sizeof(int));
   x[10] = 0;        // problem 1: heap block overrun
}                    // problem 2: memory leak -- x not freed

int main(void)
{
   f();
   return 0;
}

--detect memory leak:
valgrind --leak-check=yes ./test

[ashukla1@ctoqalnx018 my_test]$ valgrind --leak-check=yes ./test
==767741== Memcheck, a memory error detector
==767741== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==767741== Using Valgrind-3.21.0 and LibVEX; rerun with -h for copyright info
==767741== Command: ./test
==767741==
==767741== Invalid write of size 4
==767741==    at 0x401144: f() (in /home/ashukla1/my_test/test)
==767741==    by 0x401155: main (in /home/ashukla1/my_test/test)
==767741==  Address 0x4da0ca8 is 0 bytes after a block of size 40 alloc'd
==767741==    at 0x484482F: malloc (vg_replace_malloc.c:431)
==767741==    by 0x401137: f() (in /home/ashukla1/my_test/test)
==767741==    by 0x401155: main (in /home/ashukla1/my_test/test)
==767741==
==767741==
==767741== HEAP SUMMARY:
==767741==     in use at exit: 40 bytes in 1 blocks
==767741==   total heap usage: 2 allocs, 1 frees, 72,744 bytes allocated
==767741==
==767741== 40 bytes in 1 blocks are definitely lost in loss record 1 of 1
==767741==    at 0x484482F: malloc (vg_replace_malloc.c:431)
==767741==    by 0x401137: f() (in /home/ashukla1/my_test/test)
==767741==    by 0x401155: main (in /home/ashukla1/my_test/test)
==767741==
==767741== LEAK SUMMARY:
==767741==    definitely lost: 40 bytes in 1 blocks
==767741==    indirectly lost: 0 bytes in 0 blocks
==767741==      possibly lost: 0 bytes in 0 blocks
==767741==    still reachable: 0 bytes in 0 blocks
==767741==         suppressed: 0 bytes in 0 blocks
  
