#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE *fin;
FILE *fout;

typedef int ElementType;
typedef ElementType List;
typedef struct HashTbl* HashTable;

typedef struct HashTbl{
	int TableSize;
	List *TheLists;
}HashTbl;

HashTable createTable(int TableSize);
void Insert(HashTable H, ElementType Key, int solution);
void Delete(HashTable H, ElementType Key, int solution);
int Find(HashTable H, ElementType Key, int solution);
void printTable(HashTable H);
void deleteTable(HashTable H);

int main(int argc, char *argv[]){
	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");


	char solution_str[20];
	int solution, TableSize;

	fscanf(fin, "%s", solution_str);
	if(!strcmp(solution_str, "linear"))
		solution = 1;
	else if(!strcmp(solution_str, "quadratic"))
		solution = 2;
	else{
		fprintf(fout, "Error: Invalid hashing solution!");
		return 0;
	}
	
	fscanf(fin, "%d", &TableSize);

	HashTable H = createTable(TableSize);

	char cv;
	int key;
	while(!feof(fin)){
		fscanf(fin, "%c", &cv);
		switch(cv){
			case 'i':
				fscanf(fin, "%d", &key);
				Insert(H, key, solution);
				break;

			case 'f':
				fscanf(fin, "%d", &key);
				int result = Find(H, key, solution);
				if(result)
					fprintf(fout, "%d is in the table\n", key);
				else
					fprintf(fout, "%d is not in the table\n", key);
				break;

			case 'd':
				fscanf(fin, "%d", &key);
				Delete(H, key, solution);
				break;

			case 'p':
				printTable(H);
				break;
		}
	}

	deleteTable(H);

	return 0;
}

/*
Create new Hash Table with given TableSize
reture:
	the pointer of new hash table
*/
HashTable createTable(int TableSize){
    HashTable h = (HashTbl*)malloc(sizeof(HashTbl));
    h->TableSize = TableSize; // Set the TableSize
    h->TheLists = (int*)malloc(TableSize* sizeof(int)); // Allocate memory for the array of lists in the hash table
    for(int i = 0; i < TableSize; i++){
        h->TheLists[i] = 0;
    }
    return h;
}

/*
Insert the key in hash table with given solution (linear or quadratic).
print out : 
	Successful insertion : "insert %d into address %d\n"
	When inserting duplicate key value : "insertion error : %d already exists at address %d\n"
	When HashTable is full : "insertion error : table is full\n"
*/
void Insert(HashTable H, ElementType Key, int solution){
    int hash; 
    int exists = Find(H, Key, solution);
    // Calculate the hash value for the key
    hash = Key % H->TableSize;
    if(exists) // Key already exists in the hash table
        fprintf(fout, "insertion error: %d already exists at address %d\n", Key, exists);
    else if(H->TheLists[hash]){
        if(solution == 1){ // Linear probing
            int i = 1;
            while(i){
                if(H->TheLists[hash+i]) i++;
                else{ 
                    if(hash+i < H->TableSize){
                        H->TheLists[hash+i] = Key; 
                        fprintf(fout, "insert %d into address %d\n", Key, hash+i);}
                    else fprintf(fout, "insertion error: table is full\n");
                    i =0;
                    
                }
            }
        }
        else if(solution == 2){
            int i = 1;
            while(i){
                if(H->TheLists[hash+(i*i)]) i++;
                else{ 
                    if(hash+(i*i) <= H->TableSize){
                        H->TheLists[hash+(i*i)] = Key; 
                        fprintf(fout, "insert %d into address %d\n", Key, hash+(i*i));}
                    else fprintf(fout, "insertion Error: table is full\n");
                    i =0;
                }
            }
        }
    }
    else{
        H->TheLists[hash] = Key; // Insert the key at the calculated hash value
       
        fprintf(fout,"insert %d into address %d\n", Key, hash);
    }
}
/*
Delete the key in hash table with given solution (linear or quadratic).
print out : 	
	when key value is found :  "delete %d\n"
	when key value does not exist : %d is not in the table\n"
*/
void Delete(HashTable H, ElementType Key, int solution){
    int pos = Find(H, Key, solution);
    if(pos){
        H->TheLists[pos] = 0; // Key found, delete it from the hash table
        fprintf(fout,"delete %d\n", Key);
        
    }
    else fprintf(fout, "deletion error: %d is not in the table\n", Key);// Key not found in the hash table
}

/*
Find the Key from hash table with given solution (linear or quadratic).
return:
	0 : when the key is not found
	1 : when the key is found
*/
int Find(HashTable H, ElementType Key, int solution){
    int hash = Key % H->TableSize;
    if(H->TheLists[hash] != Key){
          if(solution == 1){ // Collision occurred, perform linear or quadratic probing
             // Linear probing
            int i = 1;
            while(i){
                if(H->TheLists[hash+i] != Key && hash+i < H->TableSize) i++;
                else if (H->TheLists[hash+i] != Key && hash+i >= H->TableSize) return 0;
                else return hash+i;
                }
            }
            else if(solution == 2){ // Quadratic probing
                int i = 1;
                while(i){
                    if(H->TheLists[hash+i] != Key && hash+(i*i) < H->TableSize) i++;
                    else if (H->TheLists[hash+i] != Key && hash+(i*i) >= H->TableSize) return 0;
                    else return hash+(i*i);
                }
            }
        }
    else if(H->TheLists[hash] == Key) return(hash);
    
}
/*
Print all values of Hash Table
print out the key values ​​in the Hash Table in the order of index in the Hash Table.
	empty Hash Table print : "0 "
	Non empty Hash Table print : "%d "
*/
void printTable(HashTable H){ // Prints all the values in the hash table.
    for(int i = 0; i < H->TableSize; i++)
        fprintf(fout, "%d ", H->TheLists[i]);
    fprintf(fout, "\n");
}
/*
delete Table 
*/
void deleteTable(HashTable H){ //Deletes the given Key from the hash table using the specified solution (linear or quadratic)
    free(H->TheLists);
    free(H);
}
