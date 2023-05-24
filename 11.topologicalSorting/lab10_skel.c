#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE *fin;
FILE *fout;

typedef struct _Queue {
	int* key;
	int first, rear, qsize, max_queue_size;
}Queue;

typedef struct _Graph {
	int size;
	int* node;
	int** matrix;
}Graph;

Graph* CreateGraph(int* nodes, int n);
void InsertEdge(Graph* G, int a, int b);
void DeleteGraph(Graph* G);
int* Topsort(Graph* G);
Queue* MakeNewQueue(int X);
int IsEmpty(Queue* Q);
int Dequeue(Queue* Q);
void Enqueue(Queue* Q, int X);
void DeleteQueue(Queue* Q);

int main(int argc, char* agrv[]) {
	fin = fopen(agrv[1], "r");
	fout = fopen(agrv[2], "w");

	char numbers[100], inputs[150];
	fgets(numbers, 100, fin);
	int n = 0;
	countInput(&n, numbers);
	int* nodes = (int*)malloc(sizeof(int)*n);
	int* sorted_arr = NULL;
	parseInput(nodes, numbers, n);

	Graph* G = CreateGraph(nodes, n);

	fgets(inputs, 100, fin);
	int len = strlen(inputs), i, j;
	for (i = 0; i < len; i += 4) {
		int a = inputs[i] - '0', b = inputs[i + 2] - '0';
		InsertEdge(G, a, b);
	}

	// PrintGraph(G);
	fprintf(fout, "%-3s", " ");
	for (i = 0; i < G->size; i++) fprintf(fout, "%-3d", G->node[i]);
	fprintf(fout, "\n");
	for (i = 0; i < G->size; i++) {
		fprintf(fout, "%-3d", G->node[i]);
		for (j = 0; j < G->size; j++) fprintf(fout, "%-3d", G->matrix[i][j]);
		fprintf(fout, "\n");
	}
	fprintf(fout, "\n");

	sorted_arr = Topsort(G);
	if(sorted_arr == NULL){
		fprintf(fout, "sorting error : cycle!");
	}else{
		for(i = 0; i < G->size; i ++)
			fprintf(fout, "%d ", sorted_arr[i]);
		fprintf(fout, "\n");
	}
	free(sorted_arr);
	DeleteGraph(G);

	fclose(fin);
	fclose(fout);

	return 0;
}

/*
Create new graph with given nodes and the count of nodes.
saved nodes should be sorted.
return: 
        the pointer of new graph
 */
Graph* CreateGraph(int* nodes, int n) {}
/*
Insert edge from a to b in the graph.
*/
void InsertEdge(Graph* G, int a, int b) {}
/*
Deallocate the memory of the graph G.
*/
void DeleteGraph(Graph* G){}

/*
Topological sort
If two or more nodes have same priority,
    the node with the smaller number takes precedence.
return:
    the array of sorted
    NULL if the graph has a cycle
*/
int* Topsort(Graph* G){}

/*
Create new Queue with maximum size X
return:
        the pointer of new queue
*/
Queue* MakeNewQueue(int X){}
/*
Check the queue either is empty or not.
return:
        1, empty
        0, non-empty
*/
int IsEmpty(Queue* Q){}
/*
pop the front key in queue
return:
        the front key in queue
*/
int Dequeue(Queue* Q){}
/*
push the key in queue
*/
void Enqueue(Queue* Q, int X){}

/*
Deallocate the memory of the queue
*/
void DeleteQueue(Queue* Q){}


