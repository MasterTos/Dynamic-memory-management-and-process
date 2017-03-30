#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>
#include <sys/types.h>

#define PAGE_SIZE (uint64_t)(1 << 12) //PAGE_SIZE = 4096

#define MULTIPLE_SIZE 10

typedef struct {
    uint8_t * page;
    uint64_t size;
} Page;

uint64_t page_ptr_size(uint64_t size);
Page * realloc_page_ptr(Page * page_ptr, uint64_t * current_size, uint64_t new_size);
void free_all(Page * page_ptr, uint64_t size);

int main() {
    int i, input, current_size = MULTIPLE_SIZE;

    Page * page_ptr = calloc(page_ptr_size(current_size), PAGE_SIZE);

    for( i = 0 ; i < current_size ; i++) {
        page_ptr[i].page = (uint8_t *)malloc(sizeof(uint8_t)*PAGE_SIZE);
        page_ptr[i].size = sizeof(uint8_t) * PAGE_SIZE;
        printf("%d %" PRIx64 " h %" PRIx64 "\n", i, page_ptr[i], page_ptr[i].page);
    }

    while(1) {
        int a;
        printf("Please enter new page_ptr size (enter 0 to exit) : ");
        if(scanf("%d", &input) == 0) {
            fprintf(stderr, "Error, Invalid input!!\n");
            exit(EXIT_FAILURE);
        }
        if(input <= 0) break;
        page_ptr = realloc_page_ptr(page_ptr, &current_size, input);
    }
    free_all(page_ptr, current_size);
    return 0;
}

uint64_t page_ptr_size(uint64_t size) {
    return (uint64_t)(ceil((float)size / MULTIPLE_SIZE)* MULTIPLE_SIZE);
}

Page * realloc_page_ptr(Page * page_ptr, uint64_t *current_size, uint64_t new_size) {
    int c_size = *current_size;
    if(c_size == new_size) return page_ptr;
    else if(new_size < c_size) {
        int i;
        for(i = new_size ; i < c_size ; i++) {
            printf("free %" PRIx64 " %d\n", page_ptr[i], page_ptr[i].size);
            free(page_ptr[i].page);
            page_ptr[i].size = 0;
        }
    }
    if((page_ptr = realloc(page_ptr, page_ptr_size(new_size)*PAGE_SIZE)) == NULL) {
        fprintf(stderr, "Error, (re)allocation memory!!\n");
        exit(EXIT_FAILURE);
    }

    if(c_size < new_size) {
        int i;
        for( i = c_size ; i < new_size ; i++) {
            page_ptr[i].page = (uint8_t *)malloc(sizeof(uint8_t)*PAGE_SIZE);
            page_ptr[i].size = sizeof(uint8_t) * PAGE_SIZE;
        }
    }
    *current_size = new_size;
    return page_ptr;
}

void free_all(Page * page_ptr, uint64_t size) {
    int i;
    for(i = 0 ; i < size ; i++) {
        free(page_ptr[i].page);
        page_ptr[i].size = 0;
        printf("free array %d %" PRIx64 "\n", i, page_ptr[i]);
    }
    free(page_ptr);
}
