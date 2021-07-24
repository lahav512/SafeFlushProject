#ifndef C_SANDBOX_FLUSH_H
#define C_SANDBOX_FLUSH_H


/**
 * <br>
 * Represents the number of bits in a block.
 */
static const long BLOCK_BITS = 4096 * 8;
/**
 * <br>
 * Represents the total number of blocks in the storage.
 */
static const long BLOCK_COUNT = 12;
/**
 * <br>
 * Represents the total number of bits in the storage.
 */
static long MEMORY_BITS; // This variable is updated in the setup function.

#define RELATIVE_FILEPATH "FlushAPI\\Data\\storage.txt"

char * FILEPATH;

typedef struct {
    /**
     * <br>
     * Read a string of characters from the storage.
     */
    void (*read)(long address, long len, char ** buff);
    /**
     * <br>
     * Write a string of characters into the storage.
     */
    void (*write)(long address, long len, char * buff);
    /**
     * <br>
     * Erase the entire block. The numbers of blocks is BLOCK_COUNT and the indexing starts from 0.
     */
    void (*erase)(int block);
    /**
     * <br>
     * Create a new zeros storage file with the lenght of MEMORY_BITS. This function is relevant only for the dammy version which uses the storage.txt file instead of a physical storage.
     * Run this function only if the storage.txt is not exist or corrupted!
     */
    void (*createStorage)();

    long BLOCK_BITS;
    long BLOCK_COUNT;
    long MEMORY_BITS;
} FlushAPI;

extern const FlushAPI flushAPI;

#endif
