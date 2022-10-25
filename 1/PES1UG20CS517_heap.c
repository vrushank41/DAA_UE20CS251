// Name: Y Sinivas
// SRN: PES1UG20CS517
#include "heap.h"
#include <stdlib.h>

/*
 ** Do not use global variables.
 ** Mark any functions that you declare in this file that are not in the header
 *as static
 ** Do not use static variables
 ** All occurences of count_ptr indicate that the number of comparison
 ** operations need to be stored in the location pointed by it
 ** The implementation can assume it is initialized to 0.
 */

//Heapify function
static int heapify(heap_t *heap)
{
	int j;int k;int v;int heaped;
	int count = 0;
	int n = heap->size-1;
	for(int i=(n-1)/2; i>=0; --i) //parents node
	{
		k=i;
		v=heap->arr[k];
		j=2*k+1;  //left child		
		heaped = 0;
        
		while(!heaped && j<=n)
		{
			//*count_ptr++;
			count++;
			// printf("counter: %d\n", count);
			if((j+1)<=n)
			{
				//*count_ptr++;
				count++;
				if(heap->arr[j]<heap->arr[j+1])
					++j;
			}
			//*count_ptr++;
			count++;
			if(v>=heap->arr[j])
				heaped = 1;
			else
			{
				heap->arr[k]=heap->arr[j];
				k=j;
				j=2*k+1;
			}
				
		}	
		heap->arr[k]=v;
	}
		
	return count;
}

// Initialise heap
// Set heap size to 0
// Set heap max_size to paramter max_size
// Allocate memory of max_size to the array
void init_heap(heap_t *heap, int max_size) {
    heap->size = 0;
    heap->max_size = max_size;
    heap->arr = (int*)malloc(max_size*sizeof(int));
}

// Insert element "key" to heap "heap"
// and store the number of key comparisons made in the
// location pointed to by count_ptr.
void insert(heap_t *heap, int key, int *count_ptr) {
    heap->arr[heap->size] = key;
    heap->size++;
	/* printf("\nBefore heap\n");
	for(int i = 0; i<heap->size; i++){
        printf("%d\t", heap->arr[i]);
    } */
    *count_ptr = heapify(heap);
	/* printf("\nAfter heap\n");
	for(int i = 0; i<heap->size; i++){
        printf("%d\t", heap->arr[i]);
    } */

}

static void swap(int *max, int *min){
	int temp = *max;
	*max = *min;
	*min = temp;
}
// *Removes and Returns* the maximum element in the heap
// and store the number of key comparisons made in the
// location pointed to by count_ptr.
int extract_max(heap_t *heap, int *count_ptr) {
	int max = heap->arr[0];
	swap(&heap->arr[0], &heap->arr[heap->size-1]);
	heap->size--;
	*count_ptr = heapify(heap);
	return max;
}

// Searches for the element key in the heap
// Returns the element if found, else -1
int search(const heap_t *heap, int key, int *count_ptr) {
	int element = -1;
	for (int i = 0; i < heap->size; i++)
	{
		(*count_ptr)++;
		if(heap->arr[i] == key)
			element = key;
	}

	return element;
	
}

// Returns the maximum value of the element in the heap
// and store the number of key comparisons made in the
// location pointed to by count_ptr.
int find_max(const heap_t *heap, int *count_ptr) {
	(*count_ptr)++;
	return heap->arr[0];
}

// Returns the minimum value in the heap
int find_min(const heap_t *heap, int *count_ptr) {
	int min = heap->arr[heap->size/2];
	for(int i = heap->size/2; i < heap->size; i++){
		(*count_ptr)++;	
		if(heap->arr[i] < min){
			min = heap->arr[i];
		}
	}
	return min;
}

// Clears the heap for reuse
void clear_heap(heap_t *heap) {
	free(heap->arr);
	heap->size = 0;
    heap->arr = (int*)malloc(heap->max_size*sizeof(int));
}

// Frees all resources acquired to initialize heap
void free_heap(heap_t *heap) {
	free(heap->arr);
	heap->arr = NULL;
}
