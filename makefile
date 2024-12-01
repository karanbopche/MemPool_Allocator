all:
	gcc main.c MemPool/MemPoolAlloc.c -o allocator.exe -g -O0 -Wall -Werror

 