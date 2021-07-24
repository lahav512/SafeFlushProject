#ifndef C_SANDBOX_FLUSH_H
#define C_SANDBOX_FLUSH_H

static int BLOCK_BITS = 4096 * 256;
static int BLOCK_COUNT = 12;
static int MEMORY_BITS = 4096 * 256 * 12;
#define RELATIVE_FILEPATH "FlushAPI\\Data\\storage.txt"


char * FILEPATH;

typedef struct {
    void (*read)(long address, long len, char ** buff);
    void (*write)(long address, long len, char * buff);
    void (*erase)(int block);
    void (*setup)();
    void (*createStorage)();
} FlushAPI;

extern const FlushAPI flushAPI;


#endif
