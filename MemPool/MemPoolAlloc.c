#include <stdint.h>
#include <stdbool.h>
#include "MemPoolAllocCfg.h"
#include "MemPoolAlloc.h"

uint32_t heapMemory[(BLOCK_BYTE_SIZE*TOTAL_BLOCKS)/sizeof(uint32_t)];
uint32_t heapAllocBitmap[(TOTAL_BLOCKS)/BITS_IN(uint32_t)];

static bool IsBlockFree(size_t blockIdx);
static void* ReserveBlock(size_t blockIdx);
static void FreeBlock(size_t blockIdx);

static bool IsBlockFree(size_t blockIdx)
{
    const uint8_t bit = blockIdx % BITS_IN(heapAllocBitmap[0]);
    const uint32_t offset = blockIdx / BITS_IN(heapAllocBitmap[0]);
    return (heapAllocBitmap[offset] & (1<<bit)) == 0;
}

static void* ReserveBlock(size_t blockIdx)
{
    const uint8_t bit = blockIdx % BITS_IN(heapAllocBitmap[0]);
    const uint32_t offset = blockIdx / BITS_IN(heapAllocBitmap[0]);
    heapAllocBitmap[offset] |= (1<<bit);
    return &heapMemory[BLOCK_ID_TO_BYTE_OFFSET(blockIdx)/sizeof(heapMemory[0])];
}

static void FreeBlock(size_t blockIdx)
{
    const uint8_t bit = blockIdx % BITS_IN(heapAllocBitmap[0]);
    const uint32_t offset = blockIdx / BITS_IN(heapAllocBitmap[0]);
    heapAllocBitmap[offset] &= ~(1<<bit);
}

const AllocBuff MemPoolAlloc(size_t bytes)
{
    const size_t blocksToAllocate = (bytes/BLOCK_BYTE_SIZE) + ((bytes%BLOCK_BYTE_SIZE) != 0);

    size_t index = 0;
    while(index < BITS_IN(heapAllocBitmap))
    {
        size_t currentBlock = index;
        size_t freeBlocksRequired = blocksToAllocate;
        while(freeBlocksRequired > 0 && IsBlockFree(currentBlock) == true)
        {
            freeBlocksRequired--;
            currentBlock++;
        }
        if(freeBlocksRequired == 0)
        {
            void *buffAddr = ReserveBlock(index);
            for(size_t i=index+1;i<currentBlock;i++)
                ReserveBlock(i);
            AllocBuff buffer = {blocksToAllocate*BLOCK_BYTE_SIZE, buffAddr};
            return buffer;
        }
        index++;
    }
    AllocBuff buffer = {0, 0};
    return buffer;
}

void MemPoolFree(const AllocBuff * const buffer)
{
    size_t blockIdx = (((uint32_t*)buffer->addr - heapMemory)*sizeof(heapMemory[0]))/BLOCK_BYTE_SIZE;
    size_t blocksLength = buffer->size/BLOCK_BYTE_SIZE;
    while(blocksLength--){
        FreeBlock(blockIdx);
        blockIdx++;
    }
}
