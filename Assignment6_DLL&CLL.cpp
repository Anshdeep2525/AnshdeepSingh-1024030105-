#include <iostream>
#include <string>

using namespace std;

// ==========================================================
// --- DOUBLY LINKED LIST (DLL) STRUCTURE ---
// ==========================================================

struct DLLNode {
    char data; // Using char for Q4 (Palindrome), but compatible with other operations
    DLLNode* prev;
    DLLNode* next;

    DLLNode(char val) : data(val), prev(nullptr), next(nullptr) {}
};

// Global DLL head for the menu program (Q1)
DLLNode* headDLL = nullptr;

// ==========================================================
// --- CIRCULAR LINKED LIST (CLL) STRUCTURE ---
// ==========================================================

struct CLLNode {
    int data;
    CLLNode* next;

    CLLNode(int val) : data(val), next(nullptr) {}
};

// Global CLL head (used for separate CLL demo/tests)
CLLNode* headCLL = nullptr;

// ==========================================================
// --- UTILITY FUNCTIONS ---
// ==========================================================

/**
 * @brief Utility for DLL printing (supports both int and char data display).
 */
void printDLL(DLLNode* head) {
    if (head == nullptr) {
        cout << "List is empty (NULL)";
        return;
    }
    DLLNode* current = head;
    while (current != nullptr) {
        cout << current->data;
        if (current->next != nullptr) {
            cout << " <=> ";
        }
        current = current->next;
    }
    cout << " <=> NULL";
}

/**
 * @brief Utility for DLL cleanup.
 */
void cleanupDLL(DLLNode*& head) {
    DLLNode* current = head;
    DLLNode* nextNode = nullptr;
    while (current != nullptr) {
        nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
}

/**
 * @brief Utility for CLL cleanup.
 */
void cleanupCLL(CLLNode*& head) {
    if (head == nullptr) return;
    CLLNode* current = head->next;
    while (current != head) {
        CLLNode* temp = current;
        current = current->next;
        delete temp;
    }
    delete head; // Delete the head node itself
    head = nullptr;
}

// ==========================================================
// --- Q1: MENU-DRIVEN DOUBLY LINKED LIST (DLL) OPERATIONS ---
// ==========================================================

// --- Q1(a): DLL Insertion ---

// Insert at the beginning (First node)
void insertDLLAtBeginning(char data) {
    DLLNode* newNode = new DLLNode(data);
    if (headDLL == nullptr) {
        headDLL = newNode;
    } else {
        newNode->next = headDLL;
        headDLL->prev = newNode;
        headDLL = newNode;
    }
    cout << "Node '" << data << "' inserted at the beginning." << endl;
}

// Insert at the end (Last node)
void insertDLLAtEnd(char data) {
    DLLNode* newNode = new DLLNode(data);
    if (headDLL == nullptr) {
        headDLL = newNode;
        return;
    }
    DLLNode* current = headDLL;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = newNode;
    newNode->prev = current;
    cout << "Node '" << data << "' inserted at the end." << endl;
}

// Insert after a specific node
void insertDLLAfter(char newData, char targetData) {
    DLLNode* current = headDLL;
    while (current != nullptr && current->data != targetData) {
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Error: Target node '" << targetData << "' not found." << endl;
        return;
    }

    DLLNode* newNode = new DLLNode(newData);
    newNode->next = current->next;
    newNode->prev = current;
    if (current->next != nullptr) {
        current->next->prev = newNode;
    }
    current->next = newNode;
    cout << "Node '" << newData << "' inserted AFTER node '" << targetData << "'." << endl;
}

// Insert before a specific node
void insertDLLBefore(char newData, char targetData) {
    DLLNode* current = headDLL;
    while (current != nullptr && current->data != targetData) {
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Error: Target node '" << targetData << "' not found." << endl;
        return;
    }

    // Handle case where target is the head
    if (current == headDLL) {
        insertDLLAtBeginning(newData);
        return;
    }

    DLLNode* newNode = new DLLNode(newData);
    // Link new node
    newNode->next = current;
    newNode->prev = current->prev;

    // Update neighboring nodes
    current->prev->next = newNode;
    current->prev = newNode;
    cout << "Node '" << newData << "' inserted BEFORE node '" << targetData << "'." << endl;
}


// --- Q1(b): DLL Deletion of a specific node ---

void deleteDLLSpecificNode(char targetData) {
    if (headDLL == nullptr) {
        cout << "List is empty. Cannot delete." << endl;
        return;
    }

    DLLNode* current = headDLL;
    while (current != nullptr && current->data != targetData) {
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Error: Node '" << targetData << "' not found." << endl;
        return;
    }

    // Case 1: Deleting the Head
    if (current == headDLL) {
        headDLL = current->next;
        if (headDLL != nullptr) {
            headDLL->prev = nullptr;
        }
    }
    // Case 2: Deleting the Tail
    else if (current->next == nullptr) {
        current->prev->next = nullptr;
    }
    // Case 3: Deleting a Middle Node
    else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
    }

    cout << "Deleted node with value: '" << current->data << "'." << endl;
    delete current;
}


