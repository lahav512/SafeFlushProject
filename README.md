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

### Setup: `void setup()`
Setup the library and update the path of the storage file. **You must excecute this function before using the library!**

### Constants
The constants are declared in the `FlushAPI/Headers/flush.h` file.<br><br>
`BLOCK_BITS` - Represents the number of bits in a block. `Default: 4096 * 256`<br>
`BLOCK_COUNT` - Represents the total number of blocks in the storage. `Default: 12`<br>
`MEMORY_BITS` - Represents the total number of bits in the storage. `Default: 4096 * 256 * 12`<br>

## SafeFlushAPI
This is an extension library of the `FlushAPI`. It enables to write into the storage without with no worries about overwriting `0` on `1`. This funciton also prints `erase block i` for every block `i` that has been erased before it is restored and updated.

### Safe Write: `void safeWrite(long address, long len, const char *buff)`
Safely write a string of characters into the storage.

### Erase All: `void eraseAll()`
Erase all blocks.

## Examples

### Import
```
#include "SafeFlushAPI/Headers/safe_flush.h"
```

### Setup
```
// Setup the flushAPI library.
flushAPI.setup();
```

### Create Storage
```
// Create an an empty (zeros) storage.
flushAPI.createStorage();
```

### Read
This example reads the first two blocks into the `data` variable.
```
#include <stdio.h>
#include <string.h>

char * data;
long address = 0;
long len = 2 * flushAPI.BLOCK_BITS;

flushAPI.read(address, len, &data);
printf("%s\n", data);
```

### Write
Thise example writes on both `block 0` and `block 1`. This operation will not work with a physical storage, but can be used in order to setup the `storage.txt` file.
```
#include <stdio.h>
#include <string.h>

char * data = "0101110101010111111111111111010100000111000110101100010101";
long address = flushAPI.BLOCK_BITS - 4;

flushAPI.write(address, (long) strlen(data), data);
```

### Erase
```
flushAPI.erase(0); // Erase the first block
flushAPI.erase(1); // Erase the second block
flushAPI.erase(flushAPI.BLOCK_COUNT - 1); // Erase the last block

safeFlushAPI.eraseAll(); // Erase all blocks
```

### Safe Write
Thise example safely writes on both `block 0` and `block 1`. It erases some of the blocks if necessary and rewrite their content while merging the new data.
```
#include <stdio.h>
#include <string.h>

char * data = "0101110101010111111111111111010100000111000110101100010101";
long address = flushAPI.BLOCK_BITS - 4;

safeFlushAPI.safeWrite(address, (long) strlen(data), data);
```
