#include <stdio.h>
#include "mymalloc.h"

int main(){
	int heap_size = 30000;
	int allocation_sizes[10] = {10, 20, 30, 270000};
	create_freelist(heap_size);

	int *p = (int*)my_malloc(allocation_sizes[0] * sizeof(int));
	my_free(p);
	int *q = (int*)my_malloc(allocation_sizes[1] * sizeof(int));
	char *r = (char*)my_malloc(allocation_sizes[2] * sizeof(char));	
	int *s = (int*)my_malloc(allocation_sizes[3] * sizeof(int));
	
}
