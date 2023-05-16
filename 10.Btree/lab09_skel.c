#include<stdio.h>
#include<stdlib.h>

FILE *fin;
FILE *fout;

typedef struct BNode* BNodePtr;

struct BNode{
    int order;
    int size;           /* number of children */
    BNodePtr *child;    /* children pointers */
    int *key;           /* keys */
    int is_leaf;
}BNode;

BNodePtr CreateTree(int order);

void Insert(BNodePtr *root, int key);

int Find(BNodePtr root, int key);

void PrintTree(BNodePtr root);

void DeleteTree(BNodePtr root);

int main(int argc, char* argv[]){
    fin = fopen(argv[1], "r");
    fout = fopen(argv[2], "w");

    int order;
    fscanf(fin, "%d", &order);
    BNodePtr root = CreateTree(order);

    char cv;
    int key;
    while(!feof(fin)){
        fscanf(fin, "%c", &cv);
        switch(cv){
            case 'i':
                fscanf(fin, "%d", &key);
                if(Find(root, key))
                    fprintf(fout, "insert error : key %d is already in the tree!\n", key);
                else
                    Insert(&root, key);
                break;
            case 'f':
                fscanf(fin, "%d", &key);
                if(Find(root, key))
                    fprintf(fout, "key %d found\n", key);
                else
                    fprintf(fout, "finding error : key %d is not in the tree!\n", key);
                break;
            case 'p':
                if (root->size == 1)
                    fprintf(fout, "print error : tree is empty!");
                else
                    PrintTree(root);
                fprintf(fout, "\n");
                break;
        }
    }
   
    DeleteTree(root);
    fclose(fin);
    fclose(fout);

    return 0;
}

/*
Create new BTree with given order
order: order of BTree (order >= 2)
return: 
        the pointer of new BTree
 */
BNodePtr CreateTree(int order){

}

/*
Insert the key value into BTree 
key: the key value in BTree node 
*/
void Insert(BNodePtr *root, int key){
    
}

/*
Find node that has key in BTree
key: the key value in BTree node 
*/
int Find(BNodePtr root, int key){

}

/* 
Print Tree, inorder traversal 
*/
void PrintTree(BNodePtr root){

}

/*
Free memory, delete a BTree completely 
*/
void DeleteTree(BNodePtr root){

}
