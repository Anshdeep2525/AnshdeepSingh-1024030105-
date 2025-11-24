#include <iostream>
#include <string>

using namespace std;

// Define the maximum size of the Hash Table array (M)
const int TABLE_SIZE = 11; // A prime number is often chosen for good distribution

// ==========================================================
// 1. Custom Hash Node (for both Map and Set)
// ==========================================================

// Node structure for Separate Chaining (Linked List)
struct HashNode {
    int key;
    int value; // Stores frequency for HashMap, unused for HashSet
    HashNode* next;

    // Constructor for HASH MAP (key and value)
    HashNode(int k, int v) : key(k), value(v), next(nullptr) {}
    
    // Constructor for HASH SET (key only, value defaults to 0)
    HashNode(int k) : key(k), value(0), next(nullptr) {}
};

// ==========================================================
// 2. Custom Hashing Utilities
// ==========================================================

// Simple Division Hashing Function
int hashFunction(int key) {
    // Ensure key is positive for the modulo operation
    return (key < 0 ? -key : key) % TABLE_SIZE;
}

// ==========================================================
// 3. Custom Hash Set Implementation
// ==========================================================
// Used for Q1, Q2, Q5, Q6
class CustomHashSet {
private:
    HashNode* table[TABLE_SIZE];

    // Helper to search for a key in a specific bucket
    HashNode* searchBucket(int index, int key) const {
        HashNode* current = table[index];
        while (current != nullptr) {
            if (current->key == key) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

public:
    CustomHashSet() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            table[i] = nullptr;
        }
    }

    ~CustomHashSet() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            HashNode* current = table[i];
            while (current != nullptr) {
                HashNode* next = current->next;
                delete current;
                current = next;
            }
        }
    }

    // Inserts a key into the set
    void insert(int key) {
        int index = hashFunction(key);
        // Check if the key already exists
        if (searchBucket(index, key)) {
            return; // Key already present
        }

        // Insert new node at the beginning of the list (Separate Chaining)
        HashNode* newNode = new HashNode(key);
        newNode->next = table[index];
        table[index] = newNode;
    }

    // Checks if a key is present in the set
    bool contains(int key) const {
        int index = hashFunction(key);
        return searchBucket(index, key) != nullptr;
    }

    // Removes a key from the set
    void remove(int key) {
        int index = hashFunction(key);
        HashNode* current = table[index];
        HashNode* prev = nullptr;

        while (current != nullptr && current->key != key) {
            prev = current;
            current = current->next;
        }

        if (current == nullptr) return; // Key not found

        // Unlink the node
        if (prev == nullptr) {
            table[index] = current->next; // Head node deleted
        } else {
            prev->next = current->next;
        }
        delete current;
    }
};

// ==========================================================
// 4. Custom Hash Map Implementation
// ==========================================================
// Used for Q3, Q4
class CustomHashMap {
private:
    HashNode* table[TABLE_SIZE];

    // Helper to search for a key in a specific bucket
    HashNode* searchBucket(int index, int key) const {
        HashNode* current = table[index];
        while (current != nullptr) {
            if (current->key == key) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

public:
    CustomHashMap() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            table[i] = nullptr;
        }
    }

    ~CustomHashMap() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            HashNode* current = table[i];
            while (current != nullptr) {
                HashNode* next = current->next;
                delete current;
                current = next;
            }
        }
    }

    // Inserts a key or updates its value
    void put(int key, int value) {
        int index = hashFunction(key);
        HashNode* node = searchBucket(index, key);

        if (node) {
            node->value = value; // Key exists, update value
        } else {
            // Key does not exist, insert new node
            HashNode* newNode = new HashNode(key, value);
            newNode->next = table[index];
            table[index] = newNode;
        }
    }

    // Gets the value associated with a key, returns -1 if key not found
    int get(int key) const {
        int index = hashFunction(key);
        HashNode* node = searchBucket(index, key);
        return node ? node->value : -1;
    }

    // Checks if a key is present
    bool containsKey(int key) const {
        int index = hashFunction(key);
        return searchBucket(index, key) != nullptr;
    }

    // Increments the count for a key (used for frequency counting)
    void incrementCount(int key) {
        int index = hashFunction(key);
        HashNode* node = searchBucket(index, key);

        if (node) {
            node->value++; // Increment frequency
        } else {
            // Insert with count 1
            HashNode* newNode = new HashNode(key, 1);
            newNode->next = table[index];
            table[index] = newNode;
        }
    }

    // Utility function to iterate over all entries (only keys are accessible)
    void printAllFrequencies() const {
        cout << "Key -> Frequency:" << endl;
        for (int i = 0; i < TABLE_SIZE; ++i) {
            HashNode* current = table[i];
            while (current != nullptr) {
                cout << "  " << current->key << " -> " << current->value << " times" << endl;
                current = current->next;
            }
        }
    }
};

