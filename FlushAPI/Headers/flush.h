#ifndef C_SANDBOX_FLUSH_H
#define C_SANDBOX_FLUSH_H

static const long BLOCK_BITS = 4096 * 8;
static const long BLOCK_COUNT = 12;
static long MEMORY_BITS; // This variable is updated in the setup function.

#define RELATIVE_FILEPATH "FlushAPI\\Data\\storage.txt"

char * FILEPATH;

typedef struct {
    void (*read)(long address, long len, char ** buff);
    void (*write)(long address, long len, char * buff);
    void (*erase)(int block);
    void (*createStorage)();
    long BLOCK_BITS;
    long BLOCK_COUNT;
    long MEMORY_BITS;
} FlushAPI;

extern const FlushAPI flushAPI;

#endif
