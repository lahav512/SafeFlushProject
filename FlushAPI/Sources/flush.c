#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/tools.h"
#include "../Headers/flush.h"

void __attribute__((constructor)) setup();

void read(long address, long len, char ** buff) {
    FILE * file_p;

    // Open the file
    file_p = fopen(FILEPATH, "r+");
    if (!file_p) {
        fprintf(stderr, "Could not read the file.");
        *buff = NULL;
        return;
    }

    // Go to the relevant file address
    fseek(file_p, (long) address, SEEK_SET);

    // Get the relevant data into 'buff'
    *buff = (char *) malloc((len+1) * sizeof(char));
    fgets(*buff, (long) len + 1, file_p);
    (*buff)[len] = '\0';

    // Close the file
    fclose(file_p);
}
void write(long address, long len, char * buff) {
    FILE *file_p;
    file_p = fopen(FILEPATH, "r+");
    fseek(file_p, address, SEEK_SET);
    fprintf(file_p, "%s", buff);
    fclose(file_p);
}
void erase(int block) {
    FILE *file_p;
    file_p = fopen(FILEPATH, "r+");
    fseek(file_p, BLOCK_BITS * block, SEEK_SET);
    fprintf(file_p, "%0*d", BLOCK_BITS, 0);
    fclose(file_p);
}
void createStorage() {
    FILE *file_p;
    file_p = fopen(FILEPATH, "w");
    fprintf(file_p, "%0*d", MEMORY_BITS, 0);
    fclose(file_p);
}

void setup() {
    char * file_path = getRootDir();
    strcat(file_path, RELATIVE_FILEPATH);
    FILEPATH = file_path;

    MEMORY_BITS = BLOCK_BITS * BLOCK_COUNT;
}

const FlushAPI flushAPI = {
        read,
        write,
        erase,
        createStorage
};
