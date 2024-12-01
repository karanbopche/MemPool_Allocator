#ifndef MEM_POOL_ALLOC_CFG_H
#define MEM_POOL_ALLOC_CFG_H

#define BLOCK_BYTE_SIZE     32
#define TOTAL_BLOCKS        128

#define SET_CONSECUTIVE_BITS(from, to)  (((1<<(to-from))-1)<<from) 

#define ARR_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))
#define BITS_IN_BYTE    8
#define BITS_IN(x) (sizeof(x)*BITS_IN_BYTE)

#define BLOCK_ID_TO_BYTE_OFFSET(id) (id*BLOCK_BYTE_SIZE)

#endif
