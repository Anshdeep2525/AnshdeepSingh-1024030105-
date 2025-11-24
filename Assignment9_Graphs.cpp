#include <iostream>
#include <string>

using namespace std;

// Define a maximum number of vertices for fixed-size arrays
const int MAX_VERTICES = 100;
// Define a large number to represent infinity for shortest path algorithms
const int INF = 10000000; 

// Custom utility function to find the minimum of two integers
int custom_min(int a, int b) {
    return (a < b) ? a : b;
}

// ------------------------------------------------
// 1. Graph Node and Representation (Adjacency List)
// ------------------------------------------------

// Node structure for the Adjacency List (linked list implementation)
struct AdjNode {
    int neighbor;
    int weight;
    AdjNode* next;

    AdjNode(int n, int w) : neighbor(n), weight(w), next(nullptr) {}
};

// Edge structure for Kruskal's algorithm
struct Edge {
    int u, v, weight;
};

// ------------------------------------------------
// 2. Custom Data Structures (Queue, MinHeap, DSU)
// ------------------------------------------------

// Custom Queue for BFS (Fixed-size array implementation)
class CustomQueue {
private:
    int arr[MAX_VERTICES];
    int front_idx;
    int rear_idx;
    int current_size;

public:
    CustomQueue() : front_idx(0), rear_idx(-1), current_size(0) {}

    void push(int data) {
        if (current_size == MAX_VERTICES) return; // Overflow
        rear_idx = (rear_idx + 1) % MAX_VERTICES;
        arr[rear_idx] = data;
        current_size++;
    }

    void pop() {
        if (current_size == 0) return; // Underflow
        front_idx = (front_idx + 1) % MAX_VERTICES;
        current_size--;
    }

    int front() const {
        if (current_size == 0) return -1; // Should handle error appropriately
        return arr[front_idx];
    }

    bool empty() const {
        return current_size == 0;
    }
};


// Pair structure for Min-Heap: (priority/distance, vertex)
struct HeapPair {
    int key;    // distance or weight
    int value;  // vertex index
};

// Custom Min-Heap for Prim's and Dijkstra's (Fixed-size array implementation)
class CustomMinHeap {
private:
    HeapPair heap_arr[MAX_VERTICES];
    int size;

    void swap(HeapPair& a, HeapPair& b) {
        HeapPair temp = a;
        a = b;
        b = temp;
    }

    void minHeapify(int i) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int smallest = i;

        if (l < size && heap_arr[l].key < heap_arr[i].key) {
            smallest = l;
        }

        if (r < size && heap_arr[r].key < heap_arr[smallest].key) {
            smallest = r;
        }

        if (smallest != i) {
            swap(heap_arr[i], heap_arr[smallest]);
            minHeapify(smallest);
        }
    }

