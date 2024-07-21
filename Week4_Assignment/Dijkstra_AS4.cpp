#include <iostream>
#include <climits>
#include <cstring>
#include <map>

using namespace std;

struct Node {
    int currentNode;
    int weight;
    Node* next;
};

struct Graph {
    int numNodes;
    Node** adjLists;
    map<char, int> nodeToIndex; // to enter the letters as nodeNames
    map<int, char> indexToNode;
};

// Function to create a new neighbouring list node
Node* createNode(int currentNode, int weight) {
    Node* newNode = new Node;
    newNode->currentNode = currentNode;
    newNode->weight = weight;
    newNode->next = nullptr;
    return newNode;
}

// Function to initialize a graph with a given number of nodes
Graph* createGraph(int numNodes) {
    Graph* graph = new Graph;
    graph->numNodes = numNodes;
    graph->adjLists = new Node * [numNodes];

    for (int i = 0; i < numNodes; i++) {
        graph->adjLists[i] = nullptr;
    }

    return graph;
}

// Function to add an edge to the graph
void addEdge(Graph* graph, char src, char dest, int weight) {
    int srcIndex = graph->nodeToIndex[src];
    int destIndex = graph->nodeToIndex[dest];

    // Add edge from src to dest
    Node* newNode = createNode(destIndex, weight);
    newNode->next = graph->adjLists[srcIndex];
    graph->adjLists[srcIndex] = newNode;
}

// Function to print the shortest path and its lowest cost
void printPath(int parent[], int j, Graph* graph) {
    if (parent[j] == -1) {
        cout << graph->indexToNode[j] << " ";
        return;
    }
    printPath(parent, parent[j], graph);
    cout << graph->indexToNode[j] << " ";
}

// Function to implement Dijkstra's algorithm
void dijkstra(Graph* graph, char start, char end) {
    int numNodes = graph->numNodes;

    // Convert letters to indices
    int startIndex = graph->nodeToIndex[start];
    int endIndex = graph->nodeToIndex[end];

    // Dynamic memory allocation for distance, visited, and parent arrays
    int* dist = new int[numNodes];
    bool* visited = new bool[numNodes];
    int* parent = new int[numNodes];

    for (int i = 0; i < numNodes; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
        parent[i] = -1;
    }
    dist[startIndex] = 0;

    // Main step of Dijkstra's algorithm
    for (int count = 0; count < numNodes - 1; count++) {
        // Find the node with the minimum distance value
        int minDist = INT_MAX;
        int minIndex = -1;
        for (int v = 0; v < numNodes; v++) {
            if (!visited[v] && dist[v] <= minDist) {
                minDist = dist[v];
                minIndex = v;
            }
        }

        // Check if we have a valid minimum index
        if (minIndex == -1) {
            break;
        }

        // Update distance values of neighboring nodes
        Node* temp = graph->adjLists[minIndex];
        while (temp) {
            int v = temp->currentNode;
            if (!visited[v] && dist[minIndex] != INT_MAX && dist[minIndex] + temp->weight < dist[v]) {
                dist[v] = dist[minIndex] + temp->weight;
                parent[v] = minIndex;
            }
            temp = temp->next;
        }
        visited[minIndex] = true;
    }

    // Prints the shortest path and its lowest cost
    if (dist[endIndex] == INT_MAX) {
        cout << "No path from " << start << " to " << end << endl;
    }
    else {
        cout << "Shortest Path from " << start << " to " << end << ": ";
        printPath(parent, endIndex, graph);
        cout << "\n Lowest Cost: " << dist[endIndex] << endl;
    }

    // Free dynamically allocated memory
    delete[] dist;
    delete[] visited;
    delete[] parent;
}

int main() {
    // Hardcoded the graph input data
    int numNodes = 5;
    Graph* graph = createGraph(numNodes);

    // Map nodes to indices to use alphabets/letters
    graph->nodeToIndex['A'] = 0;
    graph->nodeToIndex['B'] = 1;
    graph->nodeToIndex['C'] = 2;
    graph->nodeToIndex['D'] = 3;
    graph->nodeToIndex['E'] = 4;
    graph->indexToNode[0] = 'A';
    graph->indexToNode[1] = 'B';
    graph->indexToNode[2] = 'C';
    graph->indexToNode[3] = 'D';
    graph->indexToNode[4] = 'E';

    // Add edges to the graph
    addEdge(graph, 'A', 'B', 10);
    addEdge(graph, 'A', 'E', 3);
    addEdge(graph, 'B', 'C', 2);
    addEdge(graph, 'B', 'E', 4);
    addEdge(graph, 'C', 'D', 9);
    addEdge(graph, 'D', 'C', 7);
    addEdge(graph, 'E', 'B', 1);
    addEdge(graph, 'E', 'D', 2);

    char start, end;
    cout << "Enter the starting node (Upper Case: A-E): ";
    cin >> start;
    cout << "Enter the ending node (Upper Case: A-E): ";
    cin >> end;

    if (graph->nodeToIndex.find(start) == graph->nodeToIndex.end() || graph->nodeToIndex.find(end) == graph->nodeToIndex.end()) {
        cout << "Invalid node input! Please enter a node between Uppercase A and E." << endl;
        return 1;
    }

    dijkstra(graph, start, end);

    // Delete/free graph memory
    for (int i = 0; i < numNodes; i++) {
        Node* temp;
        while (graph->adjLists[i] != nullptr) {
            temp = graph->adjLists[i];
            graph->adjLists[i] = graph->adjLists[i]->next;
            delete temp;
        }
    }
    delete[] graph->adjLists;
    delete graph;

    return 0;
}
