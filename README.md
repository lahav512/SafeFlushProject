# SafeFlushProject
This project contains a module which safely writes into a storage. Currently it stores into a local file, but can be replaced with a physical storage as well.

## FlushAPI
This is an example library of the original flush api. The storage is represented as a `storage.txt` file which is made of zeros and ones. The storage file is located in `FlushAPI/Data/`.

### Read: `void read(long address, long len, char ** buff)`
Read a string of characters from the storage.

### Write: `void write(long address, long len, char * buff)`
Write a string of characters into the storage.

### Erase: `void erase(int block)`
Erase the entire block. The numbers of blocks is `BLOCK_COUNT` and the indexing starts from 0.

### Create Storage: `void createStorage()`
Create a new zeros storage file with the lenght of `MEMORY_BITS`. This function is relevant only for the dammy version which uses the `storage.txt` file instead of a physical storage. **Run this function only if the `storage.txt` is not exist or corrupted!**

### Constants
The constants are declared in the `FlushAPI/Headers/flush.h` header.<br><br>
`BLOCK_BITS` - Represents the number of bits in a block. `Default: 4096 * 8`<br>
`BLOCK_COUNT` - Represents the total number of blocks in the storage. `Default: 12`<br>
`MEMORY_BITS` - Represents the total number of bits in the storage. This always equals to: `BLOCK_BITS * BLOCK_COUNT`<br>

## SafeFlushAPI
This is an extension library of the `FlushAPI`. It enables to write into the storage without with no worries about overwriting `0` on `1`. This funciton also prints `erase block i` for every block `i` that has been erased before it is restored and updated.

### Safe Write: `void safeWrite(long address, long len, const char *buff)`
Safely write a string of characters into the storage.

### Erase All: `void eraseAll()`
Erase all blocks.

## Examples
The library can be tested in the `main.c` source file.

### Import
```
#include "SafeFlushAPI/Headers/safe_flush.h"
```

### Create Storage
```
// Create an an empty (zeros) storage with the length of `MEMORY_BITS`.
flushAPI.createStorage();
```

### Read
This example reads the first two blocks into the `data` variable.
```
#include <stdio.h>
#include <string.h>

char * data;
long address = 0;
long len = 2 * BLOCK_BITS;

flushAPI.read(address, len, &data);
printf("%s\n", data);
```

### Write
Thise example writes on both `block 0` and `block 1`. This operation will not work with a physical storage, but can be used in order to setup the `storage.txt` file.
```
#include <stdio.h>
#include <string.h>

char * data = "0101110101010111111111111111010100000111000110101100010101";
long address = BLOCK_BITS - 4;

flushAPI.write(address, (long) strlen(data), data);
```

### Erase
```
flushAPI.erase(0); // Erase the first block
flushAPI.erase(1); // Erase the second block
flushAPI.erase(BLOCK_COUNT - 1); // Erase the last block

safeFlushAPI.eraseAll(); // Erase all blocks
```

### Safe Write
Thise example safely writes on both `block 0` and `block 1`. It erases some of the blocks if necessary and rewrite their content while merging the new data.
```
#include <stdio.h>
#include <string.h>

char * data = "0101110101010111111111111111010100000111000110101100010101";
long address = BLOCK_BITS - 4;

safeFlushAPI.safeWrite(address, (long) strlen(data), data);
```

### Constants
The constants can be modified in order to easely check the behavior of the library. There are no setters for them since they should be fixed, but they can be accessed directly from the `FlushAPI/Headers/flush.h` header.
```
static const int BLOCK_BITS = 8; // Change the number of bits per block to 8.
static const int BLOCK_COUNT = 10; // Change the number of blocks to 10.
```

### Others
```
char * data;
char * chunk = "0101110101010111111111111111010100000111000110101100010101";
long address = BLOCK_BITS - 4;

// Print chunk
printf("chnuk:    %s\n", chunk);

// Read and print a the section of the storage.
flushAPI.read(address, (long) strlen(chunk), &data);
printf("old data: %s\n", data);

// Safely write 'chunk' into the same section of the storage.
safeFlushAPI.safeWrite(address, (long) strlen(chunk), chunk);

// Read and print a the new section of the storage which should be identical to 'chunk'.
flushAPI.read(address, (long) strlen(data), &data);
printf("new data: %s\n", data);
```
