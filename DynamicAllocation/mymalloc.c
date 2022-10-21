#include <stdlib.h>
#include <sys/mman.h>
#include "mymalloc.h"

void create_freelist(int heap_size){
	//mmap returns a pointer to a chunk of free space
	free_list = mmap(NULL, heap_size, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
	free_list->size = heap_size - sizeof(struct block);
	free_list->free = 1;
	free_list->next = NULL;
}

void *my_malloc(size_t allocated_bytes){
	printf("ALLOCATING BYTES: %d\n", allocated_bytes);
	remaining_block = free_list;
	while((((remaining_block->size) < allocated_bytes)||((remaining_block->free) == 0)) && (remaining_block->next != NULL)){
		previous_block = remaining_block;
		remaining_block = remaining_block->next;
		printf("SKIPPING BLOCK SIZE: %d\n", previous_block->size);
 	}
	if((remaining_block->size) == allocated_bytes){
		remaining_block->free = 0;
		return (void*)(++remaining_block);
	}
	else if((remaining_block->size) > (allocated_bytes + sizeof(struct block))){
		printf("ALLOCATED BYTES: %d\n",  allocated_bytes);
		struct block *block = (void*)((void*)remaining_block + allocated_bytes + sizeof(struct block));
		block->size = (remaining_block->size) - allocated_bytes - sizeof(struct block);
		block->free = 1;
		block->next = remaining_block->next;
		remaining_block->size = allocated_bytes;
		remaining_block->free = 0;
		remaining_block->next = block;
		return (void*)(++remaining_block);
	}
	else{
		printf("NO SUFFICIENT MEMORY\n");
	}
}

void my_free(void* ptr){
	struct block* remaining_block = ptr;
	struct block *previous_block;
	-- remaining_block;
	remaining_block->free = 1;
	printf("FREEING BLOCK...\n");
	printf("MERGING BLOCKS...\n");
	remaining_block = free_list;
	while((remaining_block->next) != NULL){
		if(remaining_block->free && remaining_block->next->free && remaining_block->next->next){
			remaining_block->size += (remaining_block->next->size) + (sizeof(struct block));
			remaining_block->next = remaining_block->next->next;

		} else if(remaining_block->free && remaining_block->next->free && !remaining_block->next->next){
			remaining_block->size += (remaining_block->next->size) + (sizeof(struct block));
		}
	previous_block = remaining_block;
	remaining_block = remaining_block->next;
	}
}

