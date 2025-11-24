#include <iostream>

using namespace std;

// Forward declarations for array-based functions
void printArray(const int arr[], int n, const string& title = "Array");
void swapElements(int& a, int& b);
void selectionSort(int arr[], int n);
void insertionSort(int arr[], int n);
void bubbleSort(int arr[], int n);
void merge(int arr[], int left, int mid, int right);
void mergeSort(int arr[], int left, int right);
void quickSort(int arr[], int low, int high);
void improvedSelectionSort(int arr[], int n);


// Function to swap two integer elements manually
void swapElements(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Function to print the array elements
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

// ==========================================================
// --- Q1: Standard Sorting Techniques (Array-based) ---
// ==========================================================

// --- Q1(a): Selection Sort ---
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        int min_idx = i;
        // Find the minimum element in the remaining unsorted array
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        // Swap the found minimum element with the current element at i
        swapElements(arr[i], arr[min_idx]);
    }
}

// --- Q1(b): Insertion Sort ---
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        // Move elements of arr[0..i-1], that are greater than key, 
        // to one position ahead of their current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// --- Q1(c): Bubble Sort ---
void bubbleSort(int arr[], int n) {
    bool swapped;
    for (int i = 0; i < n - 1; ++i) {
        swapped = false;
        for (int j = 0; j < n - 1 - i; ++j) {
            // Compare adjacent elements
            if (arr[j] > arr[j + 1]) {
                swapElements(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        // If no two elements were swapped by inner loop, then array is sorted
        if (swapped == false)
            break;
    }
}

// --- Q1(d): Merge Sort Helper (Merge) ---
// Merges two subarrays of arr[]. First subarray is arr[left..mid]. Second subarray is arr[mid+1..right].
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary C-style arrays
    int L[n1];
    int R[n2];

    // Copy data to temp arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge the temp arrays back into arr[left..right]
    int i = 0; 
    int j = 0; 
    int k = left; 

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// --- Q1(d): Merge Sort Main Function ---
void mergeSort(int arr[], int left, int right) {
    if (left >= right) {
        return; // Base case: array size 1 or less
    }
    int mid = left + (right - left) / 2;
    // Sort first and second halves
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    // Merge the sorted halves
    merge(arr, left, mid, right);
}

// --- Q1(e): Quick Sort Helper (Partition) ---
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // Pivot is the last element
    int i = (low - 1); // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
            i++; // Increment index of smaller element
            swapElements(arr[i], arr[j]);
        }
    }
    swapElements(arr[i + 1], arr[high]);
    return (i + 1);
}

// --- Q1(e): Quick Sort Main Function ---
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // pi is partitioning index, arr[pi] is now at right place
        int pi = partition(arr, low, high);

        // Separately sort elements before partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


// ==========================================================
// --- Q2: Improved Bidirectional Selection Sort ---
// ==========================================================

// Finds both minimum and maximum in one pass and swaps them to the correct 
// boundary positions (i and j) of the unsorted subarray.
void improvedSelectionSort(int arr[], int n) {
    // i starts from the beginning (for min), j starts from the end (for max)
    for (int i = 0, j = n - 1; i < j; ++i, --j) {
        int min_idx = i;
        int max_idx = i;
        
        // Find min and max indices in the unsorted subarray arr[i...j]
        for (int k = i + 1; k <= j; ++k) {
            if (arr[k] < arr[min_idx]) {
                min_idx = k;
            }
            if (arr[k] > arr[max_idx]) {
                max_idx = k;
            }
        }

        // 1. Swap the found minimum (at min_idx) with the element at the left boundary 'i'
        if (min_idx != i) {
            swapElements(arr[i], arr[min_idx]);
        }

        // 2. IMPORTANT: If the original maximum element was at 'i' (max_idx == i), 
        // it was just moved to 'min_idx' by the swap in step 1. We must update max_idx 
        // to point to its new location before performing the second swap.
        if (max_idx == i) {
            max_idx = min_idx;
        }

        // 3. Swap the found maximum (at max_idx) with the element at the right boundary 'j'
        if (max_idx != j) {
            swapElements(arr[j], arr[max_idx]);
        }
    }
}

// ==========================================================
// --- Main Function and Demonstration ---
// ==========================================================

// Helper function to run the demo for Q1 sorting functions
void runSortDemo(const string& name, void (*sortFunc)(int[], int), int arr[], int n) {
    // Create a temporary array to hold the original data for the demo
    int temp_arr[n];
    for (int i = 0; i < n; ++i) {
        temp_arr[i] = arr[i];
    }

    cout << "\n--- Running " << name << " ---" << endl;
    printArray(temp_arr, n, "Original");
    
    // Call the sorting function
    // For Merge Sort and Quick Sort, we need special wrappers to call the 
    // recursive function with the correct initial bounds (0 and n-1)
    if (name.find("Merge") != string::npos) {
        mergeSort(temp_arr, 0, n - 1);
    } else if (name.find("Quick") != string::npos) {
        quickSort(temp_arr, 0, n - 1);
    } else {
        sortFunc(temp_arr, n);
    }
    
    printArray(temp_arr, n, "Sorted");
}

int main() {
    int test_arr[] = {64, 25, 12, 22, 11, 75, 5, 33};
    int n = sizeof(test_arr) / sizeof(test_arr[0]);

    cout << "=======================================================" << endl;
    cout << "  Lab Assignment 7: Sorting Techniques (Q1)" << endl;
    cout << "=======================================================" << endl;

    // Q1 Demos:
    runSortDemo("Selection Sort (Q1a)", selectionSort, test_arr, n);
    runSortDemo("Insertion Sort (Q1b)", insertionSort, test_arr, n);
    runSortDemo("Bubble Sort (Q1c)", bubbleSort, test_arr, n);
    
    // Quick and Merge Sort wrappers are handled inside runSortDemo based on name
    runSortDemo("Merge Sort (Q1d)", nullptr, test_arr, n);
    runSortDemo("Quick Sort (Q1e)", nullptr, test_arr, n);

    cout << "\n=======================================================" << endl;
    cout << "  Improved Bidirectional Selection Sort (Q2)" << endl;
    cout << "=======================================================" << endl;
    
    // Q2 Demo: Improved Selection Sort
    int arr_q2[] = {64, 25, 12, 22, 11, 75, 5, 33};
    int n_q2 = sizeof(arr_q2) / sizeof(arr_q2[0]);

    cout << "The Improved Selection Sort finds MIN and MAX in one pass and sorts from both ends." << endl;
    printArray(arr_q2, n_q2, "Original");
    
    improvedSelectionSort(arr_q2, n_q2);
    
    printArray(arr_q2, n_q2, "Sorted (Q2)");

    return 0;
}