// ==========================================================
// 5. Linked List Structure for Q5 and Q4 (Additional)
// ==========================================================

struct Node {
    int data;
    Node* next;
    // Pointer used for cycle creation (Q5)
    Node* random; 

    Node(int d) : data(d), next(nullptr), random(nullptr) {}
};

// Helper function to print a list
void printList(Node* head) {
    if (head == nullptr) {
        cout << "NULL" << endl;
        return;
    }
    Node* current = head;
    while (current != nullptr) {
        cout << current->data;
        if (current->next != nullptr) {
            cout << "->";
        }
        current = current->next;
    }
    cout << endl;
}


// ==========================================================
// 6. Assignment Questions Implementation
// ==========================================================

// Q1. Check if array contains duplicates using hash set.
void check_duplicates(const int arr[], int size) {
    CustomHashSet set;
    bool has_duplicates = false;
    
    for (int i = 0; i < size; ++i) {
        if (set.contains(arr[i])) {
            has_duplicates = true;
            break;
        }
        set.insert(arr[i]);
    }

    cout << "\n--- Q1. Check for Duplicates ---" << endl;
    cout << "Input: [";
    for(int i=0; i<size; ++i) cout << arr[i] << (i == size-1 ? "" : ", ");
    cout << "]" << endl;
    cout << "Output: " << (has_duplicates ? "true (Duplicates Found)" : "false (No Duplicates)") << endl;
}

// Q2. Find common elements in two arrays using a hash set.
void find_common_elements(const int A[], int sizeA, const int B[], int sizeB) {
    CustomHashSet set;
    // 1. Insert all elements of A into the hash set
    for (int i = 0; i < sizeA; ++i) {
        set.insert(A[i]);
    }

    cout << "\n--- Q2. Find Common Elements ---" << endl;
    cout << "Input A: [";
    for(int i=0; i<sizeA; ++i) cout << A[i] << (i == sizeA-1 ? "" : ", ");
    cout << "]" << endl;
    cout << "Input B: [";
    for(int i=0; i<sizeB; ++i) cout << B[i] << (i == sizeB-1 ? "" : ", ");
    cout << "]" << endl;
    
    cout << "Output (Common Elements): ";
    bool first = true;
    // 2. Check each element of B against the set
    for (int i = 0; i < sizeB; ++i) {
        if (set.contains(B[i])) {
            if (!first) cout << ",";
            cout << B[i];
            first = false;
            // Optionally remove from set if we only want unique common elements printed once
            set.remove(B[i]); 
        }
    }
    cout << endl;
}

// Q3. Count the frequency of each number in an array using a hash map.
void count_frequency(const int arr[], int size) {
    CustomHashMap map;
    
    for (int i = 0; i < size; ++i) {
        map.incrementCount(arr[i]);
    }

    cout << "\n--- Q3. Count Frequency ---" << endl;
    cout << "Input: [";
    for(int i=0; i<size; ++i) cout << arr[i] << (i == size-1 ? "" : ", ");
    cout << "]" << endl;
    map.printAllFrequencies();
}

// Q4. Find the first non-repeating element in an array using a hash map.
void find_first_non_repeating(const int arr[], int size) {
    CustomHashMap frequency_map;
    // 1. Calculate frequency of all elements
    for (int i = 0; i < size; ++i) {
        frequency_map.incrementCount(arr[i]);
    }

    int first_non_repeating = -1;
    // 2. Iterate through the array again and check frequency
    for (int i = 0; i < size; ++i) {
        if (frequency_map.get(arr[i]) == 1) {
            first_non_repeating = arr[i];
            break;
        }
    }

    cout << "\n--- Q4. Find First Non-Repeating Element ---" << endl;
    cout << "Input: [";
    for(int i=0; i<size; ++i) cout << arr[i] << (i == size-1 ? "" : ", ");
    cout << "]" << endl;
    
    cout << "Output: " << first_non_repeating;
    if (first_non_repeating == -1) {
        cout << " (No non-repeating element found)";
    }
    cout << endl;
}

