#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>
#include <sys/types.h>

#define PAGE_SIZE (uint64_t)(1 << 12) //PAGE_SIZE = 4096

#define MULTIPLE_SIZE 10

uint64_t page_ptr_size(uint64_t size);

typedef struct
{
    uint8_t * page;
    uint64_t size;
} Page;

int main()
{
    int i, input = 1, current_size = MULTIPLE_SIZE;

    Page * page_ptr = calloc(page_ptr_size(current_size), PAGE_SIZE);

    for( i = 0 ; i < current_size ; i++)
    {
        page_ptr[i].page = (uint8_t *)malloc(sizeof(uint8_t)*PAGE_SIZE);
        page_ptr[i].size = sizeof(uint8_t) * PAGE_SIZE;
    }

    while(input > 0)
    {
        int a;
        printf("Please enter new page_ptr size (enter 0 to exit) : ");
        if(scanf("%d", &input) == 0)
        {
            fprintf(stderr, "Error, Invalid input!!\n");
            exit(EXIT_FAILURE);
        }
        current_size = realloc_page_ptr(page_ptr, current_size, input);

    }

    return 0;
}

uint64_t page_ptr_size(uint64_t size)
{
    return (uint64_t)(ceil((float)size / MULTIPLE_SIZE)* MULTIPLE_SIZE);
}

int realloc_page_ptr(Page * page_ptr, uint64_t current_size, uint64_t new_size)
{
    if(current_size == new_size) return new_size;
    else if(new_size < current_size) {
        int i;
        for(i = new_size - 1 ; i < current_size ; i++) {
            free(page_ptr[i].page);
            page_ptr[i].size = 0;
        }
    }
    else if(realloc(page_ptr, page_ptr_size(new_size)) != NULL)
    {
        fprintf(stderr, "Error, (re)allocation memory!!\n");
        exit(EXIT_FAILURE);
    }

    if(current_size < new_size) {
        int i;
        for( i = current_size - 1 ; i < new_size ; i++) {
            page_ptr[i].page = (uint8_t *)malloc(sizeof(uint8_t)*PAGE_SIZE);
            page_ptr[i].size = sizeof(uint8_t) * PAGE_SIZE;
        }
    }

        return new_size;
}
