#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/tools.h"
#include "../Headers/flush.h"

//extern char * FILEPATH;

void read(long address, long len, char ** buff) {
    FILE * file_p;

    file_p = fopen(FILEPATH, "r+");
    if (!file_p) {
        fprintf(stderr, "Could not read the file.");
        *buff = NULL;
        return;
    }

    fseek(file_p, (long) address, SEEK_SET);
    *buff = (char *) malloc((len+1) * sizeof(char));
    fgets(*buff, (long) len + 1, file_p);
    (*buff)[len] = '\0';
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
}

const FlushAPI flushAPI = {
        read,
        write,
        erase,
        setup,
        createStorage
};
