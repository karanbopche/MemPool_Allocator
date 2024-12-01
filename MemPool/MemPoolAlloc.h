#ifndef MEM_POOL_ALLOC_H
#define MEM_POOL_ALLOC_H

#include <stdint.h>

typedef struct {
    const size_t size;
    void * const addr;
} AllocBuff;

[[nodiscard]] const AllocBuff MemPoolAlloc(size_t bytes);
void MemPoolFree(const AllocBuff * const buffer);

#endif
