#include<stdio.h>
#include<stdlib.h>

FILE *fin;
FILE *fout;

typedef struct BST* Tree;
typedef struct BST{
	int value;
	struct BST* left;
	struct BST* right;
}BST;

Tree insertNode(Tree root, int key);
Tree deleteNode(Tree root, int key);
int findNode(Tree root, int key);
void printInorder(Tree root);
void deleteTree(Tree root);

void main(int argc, char* argv[]){
	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");
	char cv;
	int key;

	Tree root = NULL;

	while(!feof(fin)){
		fscanf(fin, "%c", &cv);
		switch(cv){
			case 'i':
				fscanf(fin, "%d", &key);
				if(!findNode(root, key))
					root = insertNode(root, key);
				else
					fprintf(fout, "insertion error: %d is already in the tree\n", key);
				break;
			case 'f':
				fscanf(fin,"%d",&key);
				if(findNode(root, key))
					fprintf(fout, "%d is in the tree\n", key);
				else
					fprintf(fout, "finding error: %d is not in the tree\n", key);
				break;
			case 'd':
				fscanf(fin, "%d", &key);
				if(findNode(root, key)){
					root = deleteNode(root, key);
					fprintf(fout, "delete %d\n", key);
				}
				else{
					fprintf(fout, "deletion error: %d is not in the tree\n", key);
				}
				break;
			case 'p':
				fscanf(fin, "%c", &cv);
				if(cv == 'i'){
					if(root == NULL)
						fprintf(fout, "tree is empty");
					else
						printInorder(root);
				}
				fprintf(fout, "\n");
				break;
		}
	}
	deleteTree(root);
}
/*
Insert the value "key" in Tree "root"
Tree root : A pointer to the root node of the binary search tree.
int key : The value of the new node to insert.
return:
	pointer of root
print out:
	"insert key\n"
*/
Tree insertNode(Tree root, int key){
    if (root == NULL) { // tree is empty, create new root node
        Tree newNode = (Tree) malloc(sizeof(BST));
        newNode->value = key;
        newNode->left = NULL;
        newNode->right = NULL;
        fprintf(fout, "insert %d\n", key);
        return newNode;
    } else if (key < root->value) { // key is less than root value, insert in left subtree
        root->left = insertNode(root->left, key);
    } else if (key > root->value) { // key is greater than root value, insert in right subtree
        root->right = insertNode(root->right, key);
    } else { // key is already in the tree, print error message
        fprintf(fout, "insertion error: %d is already in the tree\n", key);
    
    }
    return root;
}
/*
Delete the value key in Tree root
Tree root : A pointer to the root node of the binary search tree.
int key : The value of the new node to be deleted.
return :
    pointer of root
*/
Tree deleteNode(Tree root, int key){
    if (root == NULL) {
        return root;
    }

    // If the key is smaller than the root's key, then it lies in the left subtree
    if (key < root->value) {
        root->left = deleteNode(root->left, key);
    }
    // If the key is greater than the root's key, then it lies in the right subtree
    else if (key > root->value) {
        root->right = deleteNode(root->right, key);
    }
    // If the key is same as root's key, then this is the node to be deleted
    else {
        // node with only one child or no child
        if (root->left == NULL) {
            Tree temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Tree temp = root->left;
            free(root);
            return temp;
        }

        // node with two children: get the inorder successor (smallest in the right subtree)
        Tree temp = root->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }

        // Copy the inorder successor's content to this node
        root->value = temp->value;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->value);
    }

    return root;
}
/*
Find the value key in Tree root
Tree root : A pointer to the root node of the binary search tree.
int key : The value of the node trying to find.
return :
	1, key is found
	0, key is not found
*/
int findNode(Tree root, int key){
    // If root is null or key is found at root, return 1
    if(root == NULL || root->value == key) {
        return (root != NULL);
    }
    // If key is greater than root's value, search in right subtree
    if(root->value < key) {
        return findNode(root->right, key);
    }
    // If key is smaller than root's value, search in left subtree
    return findNode(root->left, key);
}
/*
In Order Traversal
Tree root : A pointer to the root node of the binary search tree.
print out:
	"root->value "
*/
void printInorder(Tree root){
    if(root != NULL) {
        printInorder(root->left);
        fprintf(fout, "%d ", root->value);
        printInorder(root->right);
    }
}
/*
Delete Tree
free allocated memory
Tree root : A pointer to the root node of the binary search tree.
*/
void deleteTree(Tree root){
    if (root != NULL) {
        deleteTree(root->left);
        deleteTree(root->right);
        free(root);
    }
}
