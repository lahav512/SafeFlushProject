#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../Headers/safe_flush.h"

void safeWrite(long address, long len, const char *buff) {
    // Calculate the min and max blocks which are about to change
    int block_min = (int) floor(address / (double) BLOCK_BITS);
    int block_max = (int) ceil((address + len) / (double) BLOCK_BITS) - 1;

    // Setup buffer variables
    long new_buff_size = (block_max - block_min + 1) * BLOCK_BITS;
    char *old_buff;

    // Setup index and boolean variables
    long bit_index = address;
    short is_first_block_erased = 0;
    short is_last_block_erased = 0;

    // Load the section of the entire range blocks from the storage into 'old_buff'
    flushAPI.read(block_min * BLOCK_BITS, new_buff_size, &old_buff);

    // Iterate the blocks in the storage to determine which of them should be erased
    for (int block_ind = block_min; block_ind <= block_max; block_ind++) {
        // Iterate the bits in the storage
        while (bit_index < (block_ind + 1) * BLOCK_BITS && bit_index - address < len) {
            if (old_buff[bit_index - block_min * BLOCK_BITS] == '1') {
                if (buff[bit_index - address] == '0') {
                    // Block needs to be erased

                    // Update boolean regarding whether the first or last block have been erased.
                    if (block_ind == block_min) {
                        is_first_block_erased = 1;
                    } else if (block_ind == block_max) {
                        is_last_block_erased = 1;
                    }

                    // Erase the block
                    printf("erase block %d\n", block_ind);
                    flushAPI.erase(block_ind);

                    bit_index = (block_ind + 1) * BLOCK_BITS; // Update index
                    break;
                }
            }
            bit_index++; // Update index
        }
    }

    // Setup the bit indices
    long start_ind = block_min * BLOCK_BITS;
    long middle_start_ind = address;
    long middle_end_ind = address + len;

    // Setup the bit indices if necessary
    if (!is_first_block_erased) {
        new_buff_size -= address - block_min * BLOCK_BITS;
        start_ind = middle_start_ind;
    }
    if (!is_last_block_erased) {
        new_buff_size -= (block_max + 1) * BLOCK_BITS - address - len;
    }

    // Setup 'new_buff' according to its new size
    char * new_buff = (char *) malloc((new_buff_size + 1) * sizeof(char));

    // Copy the relevant values from 'buff' and 'old_buff' into 'new_buff'
    for (int sub_bit_index = start_ind; sub_bit_index <= new_buff_size + start_ind; sub_bit_index++) {
        if (sub_bit_index < middle_start_ind) {
            // copy from 'old_buff' into the beginning of 'new_buff'
            new_buff[sub_bit_index - start_ind] = old_buff[sub_bit_index - start_ind];
        } else if (sub_bit_index < middle_end_ind) {
            // copy from 'buff' into the middle of 'new_buff'
            new_buff[sub_bit_index - start_ind] = buff[sub_bit_index - middle_start_ind];
        } else {
            // copy from 'old_buff' into the middle of 'new_buff'
            new_buff[sub_bit_index - start_ind] = old_buff[sub_bit_index];
        }
    }

    // Close the string of 'new_buff'
    new_buff[new_buff_size] = '\0';

    // Write 'new_buff into the storage
    flushAPI.write(start_ind, new_buff_size, new_buff);
}
void eraseAll() {
    // Erase all blocks
    for (int i=0; i < BLOCK_COUNT; i++) {
        flushAPI.erase(i);
    }
}

const SafeFlushAPI safeFlushAPI = {
        (void (*)(long, long, char *)) safeWrite,
        eraseAll
};