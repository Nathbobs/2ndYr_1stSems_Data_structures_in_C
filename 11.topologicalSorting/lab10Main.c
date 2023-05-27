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

void countInput(int* n, char* str) {
	int len = strlen(str), i;
	for (i = 0; i < len; i++)
		if (0 <= str[i] - '0' && str[i] - '0' < 10) (*n)++;
}

void parseInput(int* arr, char* str, int n) {
	int len = strlen(str), i;
	int cnt = 0;
	for (i = 0; i < len; i++)
	if (0 <= str[i] - '0' && str[i] - '0' < 10) arr[cnt++] = str[i] - '0';
}
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
Graph* CreateGraph(int* nodes, int n) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->size = n;
    graph->node = (int*)malloc(sizeof(int) * n);
    graph->matrix = (int**)malloc(sizeof(int*) * n);
    
    int i, j;
    for (i = 0; i < n; i++) {
        graph->node[i] = nodes[i];
        graph->matrix[i] = (int*)malloc(sizeof(int) * n);
        for (j = 0; j < n; j++) {
            graph->matrix[i][j] = 0;  // Initialize the matrix with 0
        }
    }
    
    return graph;
}

/*
Insert edge from a to b in the graph.
*/
void InsertEdge(Graph* G, int a, int b) {
    int i, j;
    
    // Find the indices of nodes a and b in the node array
    int indexA = -1, indexB = -1;
    for (i = 0; i < G->size; i++) {
        if (G->node[i] == a)
            indexA = i;
        if (G->node[i] == b)
            indexB = i;
    }
    
    // If both nodes are found, update the adjacency matrix
    if (indexA != -1 && indexB != -1) {
        G->matrix[indexA][indexB] = 1;
    }
}

/*
Deallocate the memory of the graph G.
*/
void DeleteGraph(Graph* G) {
    int i;

    // Deallocate memory for the adjacency matrix
    for (i = 0; i < G->size; i++) {
        free(G->matrix[i]);
    }
    free(G->matrix);

    // Deallocate memory for the node array and the graph structure
    free(G->node);
    free(G);
}


/*
Topological sort
If two or more nodes have same priority,
    the node with the smaller number takes precedence.
return:
    the array of sorted
    NULL if the graph has a cycle
*/
int* Topsort(Graph* G) {
    int* indegree = (int*)malloc(sizeof(int) * G->size);
    int* sorted = (int*)malloc(sizeof(int) * G->size);
    int* visited = (int*)malloc(sizeof(int) * G->size);
    int i, j;

    // Initialize the arrays
    for (i = 0; i < G->size; i++) {
        indegree[i] = 0;
        sorted[i] = 0;
        visited[i] = 0;
    }

    // Calculate the indegree of each node
    for (i = 0; i < G->size; i++) {
        for (j = 0; j < G->size; j++) {
            if (G->matrix[j][i] == 1) {
                indegree[i]++;
            }
        }
    }

    Queue* queue = MakeNewQueue(G->size);
    int count = 0;

    // Enqueue nodes with indegree 0
    for (i = 0; i < G->size; i++) {
        if (indegree[i] == 0) {
            Enqueue(queue, i);
            visited[i] = 1;
        }
    }

    // Perform topological sorting
    while (!IsEmpty(queue)) {
        int node = Dequeue(queue);
        sorted[count++] = G->node[node];

        for (i = 0; i < G->size; i++) {
            if (G->matrix[node][i] == 1) {
                indegree[i]--;
                if (indegree[i] == 0 && !visited[i]) {
                    Enqueue(queue, i);
                    visited[i] = 1;
                }
            }
        }
    }

    // Check if a cycle exists in the graph
    if (count != G->size) {
        free(indegree);
        free(sorted);
        sorted = NULL;  // Indicate sorting error by returning NULL
    }

    DeleteQueue(queue);
    free(visited);

    return sorted;
}


/*
Create new Queue with maximum size X
return:
        the pointer of new queue
*/
Queue* MakeNewQueue(int X) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->key = (int*)malloc(sizeof(int) * X);
    queue->first = 0;
    queue->rear = -1;
    queue->qsize = 0;
    queue->max_queue_size = X;

    return queue;
}

/*
Check the queue either is empty or not.
return:
        1, empty
        0, non-empty
*/
int IsEmpty(Queue* Q) {
    return (Q->qsize == 0);  // Returns 1 if the queue is empty, 0 otherwise
}

/*
pop the front key in queue
return:
        the front key in queue
*/
int Dequeue(Queue* Q) {
    if (IsEmpty(Q)) {
        // Error: Trying to dequeue from an empty queue
        return -1;  // Return a sentinel value or handle the error in an appropriate way
    }

    int value = Q->key[Q->first];
    Q->first = (Q->first + 1) % Q->max_queue_size;
    Q->qsize--;

    return value;
}

/*
push the key in queue
*/
void Enqueue(Queue* Q, int X) {
    if (Q->qsize == Q->max_queue_size) {
        // Error: Trying to enqueue to a full queue
        return;  // Handle the error in an appropriate way
    }

    Q->rear = (Q->rear + 1) % Q->max_queue_size;
    Q->key[Q->rear] = X;
    Q->qsize++;
}


/*
Deallocate the memory of the queue
*/
void DeleteQueue(Queue* Q) {
    free(Q->key);
    free(Q);
}
