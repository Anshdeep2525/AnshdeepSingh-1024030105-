#include <iostream>

using namespace std;

// Custom utility function to find the maximum of two integers, 
// replacing std::max from <cmath>
int custom_max(int a, int b) {
    return (a > b) ? a : b;
}

// Custom utility function to find the minimum of two integers, 
// replacing std::min from <cmath>
int custom_min(int a, int b) {
    return (a < b) ? a : b;
}

// Global constant for minimum integer value, replacing INT_MIN
const int CUSTOM_INT_MIN = -2147483647 - 1; // Standard C++ minimum 32-bit signed int

// Forward declaration for the TreeNode structure
struct TreeNode;

// ==========================================================
// BST IMPLEMENTATION
// (Q1, Q2, Q3, Q4)
// ==========================================================

// Structure for a tree node
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    // Constructor
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    TreeNode* root;

    // Helper for Q3(a): Recursive insertion (no duplicates)
    TreeNode* insertRecursive(TreeNode* node, int data) {
        if (node == nullptr) {
            return new TreeNode(data);
        }

        if (data < node->data) {
            node->left = insertRecursive(node->left, data);
        } else if (data > node->data) {
            node->right = insertRecursive(node->right, data);
        }
        // If data == node->data (duplicate), we do nothing

        return node;
    }

    // Helper for Q2(d/e) and Q3(b): Finds the node with the minimum value in a given tree
    TreeNode* findMin(TreeNode* node) {
        if (node == nullptr) return nullptr;
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    // Helper for Q3(b): Recursive deletion
    TreeNode* deleteRecursive(TreeNode* node, int key) {
        if (node == nullptr) {
            return nullptr;
        }

        if (key < node->data) {
            node->left = deleteRecursive(node->left, key);
        } else if (key > node->data) {
            node->right = deleteRecursive(node->right, key);
        } else {
            // Case 1: Node with only one child or no child
            if (node->left == nullptr) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }

            // Case 2: Node with two children. Replace with in-order successor (smallest in right subtree)
            TreeNode* temp = findMin(node->right);
            node->data = temp->data; // Copy successor's content to this node
            node->right = deleteRecursive(node->right, temp->data); // Delete the successor
        }
        return node;
    }

    // Q1: Pre-order traversal (Node -> Left -> Right)
    void preOrderRecursive(TreeNode* node) const {
        if (node == nullptr) return;
        cout << node->data << " ";
        preOrderRecursive(node->left);
        preOrderRecursive(node->right);
    }

    // Q1: In-order traversal (Left -> Node -> Right - prints sorted elements in BST)
    void inOrderRecursive(TreeNode* node) const {
        if (node == nullptr) return;
        inOrderRecursive(node->left);
        cout << node->data << " ";
        inOrderRecursive(node->right);
    }

    // Q1: Post-order traversal (Left -> Right -> Node)
    void postOrderRecursive(TreeNode* node) const {
        if (node == nullptr) return;
        postOrderRecursive(node->left);
        postOrderRecursive(node->right);
        cout << node->data << " ";
    }

    // Q3(c): Calculates the maximum depth (Height) of the tree
    int maxDepthRecursive(TreeNode* node) const {
        if (node == nullptr) {
            return 0;
        }
        int leftDepth = maxDepthRecursive(node->left);
        int rightDepth = maxDepthRecursive(node->right);
        // Depth is 1 (for current node) plus the maximum of the two sub-tree depths
        return 1 + custom_max(leftDepth, rightDepth);
    }

    // Q3(d): Calculates the minimum depth of the tree (shortest path to a leaf)
    int minDepthRecursive(TreeNode* node) const {
        if (node == nullptr) {
            return 0;
        }
        if (node->left == nullptr && node->right == nullptr) {
            return 1; // Leaf node
        }
        if (node->left == nullptr) {
            return 1 + minDepthRecursive(node->right);
        }
        if (node->right == nullptr) {
            return 1 + minDepthRecursive(node->left);
        }
        // Minimum depth is 1 + minimum of the two sub-tree depths
        return 1 + custom_min(minDepthRecursive(node->left), minDepthRecursive(node->right));
    }

    // Q4: Helper function to check if a binary tree is a valid BST
    bool isBST(TreeNode* node, int min_val, int max_val) const {
        // Base case: An empty tree is a BST
        if (node == nullptr) {
            return true;
        }

        // Check if the current node's value is within the valid range
        if (node->data <= min_val || node->data >= max_val) {
            return false;
        }

        // Recursively check the left subtree: max constraint becomes current node's data
        // Recursively check the right subtree: min constraint becomes current node's data
        return isBST(node->left, min_val, node->data) &&
               isBST(node->right, node->data, max_val);
    }

