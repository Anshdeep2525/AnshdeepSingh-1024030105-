#include <iostream>

using namespace std;

// --- Node Structure (Used by all Questions) ---
struct Node {
    int data;
    Node* next;

    // Constructor for easy list creation in Q2, Q3, Q4 demos
    Node(int val) : data(val), next(nullptr) {}
    // Default constructor for Q1's createNode logic
    Node() : data(0), next(nullptr) {}
};

// Global head pointer for the Q1 Menu-Driven program
Node* headQ1 = nullptr;

// --- Utility Functions (Used for display and cleanup) ---

void printList(Node* head) {
    if (head == nullptr) {
        cout << "List is empty (NULL)";
        return;
    }
    Node* current = head;
    while (current != nullptr) {
        cout << current->data;
        if (current->next != nullptr) {
            cout << " -> ";
        }
        current = current->next;
    }
    cout << " -> NULL";
}

void cleanupList(Node*& head) {
    Node* current = head;
    Node* nextNode = nullptr;
    while (current != nullptr) {
        nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
}


// ==========================================================
// --- Q1: Menu Driven Program Operations ---
// ==========================================================

Node* createNodeQ1(int data) {
    Node* newNode = new Node();
    // Assuming successful allocation or using try/catch in a real environment
    newNode->data = data;
    newNode->next = nullptr;
    return newNode;
}

// (a) Insertion at the beginning
void insertAtBeginningQ1(int data) {
    Node* newNode = createNodeQ1(data);
    newNode->next = headQ1;
    headQ1 = newNode;
    cout << "Node " << data << " inserted at the beginning." << endl;
}

// (b) Insertion at the end
void insertAtEndQ1(int data) {
    Node* newNode = createNodeQ1(data);
    if (headQ1 == nullptr) {
        headQ1 = newNode;
        cout << "Node " << data << " inserted at the end." << endl;
        return;
    }
    Node* current = headQ1;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = newNode;
    cout << "Node " << data << " inserted at the end." << endl;
}

// (c) Insertion in between (before or after a node having a specific value)
void insertInBetweenQ1(int newData, int targetValue, bool insertAfter) {
    Node* newNode = createNodeQ1(newData);
    Node* current = headQ1;
    Node* prev = nullptr;
    bool found = false;

    while (current != nullptr) {
        if (current->data == targetValue) {
            found = true;
            break;
        }
        prev = current;
        current = current->next;
    }

    if (!found) {
        cout << "Error: Node with value " << targetValue << " not found." << endl;
        delete newNode;
        return;
    }

    if (insertAfter) {
        // Insert AFTER the target node (current)
        newNode->next = current->next;
        current->next = newNode;
        cout << "Node " << newData << " inserted AFTER node " << targetValue << "." << endl;
    } else {
        // Insert BEFORE the target node (current)
        if (prev == nullptr) {
            // Target is the head node
            newNode->next = headQ1;
            headQ1 = newNode;
        } else {
            // Target is in the middle
            newNode->next = current;
            prev->next = newNode;
        }
        cout << "Node " << newData << " inserted BEFORE node " << targetValue << "." << endl;
    }
}

// (d) Deletion from the beginning
void deleteFromBeginningQ1() {
    if (headQ1 == nullptr) {
        cout << "List is empty. Cannot delete." << endl;
        return;
    }
    Node* temp = headQ1;
    headQ1 = headQ1->next;
    cout << "Deleted node with value: " << temp->data << " from the beginning." << endl;
    delete temp;
}

// (e) Deletion from the end
void deleteFromEndQ1() {
    if (headQ1 == nullptr) {
        cout << "List is empty. Cannot delete." << endl;
        return;
    }
    if (headQ1->next == nullptr) {
        // Only one node
        cout << "Deleted node with value: " << headQ1->data << " from the end." << endl;
        delete headQ1;
        headQ1 = nullptr;
        return;
    }
    Node* current = headQ1;
    Node* prev = nullptr;
    while (current->next != nullptr) {
        prev = current;
        current = current->next;
    }
    prev->next = nullptr;
    cout << "Deleted node with value: " << current->data << " from the end." << endl;
    delete current;
}

// (f) Deletion of a specific node
void deleteSpecificNodeQ1(int targetValue) {
    if (headQ1 == nullptr) {
        cout << "List is empty. Cannot delete." << endl;
        return;
    }

    Node* current = headQ1;
    Node* prev = nullptr;

    // Case 1: Target is the head node
    if (current != nullptr && current->data == targetValue) {
        headQ1 = current->next;
        cout << "Deleted node with value: " << current->data << "." << endl;
        delete current;
        return;
    }

    // Search for the target node
    while (current != nullptr && current->data != targetValue) {
        prev = current;
        current = current->next;
    }

    // Case 2: Target not found
    if (current == nullptr) {
        cout << "Error: Node with value " << targetValue << " not found." << endl;
        return;
    }

    // Case 3: Target found in the middle or end
    prev->next = current->next;
    cout << "Deleted node with value: " << current->data << "." << endl;
    delete current;
}

// (g) Search for a node and display its position from head
void searchNodeQ1(int targetValue) {
    if (headQ1 == nullptr) {
        cout << "List is empty. Search failed." << endl;
        return;
    }
    Node* current = headQ1;
    int position = 1;

    while (current != nullptr) {
        if (current->data == targetValue) {
            cout << "Node with value " << targetValue << " found at position " << position << "." << endl;
            return;
        }
        current = current->next;
        position++;
    }

    cout << "Node with value " << targetValue << " not found in the list." << endl;
}

// (h) Display all the node values
void displayListQ1() {
    cout << "Q1 Linked List: ";
    printList(headQ1);
    cout << endl;
}

// ==========================================================
// --- Q2: Delete All Occurrences ---
// ==========================================================

int deleteAllOccurrences(Node*& head, int key) {
    if (head == nullptr) {
        return 0;
    }

    int count = 0;
    Node* current = head;
    
    // 1. Handle occurrences at the beginning
    while (current != nullptr && current->data == key) {
        Node* temp = current;
        head = current->next;
        current = head;
        delete temp;
        count++;
    }

    if (head == nullptr) {
        return count;
    }

    // 2. Handle occurrences in the middle and end
    Node* prev = head;
    current = head->next;

    while (current != nullptr) {
        if (current->data == key) {
            Node* temp = current;
            prev->next = current->next; // Bypass the node
            current = current->next;    // Move current
            delete temp;
            count++;
        } else {
            prev = current;             // Advance prev
            current = current->next;
        }
    }

    return count;
}

// ==========================================================
// --- Q3: Find Middle Node ---
// ==========================================================

Node* findMiddle(Node* head) {
    if (head == nullptr) {
        return nullptr;
    }

    Node* slow = head;
    Node* fast = head;

    // Fast pointer moves twice as fast as slow
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow; // Slow is at the middle element
}

// ==========================================================
// --- Q4: Reverse a Linked List ---
// ==========================================================

Node* reverseList(Node* head) {
    Node* prev = nullptr;
    Node* current = head;
    Node* nextNode = nullptr;

    while (current != nullptr) {
        nextNode = current->next; // Store next
        current->next = prev;     // Reverse pointer
        prev = current;           // Move prev
        current = nextNode;       // Move current
    }

    return prev; // New head of the reversed list
}

// ==========================================================
// --- Main Program ---
// ==========================================================

void runQ1Menu() {
    cleanupList(headQ1); // Ensure Q1 list starts clean
    insertAtBeginningQ1(10);
    insertAtBeginningQ1(20);
    insertAtEndQ1(30);
    insertAtEndQ1(40);
    displayListQ1();

    int choice, data, target;
    bool insertAfter;

    do {
        cout << "\n--- Q1: Singly Linked List Menu ---" << endl;
        cout << "1. Insert at Beginning (a)" << endl;
        cout << "2. Insert at End (b)" << endl;
        cout << "3. Insert In Between (Before/After Target) (c)" << endl;
        cout << "4. Delete from Beginning (d)" << endl;
        cout << "5. Delete from End (e)" << endl;
        cout << "6. Delete Specific Node by Value (f)" << endl;
        cout << "7. Search Node and Display Position (g)" << endl;
        cout << "8. Display List (h)" << endl;
        cout << "9. Exit Q1 Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter data to insert at beginning: ";
                cin >> data;
                insertAtBeginningQ1(data);
                break;
            case 2:
                cout << "Enter data to insert at end: ";
                cin >> data;
                insertAtEndQ1(data);
                break;
            case 3:
                cout << "Enter new data to insert: ";
                cin >> data;
                cout << "Enter target value to insert relative to: ";
                cin >> target;
                cout << "Insert AFTER target (1) or BEFORE target (0)? ";
                cin >> insertAfter;
                insertInBetweenQ1(data, target, insertAfter);
                break;
            case 4:
                deleteFromBeginningQ1();
                break;
            case 5:
                deleteFromEndQ1();
                break;
            case 6:
                cout << "Enter value of node to delete: ";
                cin >> target;
                deleteSpecificNodeQ1(target);
                break;
            case 7:
                cout << "Enter value of node to search: ";
                cin >> target;
                searchNodeQ1(target);
                break;
            case 8:
                displayListQ1();
                break;
            case 9:
                cout << "Exiting Q1 Menu..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 9);
}

void runQ2Demo() {
    cout << "\n--- Q2: Delete All Occurrences Demo ---" << endl;
    // Input: 1->2->1->2->1->3->1, key: 1
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(1);
    head->next->next->next = new Node(2);
    head->next->next->next->next = new Node(1);
    head->next->next->next->next->next = new Node(3);
    head->next->next->next->next->next->next = new Node(1);

    int key = 1;
    cout << "Original List: ";
    printList(head);
    cout << "\nKey to delete: " << key << endl;

    int count = deleteAllOccurrences(head, key);

    cout << "Count: " << count << endl;
    cout << "Updated List: ";
    printList(head);
    cout << "\n(Expected: 2 -> 2 -> 3 -> NULL)" << endl;

    cleanupList(head);
}

void runQ3Demo() {
    cout << "\n--- Q3: Find Middle Node Demo ---" << endl;

    // Odd length list
    Node* head1 = new Node(1);
    head1->next = new Node(2);
    head1->next->next = new Node(3);
    head1->next->next->next = new Node(4);
    head1->next->next->next->next = new Node(5);

    cout << "Input List (Odd length): ";
    printList(head1);
    Node* middle1 = findMiddle(head1);
    cout << "\nOutput: " << (middle1 ? to_string(middle1->data) : "NULL") << " (Expected: 3)" << endl;
    cleanupList(head1);

    // Even length list
    Node* head2 = new Node(10);
    head2->next = new Node(20);
    head2->next->next = new Node(30);
    head2->next->next->next = new Node(40);

    cout << "\nInput List (Even length): ";
    printList(head2);
    Node* middle2 = findMiddle(head2);
    cout << "\nOutput: " << (middle2 ? to_string(middle2->data) : "NULL") << " (Expected: 30)" << endl;
    cleanupList(head2);
}

void runQ4Demo() {
    cout << "\n--- Q4: Reverse Linked List Demo ---" << endl;
    // Input: 1->2->3->4->NULL
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);

    cout << "Original List: ";
    printList(head);

    Node* reversedHead = reverseList(head);

    cout << "\nReversed List: ";
    printList(reversedHead);
    cout << "\n(Expected: 4 -> 3 -> 2 -> 1 -> NULL)" << endl;

    cleanupList(reversedHead);
}

int main() {
    int mainChoice;

    do {
        cout << "\n=========================================" << endl;
        cout << "  Singly Linked List Assignment Solver" << endl;
        cout << "=========================================" << endl;
        cout << "1. Run Q1: Menu Driven SLL Operations" << endl;
        cout << "2. Run Q2: Delete All Occurrences Demo" << endl;
        cout << "3. Run Q3: Find Middle Node Demo" << endl;
        cout << "4. Run Q4: Reverse Linked List Demo" << endl;
        cout << "5. Exit Program" << endl;
        cout << "Enter your choice (1-5): ";
        cin >> mainChoice;

        switch (mainChoice) {
            case 1:
                runQ1Menu();
                break;
            case 2:
                runQ2Demo();
                break;
            case 3:
                runQ3Demo();
                break;
            case 4:
                runQ4Demo();
                break;
            case 5:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (mainChoice != 5);

    // Final cleanup of Q1 list just in case
    cleanupList(headQ1);

    return 0;
}
