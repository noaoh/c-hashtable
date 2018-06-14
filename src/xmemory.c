#include <stdlib.h>
#include <stdio.h>
#include "xmemory.h"

void* xmalloc(size_t size) {
        void* new_mem = (void*)malloc(size);
        if (new_mem == NULL) {
                fprintf(stderr, "fatal: memory exhausted (xmalloc of %lu bytes)", size);
                exit(-1);
        }
        return new_mem;
}

void* xcalloc(size_t num, size_t size) {
        void* new_mem = (void*)calloc(num, size);
        if (new_mem == NULL) {
                fprintf(stderr, "fatal: memory exhausted (xcalloc of %lu bytes)", num * size);
                exit(-1);
        }
        return new_mem;
}
