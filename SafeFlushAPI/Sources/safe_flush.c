#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../Headers/safe_flush.h"

void safeWrite(long address, long len, const char *buff) {

    int block_min = (int) floor(address / (double) BLOCK_BITS);
    int block_max = (int) ceil((address + len) / (double) BLOCK_BITS) - 1;

    long new_buff_size = (block_max - block_min + 1) * BLOCK_BITS;
    char *old_buff;
    flushAPI.read(block_min * BLOCK_BITS, new_buff_size, &old_buff);

    long bit_index = address;
    short is_first_block_erased;
    short is_last_block_erased;
    is_first_block_erased = 0;
    is_last_block_erased = 0;

    for (int block_ind = block_min; block_ind <= block_max; block_ind++) {
        while (bit_index < (block_ind + 1) * BLOCK_BITS && bit_index - address < len) {
            if (old_buff[bit_index - block_min * BLOCK_BITS] == '1') {
                if (buff[bit_index - address] == '0') {
                    if (block_ind == block_min) {
                        is_first_block_erased = 1;
                    } else if (block_ind == block_max) {
                        is_last_block_erased = 1;
                    }

                    printf("erase block %d\n", block_ind);
                    flushAPI.erase(block_ind);
                    bit_index = (block_ind + 1) * BLOCK_BITS;
                    break;
                }
            }
            bit_index++;
        }
    }

    long start_ind = block_min * BLOCK_BITS;
    long middle_start_ind = address;
    long middle_end_ind = address + len;

    if (!is_first_block_erased) {
        new_buff_size -= address - block_min * BLOCK_BITS;
        start_ind = middle_start_ind;
    }
    if (!is_last_block_erased) {
        new_buff_size -= (block_max + 1) * BLOCK_BITS - address - len;
    }

    char * new_buff = (char *) malloc((new_buff_size + 1) * sizeof(char));

    for (int sub_bit_index = start_ind; sub_bit_index <= new_buff_size + start_ind; sub_bit_index++) {
        if (sub_bit_index < middle_start_ind) {
            new_buff[sub_bit_index - start_ind] = old_buff[sub_bit_index - start_ind];
        } else if (sub_bit_index < middle_end_ind) {
            new_buff[sub_bit_index - start_ind] = buff[sub_bit_index - middle_start_ind];
        } else {
            new_buff[sub_bit_index - start_ind] = old_buff[sub_bit_index];
        }
    }

    new_buff[new_buff_size] = '\0';

    flushAPI.write(start_ind, new_buff_size, new_buff);
}
void eraseAll() {
    for (int i=0; i < BLOCK_COUNT; i++) {
        flushAPI.erase(i);
    }
}

const SafeFlushAPI safeFlushAPI = {
        (void (*)(long, long, char *)) safeWrite,
        eraseAll
};