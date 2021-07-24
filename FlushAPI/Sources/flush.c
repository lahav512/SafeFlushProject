#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/tools.h"
#include "../Headers/flush.h"

void __attribute__((constructor)) setup();

void read(long address, long len, char ** buff) {
    // Open the file
    FILE * file_p;
    file_p = fopen(FILEPATH, "r+");
    if (!file_p) {
        fprintf(stderr, "Could not read the file.");
        *buff = NULL;
        return;
    }

    fseek(file_p, (long) address, SEEK_SET); // Go to the relevant file address

    // Get the relevant data into 'buff'
    *buff = (char *) malloc((len+1) * sizeof(char));
    fgets(*buff, (long) len + 1, file_p);
    (*buff)[len] = '\0';

    fclose(file_p); // Close the file
}
void write(long address, long len, char * buff) {
    // Open the file
    FILE *file_p;
    file_p = fopen(FILEPATH, "r+");

    fseek(file_p, address, SEEK_SET); // Go to the relevant file address
    fprintf(file_p, "%s", buff); // Write 'buff' into the file
    fclose(file_p); // Close the file
}
void erase(int block) {
    // Open the file
    FILE *file_p;
    file_p = fopen(FILEPATH, "r+");

    fseek(file_p, BLOCK_BITS * block, SEEK_SET); // Go to the relevant file address
    fprintf(file_p, "%0*d", BLOCK_BITS, 0); // Erase the relevant section of the file
    fclose(file_p); // Close the file
}
void createStorage() {
    // Open the file
    FILE *file_p;
    file_p = fopen(FILEPATH, "w");

    fprintf(file_p, "%0*d", MEMORY_BITS, 0); // Create a storage of 'MEMORY_BITS' number of zeros.
    fclose(file_p); // Close the file
}

// Library constructor
void setup() {
    // Get the storage file path
    char * file_path = getRootDir();
    strcat(file_path, RELATIVE_FILEPATH);
    FILEPATH = file_path;

    // Calculate the value of 'MEMORY_BITS'
    MEMORY_BITS = BLOCK_BITS * BLOCK_COUNT;
}

const FlushAPI flushAPI = {
        read,
        write,
        erase,
        createStorage
};
