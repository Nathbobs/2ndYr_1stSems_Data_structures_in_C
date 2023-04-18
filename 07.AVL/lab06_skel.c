#include<stdio.h>
#include<stdlib.h>

FILE *fin;
FILE *fout;

struct AVLNode;
typedef struct AVLNode *Position;
typedef struct AVLNode *AVLTree;
typedef int ElementType;

typedef struct AVLNode{
	ElementType element;
	AVLTree left, right;
	int height;
}AVLNode;


/*
Insert the value X in AVLTree T
return:
	pointer of root
print out:
	"insertion error : X is already in the tree!\n" , X is already in T
*/
AVLTree Insert(ElementType X, AVLTree T){}

/*
Delete the value X in AVLTree T
return:
	pointer of root
print out:
	"deletion error : X is not in the tree!\n", X is not in T
*/
AVLTree Delete(ElementType X, AVLTree T){}
/*
Pre order Traversal
*/
void PrintPreorder(AVLTree T){}
/*
Delete Tree
free allocated memory
*/
void DeleteTree(AVLTree T){}
/*
Rotation functions for AVLTree
*/
Position SingleRotateWithLeft(Position node){}
Position SingleRotateWithRight(Position node){}
Position DoubleRotateWithLeft(Position node){}
Position DoubleRotateWithRight(Position node){}

int main(int argc, char *argv[]){
	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");
	AVLTree Tree = NULL;
	char cv;
	int key;

	int i=0;

	while(!feof(fin)){
		printf("%d: ", ++i);
		fscanf(fin, "%c", &cv);
		switch(cv){
			case 'i':
				fscanf(fin, "%d\n", &key);
				Tree = Insert(key, Tree);
				break;
			case 'd':
				fscanf(fin, "%d\n", &key);
				Tree = Delete(key, Tree);
				break;
		}
		PrintPreorder(Tree);
		fprintf(fout, "\n");
		printf("\n");
	}

	DeleteTree(Tree);
	fclose(fin);
	fclose(fout);
	return 0;
}
