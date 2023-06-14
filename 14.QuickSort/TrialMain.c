#include<stdio.h>
#include<stdlib.h>

FILE* fin;
FILE* fout;

typedef struct Array Array;

struct Array{
    int size;
    int* values;
};

Array* CreateArray(int size);
void QuickSort(Array* array, int left, int right);
int Partition(Array* array, int left, int right);
void PrintArray(Array* array, int left, int right);
void DeleteArray(Array* array);
void swap(int* a, int* b);

int main(int argc, char *argv[]){
	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");

    int size, i;
    Array* array;

    fscanf(fin, "%d", &size);
    array = CreateArray(size);
    for(i = 0; i < size; i++){
        fscanf(fin, "%d", &array->values[i]);
    }

    QuickSort(array, 0, size - 1);

    fprintf(fout, "\nsorting result :\n");
    PrintArray(array, 0, size - 1);

    DeleteArray(array);


	return 0;
}

/*
Create new array 
input : size of the number to be sorted
output : the pointer of array
*/
Array* CreateArray(int size){ //creates an array with the input size
    Array* vec = (Array*)malloc(sizeof(Array));
    vec->values = (int*)malloc(size* sizeof (int));
    vec->size = size;

    return vec; // returns a pointer to the created array
} //SOLVED

/*
Quick sort
*/
void QuickSort(Array* array, int left, int right){ //Performs a quick sort on the interval from left to right
    int pivot; 
   
    if(left<right){
        pivot = Partition(array, left, right);
        QuickSort(array, left, pivot-1);
        QuickSort(array, pivot+1, right); //recursively performs the quicksort algorithm on the array
    }
} //SOLVED

/*
Divide into 2 sub-lists based on pivot.
+ Select right-most data as pivot
+ Print left, right, pivot index at first
+ Print array values for every swap -> Printing array values should be implemented in a PrintArray function
Print format : 
    1. "left : %d, right : %d, pivot : %d\n"
    2. refered on PrintArray function
return:
    pivot index
*/
int Partition(Array* array, int left, int right){//sets the pivot and obtains the proper index of the pivot through the swapping
   int pivot = array->values[right];
   int i = left-1;
   int j = right;
   int flag = 1;
 
    fprintf(fout,"left : %d, right : %d, pivot : %d\n", left, right, pivot);
      
   for(;;){
       PrintArray(array, left, right); 
       while(array->values[--j] >= pivot);
       while(array->values[++i] < pivot);
       if(i < j){
           swap(&array->values[i], &array->values[j]);
          // PrintArray(array, left, right);
        }
        else{
            swap(&array->values[i], &array->values[right]);
            if(i!=right)
            PrintArray(array, left, right); 
            return i;
        }
   }
} //SOLVED


/*
Print array values 
Print format :
    “%-3s” : out of bound and should be filled with "-" charater
    “%-3d” : array values to be printed
*/
void PrintArray(Array* array, int left, int right){//Prints all values of the array on the interval from left to right
    char c = '-';
    for(int j = 0; j < left; j++)
        fprintf(fout,"%-3s","-");
    for(int i = left; i <= right; i++)
        fprintf(fout,"%-3d", array->values[i]);
    for(int k = right+1; k < array->size; k++)
        fprintf(fout,"%-3s", "-");
    fprintf(fout,"\n");
} //SOLVED

/*
DeleteArray
*/
void DeleteArray(Array* array){// deletes an array
    free(array->values);
    free(array);
} //SOLVED

/*
Swap values
*/
void swap(int* a, int* b){ //swaps two values in the array
    int t = *a;
    *a = *b;
    *b = t;
} //SOLVED