// --- Q1(c): DLL Search for a node ---

void searchDLLNode(char targetData) {
    if (headDLL == nullptr) {
        cout << "List is empty. Search failed." << endl;
        return;
    }
    DLLNode* current = headDLL;
    int position = 1;

    while (current != nullptr) {
        if (current->data == targetData) {
            cout << "Node '" << targetData << "' found at position " << position << " (from head)." << endl;
            return;
        }
        current = current->next;
        position++;
    }

    cout << "Node '" << targetData << "' not found in the list." << endl;
}

// ==========================================================
// --- Q2: Display all CLL node values (repeating head at end) ---
// ==========================================================

// Helper function to create a sample CLL
CLLNode* createSampleCLL(const int values[], int size) {
    if (size == 0) return nullptr;
    CLLNode* head = new CLLNode(values[0]);
    CLLNode* current = head;
    for (int i = 1; i < size; ++i) {
        current->next = new CLLNode(values[i]);
        current = current->next;
    }
    current->next = head; // Make it circular
    return head;
}

void displayCLL(CLLNode* head) {
    if (head == nullptr) {
        cout << "Circular Linked List is empty." << endl;
        return;
    }
    CLLNode* current = head;
    do {
        cout << current->data << " ";
        current = current->next;
    } while (current != head);

    // Q2 Requirement: repeating value of head node at the end too.
    cout << head->data << ". (Head repetition)" << endl;
}

// ==========================================================
// --- Q3: Find Size of DLL and CLL ---
// ==========================================================

// Q3(i): Size of Doubly Linked List
int findSizeDLL(DLLNode* head) {
    int count = 0;
    DLLNode* current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

// Q3(ii): Size of Circular Linked List
int findSizeCLL(CLLNode* head) {
    if (head == nullptr) {
        return 0;
    }
    int count = 0;
    CLLNode* current = head;
    do {
        count++;
        current = current->next;
    } while (current != head);
    return count;
}

// ==========================================================
// --- Q4: Check if DLL of characters is Palindrome ---
// ==========================================================

// Requires the DLL to be created with characters (as done in the menu)
bool isDLLPalindrome(DLLNode* head) {
    if (head == nullptr) {
        return true; // An empty list is a palindrome
    }

    // 1. Find the tail of the list
    DLLNode* tail = head;
    while (tail->next != nullptr) {
        tail = tail->next;
    }

    // 2. Use two pointers: one from head (forward) and one from tail (backward)
    DLLNode* forward = head;
    DLLNode* backward = tail;

    // We only need to check up to the middle.
    // The condition forward != backward handles odd lengths.
    // The condition forward->prev != backward handles even lengths (stopping when they cross).
    while (forward != backward && forward->prev != backward) {
        if (forward->data != backward->data) {
            return false;
        }
        forward = forward->next;
        backward = backward->prev;
    }

    return true;
}

// ==========================================================
// --- Q5: Check if a Linked List is Circular Linked List or not ---
// ==========================================================

// This function checks if a general linked list (Singly, DLL, or CLL structure) is circular.
// It uses the slow/fast pointer (Floyd's cycle-finding) algorithm.
bool isCircularLinkedList(CLLNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return false; // Not a loop if 0 or 1 node.
    }

    CLLNode* slow = head;
    CLLNode* fast = head->next;

    while (fast != nullptr && fast->next != nullptr) {
        if (slow == fast) {
            return true; // Collision found, list is circular/has a loop
        }
        slow = slow->next;      // Moves 1 step
        fast = fast->next->next; // Moves 2 steps
    }

    return false; // Fast pointer reached the end (NULL), no cycle found
}


// ==========================================================
// --- Main Program and Demo Drivers ---
// ==========================================================

