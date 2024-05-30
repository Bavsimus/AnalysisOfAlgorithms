#include <stdio.h>
#include <stdlib.h>

#define MAX 100  //max vertices

//--------
struct Queue {
    int items[MAX];
    int front;
    int rear;
};

struct Queue* createQueue();
void enqueue(struct Queue* q, int value);
int dequeue(struct Queue* q);
int isEmpty(struct Queue* q);

struct Graph {
    int numVertices;
    int** adjLists;
    int* visited;
};

struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

void enqueue(struct Queue* q, int value) {
    if (q->rear == MAX - 1)
        printf("\nOut of quota!");
    else {
        if (q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}

int dequeue(struct Queue* q) {
    int item;
    if (isEmpty(q)) {
        printf("Queue is empty!");
        item = -1;
    } else {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear) {
            q->front = q->rear = -1;
        }
    }
    return item;
}

int isEmpty(struct Queue* q) {
    if (q->rear == -1)
        return 1;
    else
        return 0;
}

struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    graph->adjLists = (int**)malloc(vertices * sizeof(int*));
    graph->visited = (int*)malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = (int*)malloc(vertices * sizeof(int));
        graph->visited[i] = 0;
    }

    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    graph->adjLists[src][dest] = 1;
    graph->adjLists[dest][src] = 1;  
}
//----


//our func
void BFS(struct Graph* graph, int startVertex) {
    struct Queue* q = createQueue();

    graph->visited[startVertex] = 1;
    enqueue(q, startVertex);

    while (!isEmpty(q)) {
        int currentVertex = dequeue(q);
        printf("%d ", currentVertex);

        for (int i = 0; i < graph->numVertices; i++) {
            if (graph->adjLists[currentVertex][i] == 1 && graph->visited[i] == 0) {
                graph->visited[i] = 1;
                enqueue(q, i);
            }
        }
    }
}

int main() {
    int numVertices, src, dest;
    struct Graph* graph;

    printf("how many vertices? :");
    scanf("%d", &numVertices);

    graph = createGraph(numVertices);

    printf("add vertices: (-1 -1 for end)\n");
    while (1) {
        scanf("%d %d", &src, &dest);
        if (src == -1 && dest == -1)
            break;
        else if (src < 0 || src >= numVertices || dest < 0 || dest >= numVertices) {
            printf("invalid vertice number try again: ");
            continue;
        }
        addEdge(graph, src, dest);
    }

    printf("BFS Traversal: ");
    BFS(graph, 0);
    printf("\n");

    return 0;
}

