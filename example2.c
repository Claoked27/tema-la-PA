/*parcurgerge  graf cu DFS/BFS*/

//Imi cer scuze in avans

#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

typedef struct graph {
    int numVertices;
    int *visited;
    Node **adjList;
} Graph;

/// utils
void checkAllocation(void *ptr) {
    if (ptr == NULL) {
        puts("Memory allocation failed!");
        exit(1);
    }
}

Node *createNode(int data) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    checkAllocation(newNode);
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Graph *createGraph(int numVertices) {
    Graph *graph = (Graph*) malloc(sizeof(Graph));
    checkAllocation(graph);
    graph->numVertices = numVertices;
    graph->adjList = (Node**) malloc((numVertices + 1) * sizeof(Node *));
    graph->visited = (int*) malloc((numVertices + 1) * sizeof(int));
    checkAllocation(graph->adjList);
    checkAllocation(graph->visited);

    for (int i = 1; i <= numVertices; i++) {
        graph->adjList[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

void addEdge(Graph *graph, int from, int to) {
    Node *node = createNode(to);
    node->next = graph->adjList[from];
    graph->adjList[from] = node;

    node = createNode(from);
    node->next = graph->adjList[to];
    graph->adjList[to] = node;
}

void insertEdges(Graph *graph, int numEdges) {
    int from, to;
    printf("Adauga %d muchii (de la 1 la %d):\n", numEdges, graph->numVertices);
    for (int i = 0; i < numEdges; i++) {
        scanf("%d%d", &from, &to);
        addEdge(graph, from, to);
    }
}

/// bfs utils
int isEmpty(Node *queue) {
    return queue == NULL;
}

void enqueue(Node **queue, int data) {
    Node *newNode = createNode(data);
    if (isEmpty(*queue)) {
        *queue = newNode;
    } else {
        Node *temp = *queue;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

int dequeue(Node **queue) {
    int data = (*queue)->data;
    Node *temp = *queue;
    *queue = (*queue)->next;
    free(temp);
    return data;
}

void printGraph(Graph *graph) {
    for (int i = 1; i <= graph->numVertices; i++) {
        Node *current = graph->adjList[i];
        printf("%d: ", i);
        while (current) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
    }
}

void wipeVisitedList(Graph *graph) {
    for (int i = 1; i <= graph->numVertices; i++) {
        graph->visited[i] = 0;
    }
}

// parcurgeri
void DFS(Graph *graph, int node) {
    graph->visited[node] = 1;
    printf("%d->", node);

    Node *current = graph->adjList[node];
    while (current != NULL) {
        int neighbor = current->data;
        if (graph->visited[neighbor] == 0) {
            DFS(graph, neighbor);
        }
        current = current->next;
    }
}

void BFS(Graph *graph, int start) {
    Node *bfsQueue = NULL;
    graph->visited[start] = 1;
    enqueue(&bfsQueue, start);

    while (!isEmpty(bfsQueue)) {
        int node = dequeue(&bfsQueue);
        printf("%d ", node);

        Node *current = graph->adjList[node];
        while (current) {
            int neighbor = current->data;
            if (graph->visited[neighbor] == 0) {
                graph->visited[neighbor] = 1;
                enqueue(&bfsQueue, neighbor);
            }
            current = current->next;
        }
    }
}

int main() {
    int numVertices, numEdges, startVertex;

    printf("Cate noduri are graful? ");
    scanf("%d", &numVertices);

    printf("Cate muchii are graful? ");
    scanf("%d", &numEdges);

    Graph *graph = createGraph(numVertices);
    insertEdges(graph, numEdges);

    printf("De unde plecam in DFS? ");
    scanf("%d", &startVertex);
    printf("Parcurgere cu DFS: ");
    DFS(graph, startVertex);
    printf("\n");

    wipeVisitedList(graph);

    printf("De unde plecam in BFS? ");
    scanf("%d", &startVertex);
    printf("Parcurgere cu BFS: ");
    BFS(graph, startVertex);
    printf("\n");

    return 0;
}

