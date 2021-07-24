#include <stdio.h>
#include <string.h>
#include "SafeFlushAPI/Headers/safe_flush.h"

int main() {
    // Create an an empty (zeros) storage.
//    flushAPI.createStorage();

    char * data;
    char * chunk = "0101110101010111111111111111010100000111000110101100010101";
    long address = BLOCK_BITS - 4;

    // Read and print a the section of the storage.
    flushAPI.read(address, (long) strlen(chunk), &data);
    printf("%s\n", data);

    // Safely write 'chunk' into the same section of the storage.
    safeFlushAPI.safeWrite(address, (long) strlen(chunk), chunk);

    // Read and print a the new section of the storage which should be identical to 'chunk'.
    flushAPI.read(address, (long) strlen(data), &data);
    printf("%s\n", data);

    return 0;
}
