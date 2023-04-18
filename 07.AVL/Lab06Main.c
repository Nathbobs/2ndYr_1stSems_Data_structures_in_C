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

// int max(int a, int b){
//     return (a > b) ? a : b;
// }

int Height(Position P){ //function to return the height of the leaves when necessary
    if (P == NULL)
        return -1;
    else
        return P->height;
}

Position SingleRotationWithLeft(Position node){ //performing singe rotation to left
    int max;
    Position tmp;
    //swaping the nodes
    tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;
    //adjusting height values
    if (Height(node->left) > Height(node->right)) max = Height(node->left);
    else max = Height(node->right);
    
    node->height = max+1;
    
    if (Height(tmp->left) > node->height) max = Height(tmp->left);
    else max = node->height;
    
    tmp->height = max+1;
    
    return tmp;
}
Position SingleRotationWithRight(Position node){ //performing single rotation to right
    int max;
    Position tmp;
    //swaping the nodes 
    tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;
    //adjusting height values
    if (Height(node->left) > Height(node->right)) max = Height(node->left);
    else max = Height(node->right);
    
    node->height = max+1;
    
    if (Height(tmp->right) > node->height) max = Height(tmp->right);
    else max = node->height;
    
    tmp->height = max+1;
    
    return tmp;
}
Position DoubleRotateWithLeft(Position node){ //rotate Left-Right
    node->left = SingleRotationWithRight(node->left);
    return SingleRotationWithLeft(node);
}
Position DoubleRotateWithRight(Position node){ //rotate Right-Left
    node->right = SingleRotationWithLeft(node->right);
    return SingleRotationWithRight(node);
}


AVLTree Insert(ElementType X, AVLTree T){
    if (T == NULL){
        T = (AVLTree)malloc(sizeof(AVLNode));
        if (T == NULL){
            printf("Memory allocation error\n");
            exit(1);
        }
        else{
            T->element = X;
            T->height = 0;
            T->left = T->right = NULL;
        }
    }
    else if (X < T->element){
        T->left = Insert(X, T->left);
        if (height(T->left) - height(T->right) == 2){
            if (X < T->left->element)
                T = SingleRotateWithLeft(T);
            else
                T = DoubleRotateWithLeft(T);
        }
    }
    else if (X > T->element){
        T->right = Insert(X, T->right);
        if (height(T->right) - height(T->left) == 2){
            if (X > T->right->element)
                T = SingleRotateWithRight(T);
            else
                T = DoubleRotateWithRight(T);
        }
    }
    else{
        fprintf(fout, "insertion error : %d is already in the tree!\n", X);
    }

    T->height = max(height(T->left), height(T->right)) + 1;
    return T;
}

/*
Delete the value X in AVLTree T
return:
	pointer of root
print out:
	"deletion error : X is not in the tree!\n", X is not in T
*/
AVLTree Delete(ElementType X, AVLTree T){
    if (T == NULL){
        fprintf(fout, "deletion error : %d is not in the tree!\n", X);
        return T;
    }

    if (X < T->element){
        T->left = Delete(X, T->left);
        if (height(T->right) - height(T->left) == 2){
            if (height(T->right->right) >= height(T->right->left))
                T = SingleRotateWithRight(T);
            else
                T = DoubleRotateWithRight(T);
        }
    }
    else if (X > T->element){
        T->right = Delete(X, T->right);
        if (height(T->left) - height(T->right) == 2){
            if (height(T->left->left) >= height(T->left->right))
                T = SingleRotateWithLeft(T);
            else
                T = DoubleRotateWithLeft(T);
        }
    }
    else{
        if (T->left && T->right){
            Position tmp = T->right;
            while (tmp->left)
                tmp = tmp->left;
            T->element = tmp->element;
            T->right = Delete(tmp->element, T->right);
        }
        else{
            Position tmp = T;
            if (T->left == NULL)
                T = T->right;
            else
                T = T->left;
            free(tmp);
        }
    }

    if (T != NULL)
        T->height = max(height(T->left), height(T->right)) + 1;

    return T;
}

/*
Pre order Traversal
*/
/*
Pre-order Traversal of AVLTree T
*/
void PrintPreorder(AVLTree T){
    if (T == NULL)
        return;
    fprintf(fout, "%d ", T->element); // Print the element of the current node
    PrintPreorder(T->left); // Recursively print the left subtree
    PrintPreorder(T->right); // Recursively print the right subtree
}

/*
Delete Tree
free allocated memory
*/
/*
Delete AVLTree T and free allocated memory
*/
void DeleteTree(AVLTree T){
    if (T == NULL)
        return;

    DeleteTree(T->left); // Recursively delete the left subtree
    DeleteTree(T->right); // Recursively delete the right subtree
    free(T); // Free the memory occupied by the current node
}

/*
Rotation functions for AVLTree
*/


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