public:
    BinarySearchTree() : root(nullptr) {}

    // Q3(a): Public interface for insertion
    void insert(int data) {
        root = insertRecursive(root, data);
    }

    // Q3(b): Public interface for deletion
    void deleteNode(int key) {
        root = deleteRecursive(root, key);
    }

    // Q2(a): Search for a given item (Recursive)
    TreeNode* searchRecursive(int key) const {
        return searchRecursiveHelper(root, key);
    }

    TreeNode* searchRecursiveHelper(TreeNode* node, int key) const {
        if (node == nullptr || node->data == key) {
            return node;
        }
        if (key < node->data) {
            return searchRecursiveHelper(node->left, key);
        } else {
            return searchRecursiveHelper(node->right, key);
        }
    }

    // Q2(a): Search for a given item (Non-Recursive/Iterative)
    TreeNode* searchNonRecursive(int key) const {
        TreeNode* current = root;
        while (current != nullptr) {
            if (key == current->data) {
                return current;
            } else if (key < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return nullptr;
    }

    // Q2(b): Maximum element of the BST
    int maxElement() const {
        if (root == nullptr) return -1; // Indicate empty tree or error
        TreeNode* current = root;
        while (current->right != nullptr) {
            current = current->right;
        }
        return current->data;
    }

    // Q2(c): Minimum element of the BST
    int minElement() const {
        if (root == nullptr) return -1; // Indicate empty tree or error
        return findMin(root)->data;
    }

    // Q2(d): In-order successor of a given node
    int inOrderSuccessor(int key) const {
        TreeNode* current = root;
        TreeNode* successor = nullptr;

        while (current != nullptr) {
            if (key < current->data) {
                successor = current; // Possible successor
                current = current->left;
            } else if (key > current->data) {
                current = current->right;
            } else { // Node found (current->data == key)
                // If it has a right child, the successor is the minimum in the right subtree
                if (current->right != nullptr) {
                    return findMin(current->right)->data;
                }
                // Otherwise, the successor is the last stored 'successor' (ancestor)
                return (successor != nullptr) ? successor->data : -1;
            }
        }
        return -1; // Key not found
    }

    // Q2(e): In-order predecessor of a given node
    int inOrderPredecessor(int key) const {
        TreeNode* current = root;
        TreeNode* predecessor = nullptr;

        while (current != nullptr) {
            if (key > current->data) {
                predecessor = current; // Possible predecessor
                current = current->right;
            } else if (key < current->data) {
                current = current->left;
            } else { // Node found (current->data == key)
                // If it has a left child, the predecessor is the maximum in the left subtree
                if (current->left != nullptr) {
                    TreeNode* temp = current->left;
                    while (temp->right != nullptr) {
                        temp = temp->right;
                    }
                    return temp->data;
                }
                // Otherwise, the predecessor is the last stored 'predecessor' (ancestor)
                return (predecessor != nullptr) ? predecessor->data : -1;
            }
        }
        return -1; // Key not found
    }

    // Q1: Public interfaces for traversals
    void preOrder() const { preOrderRecursive(root); cout << endl; }
    void inOrder() const { inOrderRecursive(root); cout << endl; }
    void postOrder() const { postOrderRecursive(root); cout << endl; }

    // Q3(c): Public interface for maximum depth
    int maxDepth() const {
        return maxDepthRecursive(root);
    }

    // Q3(d): Public interface for minimum depth
    int minDepth() const {
        return minDepthRecursive(root);
    }

    // Q4: Public interface to check if it's a BST
    bool isBinarySearchTree() const {
        // Use the custom minimum integer value for the initial min range
        // Max range is set high enough to not interfere with typical int values
        return isBST(root, CUSTOM_INT_MIN, 2147483647); 
    }
};

// ==========================================================
// HEAP AND HEAPSORT IMPLEMENTATION
// (Q5, Q6)
// ==========================================================

class MaxHeap {
private:
    int* arr;
    int capacity;
    int heap_size;

    // Helper function to swap two elements
    void swap(int& a, int& b) {
        int temp = a;
        a = b;
        b = temp;
    }

    // Get parent, left, and right indices
    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

    // Q5: Heapify a subtree rooted with node i
    void maxHeapify(int i) {
        int l = left(i);
        int r = right(i);
        int largest = i;

        // Check if left child is larger than root
        if (l < heap_size && arr[l] > arr[i]) {
            largest = l;
        }

        // Check if right child is larger than current largest
        if (r < heap_size && arr[r] > arr[largest]) {
            largest = r;
        }

        // If largest is not root
        if (largest != i) {
            swap(arr[i], arr[largest]);
            // Recursively heapify the affected sub-tree
            maxHeapify(largest);
        }
    }

    // Build the heap from an array (used by Heapsort)
    void buildMaxHeap() {
        // Start from the last non-leaf node and heapify backwards
        for (int i = (heap_size / 2) - 1; i >= 0; i--) {
            maxHeapify(i);
        }
    }

public:
    // Constructor: Takes an existing array and its size
    MaxHeap(int input_arr[], int n) {
        capacity = n;
        heap_size = n;
        arr = new int[capacity];
        for (int i = 0; i < n; i++) {
            arr[i] = input_arr[i];
        }
        buildMaxHeap(); // Build the Max Heap immediately
    }

    // Destructor to free dynamically allocated memory
    ~MaxHeap() {
        delete[] arr;
    }

    // Q6: Insert a new key into the Max Heap (Priority Queue operation)
    void insertKey(int key) {
        if (heap_size == capacity) {
            cout << "Error: Heap overflow. Cannot insert more elements." << endl;
            return;
        }

        // Insert the new key at the end
        int i = heap_size;
        arr[i] = key;
        heap_size++;

        // Fix the Max Heap property by comparing with parent (sifting up)
        while (i != 0 && arr[parent(i)] < arr[i]) {
            swap(arr[i], arr[parent(i)]);
            i = parent(i);
        }
    }

    // Q6: Extract Max (Priority Queue operation)
    int extractMax() {
        if (heap_size <= 0) {
            cout << "Error: Heap is empty." << endl;
            return -1;
        }
        if (heap_size == 1) {
            heap_size--;
            return arr[0];
        }

        // Store the maximum value
        int root = arr[0];

        // Move the last element to the root
        arr[0] = arr[heap_size - 1];
        heap_size--;

        // Heapify the root to restore the property (sifting down)
        maxHeapify(0);

        return root;
    }

    // Q5: Heapsort (Sorting in increasing order)
    void heapSortIncreasing(int sorted_arr[], int n) {
        // Create a copy of the array and heap_size for the sorting process
        int sort_arr[n];
        int current_heap_size = n;
        for(int i=0; i<n; ++i) sort_arr[i] = arr[i];

        // Perform the Heapsort logic in place on the temporary array
        for (int i = n - 1; i > 0; i--) {
            // Swap root (largest) with the last element of the current heap
            swap(sort_arr[0], sort_arr[i]);

            // Reduce the heap size for the next iteration (effectively fixing the largest element)
            current_heap_size--;
            
            // Re-heapify the root
            int largest = 0;
            int current_root_index = 0;

            // Iterative maxHeapify (to avoid needing to copy the method)
            while (true) {
                int l = 2 * current_root_index + 1;
                int r = 2 * current_root_index + 2;
                largest = current_root_index;

                if (l < current_heap_size && sort_arr[l] > sort_arr[largest]) {
                    largest = l;
                }

                if (r < current_heap_size && sort_arr[r] > sort_arr[largest]) {
                    largest = r;
                }

                if (largest != current_root_index) {
                    swap(sort_arr[current_root_index], sort_arr[largest]);
                    current_root_index = largest; // Move down
                } else {
                    break; // Heap property restored
                }
            }
        }
        
        // Copy the sorted elements back to the output array
        for (int i = 0; i < n; i++) {
            sorted_arr[i] = sort_arr[i];
        }
    }

    // Q5: Heapsort (Sorting in decreasing order)
    void heapSortDecreasing(int sorted_arr[], int n) {
        // Since we implemented MaxHeapify, the array is already sorted in increasing 
        // order after heapSortIncreasing. We just reverse that sorted array.
        int temp_arr[n];
        heapSortIncreasing(temp_arr, n); // Get the increasing order result first

        // Reverse the array to get decreasing order
        for (int i = 0; i < n; i++) {
            sorted_arr[i] = temp_arr[n - 1 - i];
        }
    }
};

// ==========================================================
// MAIN DRIVER FUNCTION
// ==========================================================

void printResult(const string& operation, int value) {
    if (value != -1) {
        cout << operation << ": " << value << endl;
    } else {
        cout << operation << ": Not found / Tree is empty / Error" << endl;
    }
}

// Utility to print an array
void printArray(const int arr[], int n, const string& title) {
    cout << title << ": [";
    for (int i = 0; i < n; ++i) {
        cout << arr[i];
        if (i < n - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}


void runBSTDemo() {
    BinarySearchTree bst;
    cout << "--- 1. BST Initialization (Q3a) ---" << endl;
    int elements[] = {50, 30, 70, 20, 40, 60, 80};
    for (int val : elements) {
        bst.insert(val);
    }
    cout << "Initial BST built with elements: 50, 30, 70, 20, 40, 60, 80" << endl;

    // Q1: Traversals
    cout << "\n--- 2. Binary Tree Traversals (Q1) ---" << endl;
    cout << "Pre-order (Root, Left, Right): "; bst.preOrder();
    cout << "In-order (Left, Root, Right): "; bst.inOrder(); 
    cout << "Post-order (Left, Right, Root): "; bst.postOrder();

    // Q2: Search and Extremes
    cout << "\n--- 3. BST Search and Extremes (Q2) ---" << endl;
    
    // Q2(a): Search
    int search_key = 40;
    cout << "Search (Recursive) for " << search_key << ": " 
         << (bst.searchRecursive(search_key) ? "Found" : "Not Found") << endl;
    search_key = 99;
    cout << "Search (Non-Recursive) for " << search_key << ": " 
         << (bst.searchNonRecursive(search_key) ? "Found" : "Not Found") << endl;

    // Q2(b, c): Min/Max
    printResult("Maximum Element (Q2b)", bst.maxElement());
    printResult("Minimum Element (Q2c)", bst.minElement());
    
    // Q2(d, e): Successor/Predecessor
    int target_node = 50;
    printResult("In-order Successor of " + to_string(target_node) + " (Q2d)", bst.inOrderSuccessor(target_node)); 
    printResult("In-order Predecessor of " + to_string(target_node) + " (Q2e)", bst.inOrderPredecessor(target_node)); 

    // Q3: Depth and Deletion
    cout << "\n--- 4. BST Depth and Deletion (Q3) ---" << endl;
    printResult("Maximum Depth (Height) (Q3c)", bst.maxDepth()); 
    printResult("Minimum Depth (Q3d)", bst.minDepth()); 

    // Q3(b): Deletion
    int delete_key = 70; 
    cout << "Deleting element " << delete_key << " (two children case)..." << endl;
    bst.deleteNode(delete_key);
    cout << "In-order after deleting " << delete_key << ": "; bst.inOrder();
    
    delete_key = 50; 
    cout << "Deleting element " << delete_key << " (Root with two children)..." << endl;
    bst.deleteNode(delete_key);
    cout << "In-order after deleting " << delete_key << ": "; bst.inOrder();
    
    // Q4: BST Property Check
    cout << "\n--- 5. BST Validation (Q4) ---" << endl;
    cout << "Is the current tree a BST? " << (bst.isBinarySearchTree() ? "Yes" : "No") << endl;
}

void runHeapDemo() {
    int arr_size = 8;
    int arr[] = {4, 1, 3, 2, 16, 9, 10, 14};
    int n = arr_size;

    cout << "\n\n=======================================================" << endl;
    cout << "  Heap and Heapsort Demonstration (Q5, Q6)" << endl;
    cout << "=======================================================" << endl;

    // --- Q5: Heapsort ---
    cout << "\n--- 1. Heapsort (Q5) ---" << endl;
    printArray(arr, n, "Original Array");
    
    // Create and build the heap
    MaxHeap heap_sort(arr, n);
    int sorted_inc[n];
    int sorted_dec[n];
    
    // Sort in increasing order
    heap_sort.heapSortIncreasing(sorted_inc, n);
    printArray(sorted_inc, n, "Heapsort (Increasing Order)");

    // Sort in decreasing order
    heap_sort.heapSortDecreasing(sorted_dec, n);
    printArray(sorted_dec, n, "Heapsort (Decreasing Order)");


    // --- Q6: Priority Queue Operations ---
    cout << "\n--- 2. Priority Queue Operations (Max Heap) (Q6) ---" << endl;
    
    // Re-initialize with original array for PQ demo
    int arr_pq[] = {4, 1, 3, 2, 16, 9, 10, 14};
    MaxHeap max_pq(arr_pq, n);

    // Q6: Extract Max
    printResult("Extract Max (1st time)", max_pq.extractMax()); 
    printResult("Extract Max (2nd time)", max_pq.extractMax()); 
    
    // Q6: Insert Key
    int new_key = 100;
    cout << "Inserting key: " << new_key << endl;
    max_pq.insertKey(new_key);
    
    printResult("Extract Max (After insertion)", max_pq.extractMax()); 
}

int main() {
    cout << "=======================================================" << endl;
    cout << "  Lab Assignment 8: Binary Search Trees & Heap" << endl;
    cout << "  (Using iostream only)" << endl;
    cout << "=======================================================" << endl;
    runBSTDemo();
    runHeapDemo();
    
    return 0;
}
