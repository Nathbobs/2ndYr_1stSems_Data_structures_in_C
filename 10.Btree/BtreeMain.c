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

BNodePtr Insert(BNodePtr root, int key); //edited this area "removed pointer and void"

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
                    Insert(root, key); //edited this area
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

BNodePtr splitNode (BNodePtr x, int i, BNodePtr y) {//splits a node y and inserts it into node x at index i
    int j;
    BNodePtr z = CreateTree(x->order);//A new node z is created with the same order as the parent node x.
    int T = x->order;
    z->size = T - 1; //The size of the new node z is set to T - 1, where T is the order of the parent node.

    for (j = 0; j < T - 1; j++){
        z->key[j] = y->key[j+T];
    }

    if (y->is_leaf == 0)
    {
        for (j = 0; j < T; j++){
            z->child[j] = y->child[j+T];
        }
    }

    y->size = T - 1;

    for (j = x->size; j >= i+1; j--){
        x->child[j+1] = x->child[j];
    }

    x->child[i+1] = z;


    for (j = x->size-1; j >= i; j--){
        x->key[j+1] = x->key[j];
    }

    x->key[i] = y->key[T-1];


    x->size++;


   return x;
}
BNodePtr InsertNonFull(BNodePtr root, int a){// inserts a new key a into a non-full node root.
   int i = root->size-1;
//    root = a;
   
    if(root->is_leaf){
        while(i >= 0 && root->key[i]> a){
            root->key[i+1] = root->key[i];
            i--;
        }
        root->key[i+1] = a;
        root->size++;
    }
    else
    {
        while (i >= 0 && root->key[i] > a){
            i--;
        }

        i = i + 1;

        if (root->child[i]->size == 2*root->order-1){
            root = splitNode(root, i, root->child[i]);

            if (a > root->key[i]){
                i = i + 1;
            }
        }

        root->child[i] = InsertNonFull(root->child[i], a);
    }

    return root;
}

/*
Create new BTree with given order
order: order of BTree (order >= 2)
return: 
        the pointer of new BTree
 */
BNodePtr CreateTree(int order){//creates a new BTree with a given order, allocates memory for a BNode struct, initializes its values, and returns a pointer to the new BNode.
    BNodePtr b = (BNodePtr)malloc(sizeof(struct BNode));
    b->is_leaf = 1;
    b->size = 0;
    b->order = order;
    b->child = (BNodePtr*)malloc(2*order * sizeof(BNodePtr));//dynamically allocates memory for an array of BNodePtr pointers of size 2*order and assigns it to b->child.
    b->key = (int*)malloc((2*order-1) * sizeof(int));
    for(int i = 0; i< order+1; i++){
        b->child[i] = NULL;// initializes all pointers in b->child to NULL.
    }
    return b;
}

/*
Insert the key value into BTree 
key: the key value in BTree node 
*/
BNodePtr Insert(BNodePtr root, int key){//inserts a key value into the BTree with the root node given by root. 
    BNodePtr r = root;
    if(r->size == 2*r->order -1){
        BNodePtr s = CreateTree(root->order);
        s->is_leaf = 0;
        s->child[0] = r;
        s= splitNode(s, 0, r);
        s = InsertNonFull(s, key);
        return s;
    }
    else{
        return InsertNonFull(r, key);
    }
}

/*
Find node that has key in BTree
key: the key value in BTree node 
*/
int Find(BNodePtr root, int key){
    
    BNodePtr high = root;
    int flag = 1;
    while(flag){
        int pos;
        for(pos = 0; pos < high->size; pos++){
            if(key == high->key[pos]) return 1;//If the key is found, 1 is returned.
            else if(key < high->key[pos]) break;
        }
        if(high->is_leaf) break;//If the current node is not a leaf, high is updated to be the child node at the corresponding position and the loop continues.
        high = high->child[pos];
    }
    return 0;
}

/* 
Print Tree, inorder traversal 
*/
void PrintTree(BNodePtr root){//prints the keys of all nodes in the BTree with the root node given by root in ascending order. 
    int i = 0;
    
    if(!root ){
        fprintf(fout, "Print Error: tree is empty!.\n");
        return; //Check if the root is NULL. If it is, print an error message and return from the function.
    }
     while(root->key[i]!=0){
      fprintf(fout,"%d ", root->key[i]);
      i++;//Traverse the root node and print the keys in ascending order using a while loop.
     }

   while(root->key[i]!=0){
      if (root->is_leaf == 0) {
         PrintTree(root->child[i]);
      }
      i++;//Traverse the child nodes recursively if the root is not a leaf node.
   }
}

/*
Free memory, delete a BTree completely 
*/
void DeleteTree(BNodePtr root){//deletes the entire BTree with the root node given by root.
     int i;
     for (i = 0; i < root->size; i++) {
        free(root->child[i]);
     }

   for (i = 0; i <= root->size; i++) {
      if (root->is_leaf == 0) {
         DeleteTree(root->child[i]);
      }
   }
 free(root);
}
