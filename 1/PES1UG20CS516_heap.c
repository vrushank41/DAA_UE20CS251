// Name:Vrushank G
// SRN:PES1UG20CS516
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

// Initialise heap
// Set heap size to 0
// Set heap max_size to paramter max_size
// Allocate memory of max_size to the array
void init_heap(heap_t *heap, int max_size) 
{
    heap->size=0;
    heap->max_size=max_size;
    heap->arr=(int*)malloc(max_size*sizeof(int));
}
static int heapfunc(heap_t *heap)
{
    int count=0;
	int p;int c; int ele;
	for(int i=1;i<heap->size;++i)
	{
		c=i;
		p=(c-1)/2;
		ele=heap->arr[i];
		while(c>0 && heap->arr[p]<ele)
		{
			count++;
			heap->arr[c]=heap->arr[p];
			c=p;
			p=(c-1)/2;
	
		}
		heap->arr[c]=ele;	
	}
    return count;
}
// Insert element "key" to heap "heap"
// and store the number of key comparisons made in the
// location pointed to by count_ptr.
void insert(heap_t *heap, int key, int *count_ptr) 
{
    heap->arr[heap->size]=key;
    heap->size++;
    *count_ptr=heapfunc(heap);
}

// *Removes and Returns* the maximum element in the heap
// and store the number of key comparisons made in the
// location pointed to by count_ptr.
static void exchange(int *first,int *last)
{
	int temp=*first;
	*first=*last;
	*last=temp;
}
int extract_max(heap_t *heap, int *count_ptr) 
{
	int max=heap->arr[0];
	exchange(&heap->arr[0],&heap->arr[heap->size-1]);
	heap->size--;
	*count_ptr=heapfunc(heap);
	return max;
}

// Searches for the element key in the heap
// Returns the element if found, else -1
int search(const heap_t *heap, int key, int *count_ptr) 
{
	int ele=-1;
	for(int i=0;i<heap->size;i++)
	{
		++(*count_ptr);
		if(heap->arr[i]==key)
			ele=key;
	}
	return ele;
}

// Returns the maximum value of the element in the heap
// and store the number of key comparisons made in the
// location pointed to by count_ptr.
int find_max(const heap_t *heap, int *count_ptr)
{
	(*count_ptr)++;
	return heap->arr[0];
}

// Returns the minimum value in the heap
int find_min(const heap_t *heap, int *count_ptr) 
{
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
void clear_heap(heap_t *heap) 
{
	free(heap->arr);
	heap->size = 0;
    heap->arr = (int*)malloc(heap->max_size*sizeof(int));
}

// Frees all resources acquired to initialize heap
void free_heap(heap_t *heap) 
{
	free(heap->arr);
	heap->arr = NULL;
}
