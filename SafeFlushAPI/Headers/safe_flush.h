#ifndef C_SANDBOX_SAFE_FLUSH_H
#define C_SANDBOX_SAFE_FLUSH_H

#include "../../FlushAPI/Headers/flush.h"

typedef struct {
    void (*safeWrite)(long address, long len, char * buff);
    void (*eraseAll)();
} SafeFlushAPI;

extern const SafeFlushAPI safeFlushAPI;

void safeWrite(long address, long len, const char * buff);
void eraseAll();

#endif
