#include <stdio.h>
// The header
struct block{
	size_t size;
	int free;
	struct block *next;
}block;

struct block *free_list;
struct block *remaining_block;
struct block *previous_block;

void create_freelist();
void *my_malloc(size_t allocated_bytes);
void my_free(void* ptr);
