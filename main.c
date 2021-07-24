#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SafeFlushAPI/Headers/safe_flush.h"

int main() {
    // Create an an empty (zeros) storage.
//    flushAPI.createStorage();

    char * data;
    char * chunk = "0101110101010111111111111111010100000111000110101100010101";
    long address = BLOCK_BITS - 4;

    flushAPI.read(address, (long) strlen(chunk), &data);
    printf("%s\n", data);

    safeFlushAPI.safeWrite(address, (long) strlen(chunk), chunk);
    return 0;
}