// Q5. Determine whether a linked list contains a loop (cycle) using a hash set.
bool contains_loop(Node* head) {
    CustomHashSet visited_nodes;
    Node* current = head;
    
    while (current != nullptr) {
        // Since we are storing the address (pointer value) in the set, 
        // we cast it to an integer type. This is generally safe for small 
        // pointer values in a test environment.
        int node_address = reinterpret_cast<int>(current);

        if (visited_nodes.contains(node_address)) {
            return true;
        }
        visited_nodes.insert(node_address);
        current = current->next;
    }
    return false;
}

void test_q5_q6() {
    cout << "\n--- Q5. Detect Loop in Linked List (using HashSet) ---" << endl;
    
    // Create list 1->2->3->4->2 (Cycle)
    Node* head1 = new Node(1);
    head1->next = new Node(2);
    head1->next->next = new Node(3);
    head1->next->next->next = new Node(4);
    // Create the cycle: 4 points back to 2
    Node* cycle_node = head1->next;
    head1->next->next->next->next = cycle_node; 

    // Note: Cannot print the cyclical list safely, so we state the structure.
    cout << "List 1 (1->2->3->4->2 [cycle]): " << (contains_loop(head1) ? "true (Loop Detected)" : "false (No Loop)") << endl;

    // Create list 5->6->7->NULL (No Cycle)
    Node* head2 = new Node(5);
    head2->next = new Node(6);
    head2->next->next = new Node(7);

    cout << "List 2 (5->6->7->NULL): " << (contains_loop(head2) ? "true (Loop Detected)" : "false (No Loop)") << endl;

    // Cleanup (only non-cyclical list can be cleaned up safely with standard traversal)
    Node* temp;
    Node* current = head2;
    while (current != nullptr) {
        temp = current;
        current = current->next;
        delete temp;
    }
    // For head1, we manually break the cycle and cleanup
    head1->next->next->next->next = nullptr;
    current = head1;
    while (current != nullptr) {
        temp = current;
        current = current->next;
        delete temp;
    }
}

// Q6. Check if binary tree contains duplicate node values using hash set.
// A simpler TreeNode structure for this problem
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int d) : data(d), left(nullptr), right(nullptr) {}
};

// Recursive helper function for Q6
bool check_tree_duplicates_recursive(TreeNode* node, CustomHashSet& set) {
    if (node == nullptr) {
        return false;
    }

    if (set.contains(node->data)) {
        return true; // Duplicate found
    }

    set.insert(node->data);

    // Check left and right subtrees
    return check_tree_duplicates_recursive(node->left, set) || 
           check_tree_duplicates_recursive(node->right, set);
}

void check_tree_duplicates(TreeNode* root) {
    CustomHashSet set;
    bool duplicates_found = check_tree_duplicates_recursive(root, set);
    
    cout << "\n--- Q6. Check Binary Tree for Duplicate Values (using HashSet) ---" << endl;
    cout << "Output: " << (duplicates_found ? "true (Duplicates Found)" : "false (No Duplicates)") << endl;
}

// Helper to cleanup tree memory
void cleanup_tree(TreeNode* node) {
    if (node == nullptr) return;
    cleanup_tree(node->left);
    cleanup_tree(node->right);
    delete node;
}


int main() {
    // --- Data for Q1-Q4 ---
    const int arr1[] = {1, 2, 3, 1};
    check_duplicates(arr1, 4); // true

    const int arr2[] = {1, 2, 3, 4};
    const int arr3[] = {3, 4, 5, 6};
    find_common_elements(arr2, 4, arr3, 4); // 3, 4

    const int arr4[] = {2, 3, 2, 4, 3, 2};
    count_frequency(arr4, 6); // 2->3, 3->2, 4->1

    const int arr5[] = {4, 5, 1, 2, 0, 4, 1};
    find_first_non_repeating(arr5, 7); // 5

    // --- Data for Q5 ---
    test_q5_q6();

    // --- Data for Q6 ---
    // Tree 1: Duplicates (5, 5)
    TreeNode* tree1 = new TreeNode(10);
    tree1->left = new TreeNode(5);
    tree1->right = new TreeNode(15);
    tree1->left->left = new TreeNode(2);
    tree1->left->right = new TreeNode(5); // Duplicate
    check_tree_duplicates(tree1); // true
    cleanup_tree(tree1);

    // Tree 2: No Duplicates
    TreeNode* tree2 = new TreeNode(10);
    tree2->left = new TreeNode(5);
    tree2->right = new TreeNode(15);
    tree2->left->left = new TreeNode(2);
    tree2->left->right = new TreeNode(7); 
    check_tree_duplicates(tree2); // false
    cleanup_tree(tree2);

    return 0;
}
