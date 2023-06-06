#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define INF 1e9

FILE *fin;
FILE *fout;

typedef struct Node {
	int vertex;
	int dist;	//distance
	int prev;
}Node;

typedef struct Graph {
	int size;
	int** vertices;
	Node* nodes;
}Graph;

typedef struct Heap {
	int Capacity;
	int Size;
	Node* Element;
}Heap;

Graph* createGraph(int size);
void deleteGraph(Graph* g);
void dijkstra(Graph* g);
int* shortestPath(Graph* g, int dest);
Heap* createMinHeap(int heapSize);
void deleteMinHeap(Heap* minHeap);
void insertToMinHeap(Heap* minHeap, int vertex, int distance);
Node deleteMin(Heap* minHeap);

void swap(Node* node1, Node* node2) {
	Node temp = *node1;
	*node1 = *node2;
	*node2 = temp;
}

void main(int argc, char *argv[]) {
	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");

	Graph* g;
	int size;
	fscanf(fin, "%d\n", &size);
	g = createGraph(size + 1);

	char tmp = 0;
	while (tmp != '\n' && tmp != EOF) {
		int node1, node2, weight;
		fscanf(fin, "%d-%d-%d", &node1, &node2, &weight);
		g->vertices[node1][node2] = weight;
		tmp = fgetc(fin);
	}

	dijkstra(g);

	int j;
	for(int i = 2; i <= g->size; i++){
		int* path = shortestPath(g, i);
		if(path == NULL){
			fprintf(fout, "can not reach to node %d\n", i);
			continue;
		}
		for (j = g->size - 1; j > 0; j--){
			if(path[j] == 0) continue;
			fprintf(fout, "%d->", path[j]);
		} 
		fprintf(fout, "%d (cost : %d)\n", i, g->nodes[i].dist);
		free(path);
	}
	deleteGraph(g);
}
/*
Allocate Graph Matrix

Initial distance: INF except 1st node (source)
Initial prev: -1
*/
Graph* createGraph(int size) {}
// deallocate graph
void deleteGraph(Graph* g){}
/*
Allocate min heap
*/ 
Heap* createMinHeap(int heapSize) {}
/*
Deallocate min heap
*/
void deleteMinHeap(Heap* minHeap){}
/*
Dijkstra Algorithm
*/
void dijkstra(Graph* g){}
/*
Return shortest path from source(1) to dest(i)
Return type is array and the size is the number of node.
You should save the path reversely. 
For example, If shortest path is 1->2->3 
and the number of node(g->size) is 5,
you must return [3, 2, 1 , 0, 0]
If there is no path, return NULL 
*/
int* shortestPath(Graph* g, int dest){}
/*
Insert Node with vertex and distance into minHeap
*/
void insertToMinHeap(Heap* minHeap, int vertex, int distance) {}
/*
pop the Node with minimum distance from minHeap
return:
	Node with minimum distance
*/
Node deleteMin(Heap *minHeap) {}