public:
    CustomMinHeap() : size(0) {}

    void push(int key, int value) {
        if (size == MAX_VERTICES) return; 

        int i = size++;
        heap_arr[i] = {key, value};

        // Fix the Min Heap property by comparing with parent
        while (i != 0 && heap_arr[i].key < heap_arr[(i - 1) / 2].key) {
            swap(heap_arr[i], heap_arr[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    HeapPair pop() {
        if (size <= 0) return {INF, -1}; 
        if (size == 1) {
            size--;
            return heap_arr[0];
        }

        HeapPair root = heap_arr[0];
        heap_arr[0] = heap_arr[--size];
        minHeapify(0);

        return root;
    }

    bool empty() const {
        return size == 0;
    }

    // Since we can't efficiently update keys in a simple array heap, 
    // we rely on inserting duplicate keys with lower priorities, 
    // which is standard practice when a decrease-key operation is costly.
};

// Disjoint Set Union (DSU) for Kruskal's (Array implementation)
class DSU {
private:
    int parent[MAX_VERTICES];

public:
    DSU(int V) {
        for (int i = 0; i < V; ++i) {
            parent[i] = i;
        }
    }

    int find(int i) {
        if (parent[i] == i)
            return i;
        // Path compression
        return parent[i] = find(parent[i]);
    }

    // Union by rank/size is omitted for simplicity, but basic union is necessary
    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
        }
    }
};


// ------------------------------------------------
// 3. Graph Class Implementation
// ------------------------------------------------

class Graph {
private:
    int V; // Number of vertices
    AdjNode* adj[MAX_VERTICES];
    Edge edges[MAX_VERTICES * MAX_VERTICES]; // For Kruskal's
    int edge_count;

    // Custom string conversion for printing integers
    string int_to_string(int n) {
        if (n == 0) return "0";
        bool is_negative = n < 0;
        string s = "";
        if (is_negative) n = -n;
        while (n > 0) {
            s = char('0' + (n % 10)) + s;
            n /= 10;
        }
        return is_negative ? "-" + s : s;
    }

    // QuickSort helper for Kruskal's Edge list (sorting based on weight)
    void quick_sort_edges(int low, int high) {
        if (low < high) {
            int pivot_index = partition(low, high);
            quick_sort_edges(low, pivot_index - 1);
            quick_sort_edges(pivot_index + 1, high);
        }
    }

    int partition(int low, int high) {
        int pivot = edges[high].weight;
        int i = (low - 1);

        for (int j = low; j <= high - 1; j++) {
            if (edges[j].weight <= pivot) {
                i++;
                Edge temp = edges[i];
                edges[i] = edges[j];
                edges[j] = temp;
            }
        }
        Edge temp = edges[i + 1];
        edges[i + 1] = edges[high];
        edges[high] = temp;
        return (i + 1);
    }

public:
    Graph(int V_count) : V(V_count), edge_count(0) {
        for (int i = 0; i < V; ++i) {
            adj[i] = nullptr;
        }
    }

    // Adds a directed or undirected edge
    void add_edge(int u, int v, int w, bool directed = false) {
        // Add u -> v
        AdjNode* newNode = new AdjNode(v, w);
        newNode->next = adj[u];
        adj[u] = newNode;

        // Add to edge list for Kruskal's
        edges[edge_count++] = {u, v, w};

        if (!directed) {
            // Add v -> u for undirected graph
            AdjNode* newNode2 = new AdjNode(u, w);
            newNode2->next = adj[v];
            adj[v] = newNode2;
            
            // Note: Kruskal's requires only one entry for an undirected edge (u, v)
        }
    }
    
    // -------------------
    // Q1. Breadth First Search (BFS)
    // -------------------
    void BFS(int start_node) {
        bool visited[MAX_VERTICES] = {false};
        CustomQueue q;

        visited[start_node] = true;
        q.push(start_node);

        cout << "BFS Traversal (starting from " << start_node << "): ";

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            cout << u << " ";

            // Traverse all neighbors of u
            AdjNode* temp = adj[u];
            while (temp != nullptr) {
                int v = temp->neighbor;
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
                temp = temp->next;
            }
        }
        cout << endl;
    }

    // -------------------
    // Q2. Depth First Search (DFS)
    // -------------------
    void DFS_recursive(int u, bool visited[]) {
        visited[u] = true;
        cout << u << " ";

        // Recurse for all unvisited neighbors
        AdjNode* temp = adj[u];
        while (temp != nullptr) {
            int v = temp->neighbor;
            if (!visited[v]) {
                DFS_recursive(v, visited);
            }
            temp = temp->next;
        }
    }

    void DFS(int start_node) {
        bool visited[MAX_VERTICES] = {false};
        cout << "DFS Traversal (starting from " << start_node << "): ";
        DFS_recursive(start_node, visited);
        cout << endl;
    }

    // -------------------
    // Q3. Minimum Spanning Tree (MST)
    // -------------------

    // Q3a. Kruskal's Algorithm
    void Kruskal_MST() {
        // 1. Sort all edges by weight
        quick_sort_edges(0, edge_count - 1);
        
        DSU dsu(V);
        int mst_weight = 0;
        int edges_in_mst = 0;

        cout << "Kruskal's MST Edges (u-v, weight):" << endl;
        
        for (int i = 0; i < edge_count && edges_in_mst < V - 1; ++i) {
            Edge current_edge = edges[i];
            int u = current_edge.u;
            int v = current_edge.v;
            int w = current_edge.weight;

            // 2. Check for cycle (if u and v are already in the same set)
            if (dsu.find(u) != dsu.find(v)) {
                // Add edge to MST
                dsu.unite(u, v);
                mst_weight += w;
                edges_in_mst++;
                cout << "  " << u << "-" << v << " (" << w << ")" << endl;
            }
        }

        cout << "Total Kruskal's MST Weight: " << mst_weight << endl;
    }

    // Q3b. Prim's Algorithm
    void Prim_MST(int start_node) {
        int key[MAX_VERTICES];      // Key value used to pick minimum weight edge
        int parent[MAX_VERTICES];   // Array to store MST tree structure
        bool in_mst[MAX_VERTICES];  // True if vertex is included in MST

        for (int i = 0; i < V; ++i) {
            key[i] = INF;
            in_mst[i] = false;
            parent[i] = -1;
        }

        CustomMinHeap min_heap;

        // Start with the initial node
        key[start_node] = 0;
        min_heap.push(0, start_node);

        while (!min_heap.empty()) {
            HeapPair p = min_heap.pop();
            int u = p.value;

            // If the element popped is already finalized, ignore it (necessary due to lack of decrease-key)
            if (in_mst[u]) continue; 

            in_mst[u] = true; 

            // Iterate through all adjacent vertices of u
            AdjNode* temp = adj[u];
            while (temp != nullptr) {
                int v = temp->neighbor;
                int weight = temp->weight;

                // Relaxation step: If v is not in MST and weight(u,v) < current key[v]
                if (!in_mst[v] && weight < key[v]) {
                    parent[v] = u;
                    key[v] = weight;
                    min_heap.push(key[v], v); // Push the new, smaller key
                }
                temp = temp->next;
            }
        }

        // Print the result
        int mst_weight = 0;
        cout << "Prim's MST Edges (u-v, weight): (starting from " << start_node << ")" << endl;
        for (int i = 0; i < V; ++i) {
            if (parent[i] != -1) {
                cout << "  " << parent[i] << "-" << i << " (" << key[i] << ")" << endl;
                mst_weight += key[i];
            }
        }
        cout << "Total Prim's MST Weight: " << mst_weight << endl;
    }
    
    // -------------------
    // Q4. Dijkstra's Shortest Path Algorithm
    // -------------------
    void Dijkstra_ShortestPath(int start_node) {
        int dist[MAX_VERTICES];
        
        for (int i = 0; i < V; ++i) {
            dist[i] = INF;
        }

        CustomMinHeap min_heap;

        dist[start_node] = 0;
        min_heap.push(0, start_node);

        while (!min_heap.empty()) {
            HeapPair p = min_heap.pop();
            int u = p.value;
            int d = p.key;

            // Optimization: If the extracted distance is larger than the recorded distance, ignore (old entry)
            if (d > dist[u]) continue; 

            // Iterate through all adjacent vertices of u
            AdjNode* temp = adj[u];
            while (temp != nullptr) {
                int v = temp->neighbor;
                int weight = temp->weight;

                // Relaxation step: dist[u] + weight < dist[v]
                if (dist[u] != INF && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    min_heap.push(dist[v], v);
                }
                temp = temp->next;
            }
        }

        // Print the result
        cout << "Dijkstra's Shortest Paths (starting from " << start_node << "):" << endl;
        for (int i = 0; i < V; ++i) {
            cout << "  To vertex " << i << ": ";
            if (dist[i] == INF) {
                cout << "Unreachable" << endl;
            } else {
                cout << dist[i] << endl;
            }
        }
    }
};

