#include<stdio.h>
#include<stdlib.h>
#define INF 1e9


FILE *fin;
FILE *fout;

typedef struct HeapStruct{
	int Capacity;
	int Size;
	int *Elements;
}Heap;

Heap* CreateHeap(int heapSize);
int Insert(Heap *heap, int value);
int Find(Heap *heap, int value);
int DeleteMax(Heap* heap);
int* GetElements(Heap* heap);
int IsFull(Heap *heap);
int IsEmpty(Heap *heap);
int Size(Heap *heap);

void swap(int* a, int* b){
	int t = *a;
	*a = *b;
	*b = t;
}

int main(int argc, char* argv[]){
	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");

	char cv;
	Heap* maxHeap;
	int heapSize, key, max_element;
	int ret;
	int* elements;
	while(!feof(fin)){
		fscanf(fin, "%c", &cv);
		switch(cv){
			case 'n':
				fscanf(fin, "%d", &heapSize);
				maxHeap = CreateHeap(heapSize);
				break;
			case 'i':
				fscanf(fin, "%d", &key);
				ret = Insert(maxHeap, key);
				if(ret == 0) fprintf(fout, "insert %d\n", key);
				else if(ret == 1) fprintf(fout, "insert error : heap is full\n");
				else if(ret == 2) fprintf(fout, "insert error : %d is already in the heap\n", key);
				else {
					fprintf(fout, "error: unknown return type\n");
					return -1;
				} 

				break;
			case 'd':
				max_element = DeleteMax(maxHeap);
				if(max_element == 0){
					fprintf(fout, "delete error : heap is empty\n");

				}else if(max_element > 0){
					fprintf(fout, "max element : %d deleted\n", max_element);
				}
				break;
			case 'p':
				if(IsEmpty(maxHeap)){
					fprintf(fout, "print error : heap is empty\n");
				}else{
					elements = GetElements(maxHeap);
					int size = Size(maxHeap);
					for(int i = 0; elements[i] > -1 && i < size; i++){
						fprintf(fout, "%d ", elements[i]);
					}
					fprintf(fout, "\n");
					free(elements);
				}
				break;
			case 'f':
				fscanf(fin, "%d", &key);
				if(Find(maxHeap, key)) fprintf(fout, "%d is in the heap\n", key);
				else fprintf(fout, "finding error : %d is not in the heap\n", key);
				break;
		}
	}

	return 0;
}

/*
Create new heap with given heapSize
Element[0] should save INF
heapSize: positive integer
return:
	the pointer of new heap  
*/
Heap* CreateHeap(int heapSize){
    Heap* heap = (Heap*) malloc(sizeof(Heap));
    heap->Capacity = heapSize;
    heap->Size = 0;
    heap->Elements = (int*) malloc((heapSize + 1) * sizeof(int));
    heap->Elements[0] = INF; // Sentinel value
    return heap;
}

/*
Insert the value into Heap
value: positive integer
return:
	0 , success
	1 , heap is full
	2 , duplicated
*/
int Insert(Heap *heap, int value){
    if (IsFull(heap)) return 1; // Heap is full

    // Check if value already exists in heap
    for (int i = 1; i <= heap->Size; i++) {
        if (heap->Elements[i] == value) {
            return 2; // Value is already in heap
        }
    }

    // Insert value at the end of the heap
    heap->Size++;
    heap->Elements[heap->Size] = value;

    // Percolate up to restore heap order
    int i = heap->Size;
    while (heap->Elements[i] > heap->Elements[i / 2]) {
        swap(&heap->Elements[i], &heap->Elements[i / 2]);
        i = i / 2;
    }

    return 0; // Insertion successful
}

/*
Find the value in Heap
return:
	1, success
	0, fail  
*/
int Find(Heap* heap, int value) {
    // Linear search for value in heap
    for (int i = 1; i <= heap->Size; i++) {
        if (heap->Elements[i] == value) {
            return 1; // value found
        }
    }
    return 0; // value not found
}


/*
Delete the maximum value in Heap
return:
	Max value, success
	0, heap is empty  
*/
int DeleteMax(Heap* heap) {
    if (IsEmpty(heap)) {
        return 0; // heap is empty
    }
    
    int max = heap->Elements[1]; // save the maximum element
    heap->Elements[1] = heap->Elements[heap->Size]; // move last element to root
    heap->Size--; // decrement heap size
    
    // Percolate down to restore heap property
    int i = 1;
    while (i * 2 <= heap->Size) { // while i has at least one child
        int child = i * 2;
        if (child + 1 <= heap->Size && heap->Elements[child + 1] > heap->Elements[child]) {
            child++; // choose the larger child
        }
        if (heap->Elements[i] < heap->Elements[child]) {
            swap(&heap->Elements[i], &heap->Elements[child]);
            i = child;
        } else {
            break;
        }
    }
    
    return max; // return the maximum element
}


/*
Return an array of copied elements from the heap
The length of the returned array should be the same as the size of the heap
The order of the returned array should be the same as the order of heap->Elements  
If heap is empty, return NULL
***WARNING***
Do not just return heap->Elements
You must copy the elements to another allocated array
*/
int* GetElements(Heap* heap){
    if(IsEmpty(heap)){
        return NULL;
    }
    int* elements = (int*)malloc(sizeof(int) * heap->Size);
    if(elements == NULL){
        fprintf(stderr, "Failed to allocate memory for elements array\n");
        exit(1);
    }
    int i;
    for(i=0; i<heap->Size; i++){
        elements[i] = heap->Elements[i+1];// the order of elements in the returned array is the same as the order of elements in the "heap->Elements" array
    }
    elements[i] = -1; // add sentinel value
    return elements;
}


/*
check heap is full
return:
	1, heap is full
	0, heap is not full
*/
int IsFull(Heap* heap){
    return heap->Size == heap->Capacity - 1;//if the heap is full, 1 is returned. else 0.
}


/*
check heap is empty
return:
	1, heap is empty
	0, heap is not empty
*/
int IsEmpty(Heap *heap){//if the heap is empty, 1 is returned. else 0.
    return heap->Size == 0;
}


/*
get size of heap
return:
	size of heap
*/
int Size(Heap *heap){// returns the value of the size field of the heap data
    return heap->Size;
}




