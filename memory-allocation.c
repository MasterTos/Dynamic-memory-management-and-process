#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>
#include <sys/types.h>

#define PAGE_SIZE (uint64_t)(1 << 12) //PAGE_SIZE = 4096

#define MULTIPLE_SIZE 10

typedef struct
{
    uint8_t * page;
    uint64_t size;
} Page;

uint64_t page_ptr_size(uint64_t size);
int realloc_page_ptr(Page * page_ptr, uint64_t current_size, uint64_t new_size);
void free_all(Page * page_ptr, uint64_t size);

int main()
{
    int i, input, current_size = MULTIPLE_SIZE;

    Page * page_ptr = calloc(page_ptr_size(current_size), PAGE_SIZE);

    for( i = 0 ; i < current_size ; i++)
    {
        page_ptr[i].page = (uint8_t *)malloc(sizeof(uint8_t)*PAGE_SIZE);
        page_ptr[i].size = sizeof(uint8_t) * PAGE_SIZE;
        printf("%d %" PRIx64 "\n", i, page_ptr[i]);
    }

    while(1)
    {
        int a;
        printf("Please enter new page_ptr size (enter 0 to exit) : ");
        if(scanf("%d", &input) == 0)
        {
            fprintf(stderr, "Error, Invalid input!!\n");
            exit(EXIT_FAILURE);
        }
        if(input <= 0) break;
        //current_size = realloc_page_ptr(page_ptr, current_size, input);

        int new_size = input;
        if(new_size < current_size) {
        int i;
        for(i = new_size ; i < current_size ; i++) {
                printf("%" PRIx64 " %d\n", page_ptr[i], page_ptr[i].size);
            free(page_ptr[i].page);
            page_ptr[i].size = 0;
        }
    }
    printf("page_ptr address before realloc :%" PRIx64 "\n", page_ptr[0]);
    if((page_ptr = realloc(page_ptr, page_ptr_size(new_size)*PAGE_SIZE)) == NULL)
    {
        fprintf(stderr, "Error, (re)allocation memory!!\n");
        exit(EXIT_FAILURE);
    }

    if(current_size < new_size) {
        int i;
        for( i = current_size ; i < new_size ; i++) {
            page_ptr[i].page = (uint8_t *)malloc(sizeof(uint8_t)*PAGE_SIZE);
            page_ptr[i].size = sizeof(uint8_t) * PAGE_SIZE;
        }
    }
    printf("page_ptr address after realloc :%" PRIx64 "\n", page_ptr[0]);

        current_size = new_size;



    }
    free_all(page_ptr, current_size);


    return 0;
}

uint64_t page_ptr_size(uint64_t size)
{
    return (uint64_t)(ceil((float)size / MULTIPLE_SIZE)* MULTIPLE_SIZE);
}

int realloc_page_ptr(Page *page_ptr, uint64_t current_size, uint64_t new_size)
{
    printf("page_ptr address before realloc :%" PRIx64 "\n", page_ptr[0]);
    if(current_size == new_size) return new_size;
    else if(new_size < current_size) {
        int i;
        for(i = new_size ; i < current_size ; i++) {
                printf("%" PRIx64 " %d\n", page_ptr[i], page_ptr[i].size);
            free(page_ptr[i].page);
            page_ptr[i].size = 0;
        }
    }

    if((page_ptr = realloc(page_ptr, page_ptr_size(new_size)*PAGE_SIZE)) == NULL)
    {
        fprintf(stderr, "Error, (re)allocation memory!!\n");
        exit(EXIT_FAILURE);
    }

    if(current_size < new_size) {
        int i;
        for( i = current_size ; i < new_size ; i++) {
            page_ptr[i].page = (uint8_t *)malloc(sizeof(uint8_t)*PAGE_SIZE);
            page_ptr[i].size = sizeof(uint8_t) * PAGE_SIZE;
        }
    }
    printf("page_ptr address after realloc :%" PRIx64 "\n", page_ptr[0]);

        return new_size;
}

void free_all(Page * page_ptr, uint64_t size) {
    //free(page_ptr);
    int i;
    for(i = 0 ; i < size ; i++) {
        free(page_ptr[i].page);
        //page_ptr[i].size = 0;
        printf("%d %" PRIx64 "\n", i, page_ptr[i]);
    }
    free(page_ptr);
}
