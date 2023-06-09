#ifndef USE_BUDDY

#ifndef _MM_IMP_H_
#define _MM_IMP_H_

/*
*   Based on: https://www.youtube.com/watch?v=74s0m4YoHgM
*   The idea of this memory allocator algorithm is to use
*   an implicit list of blocks, which supports merging 
*   forward. The end of the list is marked by EOL.
*   Blocks are used in order to allign memory.
*/

#include "memoryManager.h"

typedef union header_t {
    uint64_t size;
    uint8_t allocated : 1;  // bit_0
} header_t;

#define HEADER_SIZE (sizeof(header_t))
#define EOL_SIZE HEADER_SIZE
#define MIN_REQUEST (HEADER_SIZE + 2)

// *ptr % 2 == 0 => not allocated / free
// -2 = 111...1110
#define MASK_LAST_BIT(num) ((num) & ~0x1)
#define GET_SIZE(size) (MASK_LAST_BIT(size))

// size == 0 && allocated == 1 => EOL
// so we can check if *ptr == 1 bc 1 = 000...001
#define IS_EOL(size) ( !(GET_SIZE(size) > 0) )

/*-------------- Functions -----------------------*/

void freeBlock(header_t * ptr);

void addBlock(header_t * ptr, uint64_t len);

header_t * findFree(uint64_t len);

/**
 * @note EOL means End of List
*/
void addEOL(header_t * ptr);

#endif // _MM_IMP_H_
#endif // USE_BUDDY