void run_graph_demo() {
    // Example Graph (Undirected, Weighted)
    // Vertices 0 to 8 (V=9)
    // Edges used for MST and Shortest Path demos:
    /*
        (0, 1, 4), (0, 7, 8)
        (1, 2, 8), (1, 7, 11)
        (2, 3, 7), (2, 8, 2), (2, 5, 4)
        (3, 4, 9), (3, 5, 14)
        (4, 5, 10)
        (5, 6, 2)
        (6, 7, 1), (6, 8, 6)
        (7, 8, 7)
    */
    
    const int V = 9;
    Graph g(V);

    // Adding edges (undirected, so add_edge handles both directions)
    g.add_edge(0, 1, 4);
    g.add_edge(0, 7, 8);
    g.add_edge(1, 2, 8);
    g.add_edge(1, 7, 11);
    g.add_edge(2, 3, 7);
    g.add_edge(2, 8, 2);
    g.add_edge(2, 5, 4);
    g.add_edge(3, 4, 9);
    g.add_edge(3, 5, 14);
    g.add_edge(4, 5, 10);
    g.add_edge(5, 6, 2);
    g.add_edge(6, 7, 1);
    g.add_edge(6, 8, 6);
    g.add_edge(7, 8, 7);
    
    cout << "=======================================================" << endl;
    cout << "  Lab Assignment 9: Graph Algorithms" << endl;
    cout << "  (V=9, Undirected Weighted Graph Demo)" << endl;
    cout << "=======================================================" << endl;
    
    // Q1. BFS
    cout << "\n--- 1. Breadth First Search (BFS) (Q1) ---" << endl;
    g.BFS(0); 

    // Q2. DFS
    cout << "\n--- 2. Depth First Search (DFS) (Q2) ---" << endl;
    g.DFS(0);

    // Q3. Minimum Spanning Tree (MST)
    cout << "\n--- 3. Minimum Spanning Tree (MST) (Q3) ---" << endl;
    g.Kruskal_MST();
    cout << endl;
    g.Prim_MST(0); // Start Prim's from vertex 0

    // Q4. Dijkstra's Shortest Path
    cout << "\n--- 4. Dijkstra's Shortest Path (Q4) ---" << endl;
    g.Dijkstra_ShortestPath(0); // Find shortest paths from vertex 0
}

int main() {
    run_graph_demo();
    return 0;
}
