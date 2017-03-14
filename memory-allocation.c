#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define PAGE_SIZE (uint64_t)(1 << 12)

typedef struct {
    uint8_t * page;
    uint64_t size;
} Page;

int main() {
    int i;
    Page * page_ptr = calloc(10, PAGE_SIZE);
    for( i = 0 ; i < 10 ; i++) {
        page_ptr[i].page = (uint8_t *)malloc(sizeof(uint8_t)*PAGE_SIZE);
        page_ptr[i].size = sizeof(uint8_t) * PAGE_SIZE;
    }

}
