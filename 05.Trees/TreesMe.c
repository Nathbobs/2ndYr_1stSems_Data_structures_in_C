#include<stdio.h>
#include<stdlib.h>

FILE *fin;
FILE *fout;

#define FROMPARENT 0
#define FROMTHREAD 1

typedef struct ThreadedTree* ThreadedPtr;
typedef int ElementType;

struct ThreadedTree {
	int left_thread; // flag if ptr is thread, 1, if it is a thread or 0, if it points to a child node
	ThreadedPtr left_child;
	ElementType data;
	ThreadedPtr right_child;
	int right_thread; // flag if ptr is thread, 1, if it is a thread or 0, if it points to a child node
}ThreadedTree;

/*
Create a root of new Threaded Tree
Root data should be -1
return:
	the pointer of new Threaded Tree
*/
ThreadedPtr CreateTree(){
    ThreadedPtr tree = NULL;
    tree = (ThreadedPtr)malloc(sizeof(ThreadedTree));
    if(tree == NULL){
        fprintf(fout, "no space");
        return NULL;
    }
    tree-> data = -1;
    tree->left_thread = 1;
   // tree->left_child = tree;
    tree->right_thread = 1;
  //  tree->right_child = tree;
    return tree;

}


/*
Insert the key value "data" in Threaded Tree
root : Pointer to the root node of Threaded Tree
root_idx : Index of the root node of Threaded Tree, means the first node to find the insertion position
data : data key value of the node to be newly inserted,
idx : The index of the node to be newly inserted, 0 means root index
return :
	1, the insertion succeeds
	0, the insertion fails.
*/
int Insert(ThreadedPtr root, int root_idx, ElementType data, int idx){
    ThreadedPtr ptr = root;
    ThreadedPtr par = NULL;
    
    if(idx >= 100) return 0;
    
    while(ptr!=NULL){
        //if key already exists
        if(data == ptr->data) return 0;
        else if(ptr->data == -1) ptr->data = data;
        
        par = ptr; //actualizing parent pointer
       // printf("par data %d\n", par->data);
        
        //left subtree check
        if(data < ptr->data){
            if(ptr->left_thread == 0) ptr = ptr->left_child;
        }
        //right subtree
        else{
            if(ptr->right_thread == 0) ptr = ptr->right_child;
        }
        
        //creating new node
        ThreadedPtr tmp = (ThreadedPtr)malloc(sizeof(ThreadedTree));
        tmp->left_thread = 1;
        tmp->right_thread = 1;
        tmp->data = data;
        //printf("tmp %d\n", tmp->data);
        
         if(data < (par->data)){
            tmp->left_child = par->left_child;
            tmp->right_child = par;
            par->left_thread = 0;
            par->left_child = tmp;
           // printf("passei2 e inseri %d\n", tmp->data);
        }
        else{
            tmp->left_child = par;
            tmp->right_child = par->right_child;
            par->right_thread = 0;
            par->right_child = tmp;
           // printf("passei3 e inseri %d\n", tmp->data);
        }
        return 1;
    }

	
}

/*
In Order Traversal
Implementing in a recursive form is prohibited.
When printing out, the interval between each key is one space
print out:
	"inorder traversal : data1 data2 data3" (When there are 3 data, except root node)

*/
void printInorder(ThreadedPtr tree){
    ThreadedPtr tmp = tree;
    
    fprintf(fout, "Inorder Transversal :");
    //reach leftmost node
    while(tmp){

        if(tmp->left_thread == 0){
            tmp = tmp->left_child;
        }
        else{
            fprintf(fout, "%d ", tmp->data);
            tmp = tmp->right_child;
        } 
    }
    fprintf(fout, "\n");
}

/*
Delete the Tree
*/
void DeleteTree(ThreadedPtr root){
    if(root == NULL) return;
    free(root);
}

int main(int argc, char *argv[]){
	fin=fopen(argv[1], "r");
	fout=fopen(argv[2], "w");

	ThreadedPtr root = CreateTree();

	int NUM_NODES;
	fscanf(fin, "%d", &NUM_NODES);

	int root_idx=0, idx=0;

	while(++idx <= NUM_NODES){
		ElementType data;
		fscanf(fin, "%d", &data);
		
		if(Insert(root, root_idx, data, idx) == 0){
			fprintf(fout, "Insertion failed!\n");
			return 0;
		}
	}

	printInorder(root);
	DeleteTree(root);
	
	
	fclose(fin);
	fclose(fout);

	return 0;
}
