#include <stdio.h>
#include "MemPool/MemPoolAlloc.h"

int main()
{
    printf("allocating\n");
    AllocBuff buf = MemPoolAlloc(31);
    MemPoolFree(&buf);
    return 0;
}
