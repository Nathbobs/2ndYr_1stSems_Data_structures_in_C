#include<stdio.h>
#include<stdlib.h>

FILE* fin;
FILE* fout;

typedef struct Arrays Array;

struct Arrays{
    int size;
    int* values;
}Arrays;

Array* CreateArray(int size){
    Array* vec = (Array*)malloc(sizeof(Arrays));
    vec->values = (int*)malloc(size* sizeof (int));
    vec->size = size;

    return vec;
}

void PrintArray(Array* array, int left, int right){
    char c = '-';
    for(int j = 0; j < left; j++)
        fprintf(fout,"%-3s","-");
    for(int i = left; i <= right; i++)
        fprintf(fout,"%-3d", array->values[i]);
    for(int k = right+1; k < array->size; k++)
        fprintf(fout,"%-3s", "-");
    fprintf(fout,"\n");
}

void swap(int* a, int* b){
    int t = *a;
    *a = *b;
    *b = t;
}

int Partition(Array* array, int left, int right){
   int pivot = array->values[right];
   int i = left-1;
   int j = right;
   int flag = 1;
 
    fprintf(fout,"Left = %d, Right = %d, Pivot = %d\n", left, right, pivot);
      
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
}

void QuickSort(Array* array, int left, int right){
    int pivot; 
   
    if(left<right){
        pivot = Partition(array, left, right);
        QuickSort(array, left, pivot-1);
        QuickSort(array, pivot+1, right);
    }
}



void DeleteArray(Array* array){
    free(array->values);
    free(array);
}

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
    
    QuickSort(array, 0, size-1);
    
    fprintf(fout,"\nSorting Result:\n");
    PrintArray(array, 0, size-1);
    
    DeleteArray(array);
    
    return 0;
}