// Driver function for Q1 Menu (DLL Operations)
void runQ1Menu() {
    cout << "\n=========================================" << endl;
    cout << "  Q1: DOUBLY LINKED LIST (DLL) OPERATIONS" << endl;
    cout << "=========================================" << endl;

    cleanupDLL(headDLL);
    cout << "Initializing DLL with 'L', 'E', 'V', 'E', 'L' (Ready for Palindrome check)..." << endl;
    
    // Create 'LEVEL' structure (L <=> E <=> V <=> E <=> L)
    insertDLLAtBeginning('L'); // L
    insertDLLAtEnd('L');       // L <-> L
    insertDLLBefore('E', 'L'); // E <-> L <-> L
    insertDLLAfter('V', 'E');  // E <-> V <-> L <-> L
    deleteDLLSpecificNode('L'); // Delete first L (E <-> V <-> L)
    insertDLLAtBeginning('L'); // L <-> E <-> V <-> L
    insertDLLAfter('E', 'L'); // L <-> E <-> E <-> V <-> L (Corrected Palindrome word for demo)

    char choice;
    char data, target;
    int op;

    do {
        cout << "\n--- Current DLL: ";
        printDLL(headDLL);
        cout << " ---" << endl;
        cout << "\n[1] Insertion Menu (Q1a)" << endl;
        cout << "[2] Delete Specific Node (Q1b)" << endl;
        cout << "[3] Search for Node (Q1c)" << endl;
        cout << "[9] Exit DLL Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                cout << "  [1] Insert at Beginning" << endl;
                cout << "  [2] Insert at End" << endl;
                cout << "  [3] Insert AFTER Target" << endl;
                cout << "  [4] Insert BEFORE Target" << endl;
                cout << "  Enter insertion choice: ";
                if (!(cin >> op)) { cin.clear(); cin.ignore(10000, '\n'); op = 0; } // Handle non-int input

                cout << "  Enter data (char) to insert: ";
                if (!(cin >> data)) { cin.clear(); cin.ignore(10000, '\n'); break; }

                if (op == 1) insertDLLAtBeginning(data);
                else if (op == 2) insertDLLAtEnd(data);
                else {
                    cout << "  Enter target data (char): ";
                    if (!(cin >> target)) { cin.clear(); cin.ignore(10000, '\n'); break; }

                    if (op == 3) insertDLLAfter(data, target);
                    else if (op == 4) insertDLLBefore(data, target);
                    else cout << "  Invalid insertion choice." << endl;
                }
                break;
            case '2':
                cout << "Enter data (char) of node to delete: ";
                if (!(cin >> target)) { cin.clear(); cin.ignore(10000, '\n'); break; }
                deleteDLLSpecificNode(target);
                break;
            case '3':
                cout << "Enter data (char) of node to search: ";
                if (!(cin >> target)) { cin.clear(); cin.ignore(10000, '\n'); break; }
                searchDLLNode(target);
                break;
            case '9':
                cout << "Exiting DLL Menu..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != '9');
}

// Driver function for Q2, Q3, Q4, Q5 Demos
void runDemos() {
    // --- Q2 Demo ---
    cout << "\n=========================================" << endl;
    cout << "  Q2: CIRCULAR LINKED LIST DISPLAY" << endl;
    cout << "=========================================" << endl;
    cleanupCLL(headCLL);
    int values[] = {20, 100, 40, 80, 60};
    // The size of the array is 5.
    headCLL = createSampleCLL(values, 5);
    cout << "Input: 20 -> 100 -> 40 -> 80 -> 60 (Circular)" << endl;
    cout << "Output: ";
    displayCLL(headCLL);
    cout << "(Expected: 20 100 40 80 60 20)" << endl;

    // --- Q3 Demo ---
    cout << "\n=========================================" << endl;
    cout << "  Q3: FIND SIZE (DLL and CLL)" << endl;
    cout << "=========================================" << endl;
    cout << "Current DLL Size (from Q1 Menu): " << findSizeDLL(headDLL) << endl;
    cout << "Current CLL Size (from Q2 Demo): " << findSizeCLL(headCLL) << endl;

    // --- Q4 Demo ---
    cout << "\n=========================================" << endl;
    cout << "  Q4: DLL PALINDROME CHECK" << endl;
    cout << "=========================================" << endl;

    // Test 1: Palindrome (LEVEL)
    DLLNode* palindromeHead = new DLLNode('L');
    DLLNode* p2 = new DLLNode('E'); p2->prev = palindromeHead; palindromeHead->next = p2;
    DLLNode* p3 = new DLLNode('V'); p3->prev = p2; p2->next = p3;
    DLLNode* p4 = new DLLNode('E'); p4->prev = p3; p3->next = p4;
    DLLNode* p5 = new DLLNode('L'); p5->prev = p4; p4->next = p5;
    DLLNode* palindromeTail = p5; // Not used in check, just for reference

    cout << "Test 1 (LEVEL): ";
    printDLL(palindromeHead);
    cout << "\nIs Palindrome? " << (isDLLPalindrome(palindromeHead) ? "True" : "False") << endl;
    cleanupDLL(palindromeHead);

    // Test 2: Non-Palindrome (HELLO)
    DLLNode* nonPalindromeHead = new DLLNode('H');
    DLLNode* n2 = new DLLNode('E'); n2->prev = nonPalindromeHead; nonPalindromeHead->next = n2;
    DLLNode* n3 = new DLLNode('L'); n3->prev = n2; n2->next = n3;
    DLLNode* n4 = new DLLNode('L'); n4->prev = n3; n3->next = n4;
    DLLNode* n5 = new DLLNode('O'); n5->prev = n4; n4->next = n5;

    cout << "\nTest 2 (HELLO): ";
    printDLL(nonPalindromeHead);
    cout << "\nIs Palindrome? " << (isDLLPalindrome(nonPalindromeHead) ? "True" : "False") << endl;
    cleanupDLL(nonPalindromeHead);


    // --- Q5 Demo ---
    cout << "\n=========================================" << endl;
    cout << "  Q5: CHECK IF LINKED LIST IS CIRCULAR" << endl;
    cout << "=========================================" << endl;

    // Test 1: Circular List (from Q2 demo)
    cout << "Test 1 (Circular List): ";
    cout << (isCircularLinkedList(headCLL) ? "True" : "False") << endl;
    // Cleanup Q2/Q5 CLL
    cleanupCLL(headCLL);

    // Test 2: Non-Circular (Singly List structure ending in NULL)
    CLLNode* nonCircularHead = new CLLNode(2);
    CLLNode* nc2 = new CLLNode(4); nonCircularHead->next = nc2;
    CLLNode* nc3 = new CLLNode(6); nc2->next = nc3;
    nc3->next = nullptr; // End is NULL

    cout << "Test 2 (Non-Circular List): ";
    cout << (isCircularLinkedList(nonCircularHead) ? "True" : "False") << endl;

    // Manual cleanup for non-circular list
    delete nc3;
    delete nc2;
    delete nonCircularHead;

    // Test 3: Looped List (non-standard for a CLL, but useful for testing the check function)
    CLLNode* loopedHead = new CLLNode(1);
    CLLNode* l2 = new CLLNode(2); loopedHead->next = l2;
    CLLNode* l3 = new CLLNode(3); l2->next = l3;
    l3->next = l2; // Creates a loop: 1 -> 2 -> 3 -> 2 -> 3 -> ...

    cout << "Test 3 (Looped List): ";
    cout << (isCircularLinkedList(loopedHead) ? "True" : "False") << endl;

    // Manual cleanup for looped list (must break loop first)
    l3->next = nullptr;
    delete l3;
    delete l2;
    delete loopedHead;
}

int main() {
    int mainChoice;

    // Input validation loop for main menu
    do {
        cout << "\n=========================================" << endl;
        cout << "  Lab Assignment 6 Solver (DLL & CLL)" << endl;
        cout << "=========================================" << endl;
        cout << "1. Run Q1: DLL Menu Operations" << endl;
        cout << "2. Run Q2, Q3, Q4, Q5 Demos" << endl;
        cout << "3. Exit Program" << endl;
        cout << "Enter your choice (1-3): ";

        if (!(cin >> mainChoice)) {
            cout << "Invalid input. Please enter a number (1, 2, or 3)." << endl;
            cin.clear(); // Clear the error flags
            cin.ignore(10000, '\n'); // Discard invalid input
            mainChoice = 0; // Set choice to an invalid value to force loop continuation
            continue;
        }

        switch (mainChoice) {
            case 1:
                runQ1Menu();
                break;
            case 2:
                runDemos();
                break;
            case 3:
                cout << "Exiting program. Cleaning up memory..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (mainChoice != 3);

    // Final cleanup
    cleanupDLL(headDLL);
    cleanupCLL(headCLL);

    return 0;
}
