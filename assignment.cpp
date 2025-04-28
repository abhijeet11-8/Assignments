#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <cstdlib>  // for rand() and srand()
#include <ctime>    // for time()

using namespace std;
using namespace chrono;

// Selection Sort
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        swap(arr[min_idx], arr[i]);
    }
}

// Insertion Sort
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

// Merge Sort
void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int i = 0; i < n2; i++) R[i] = arr[m + 1 + i];
    
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

// Function to generate random array
vector<int> generateRandomArray(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100000; // Random numbers up to 100000
    }
    return arr;
}

// Function to measure execution time
template<typename Func>
double measureTime(Func sortingFunction, vector<int> arr) {
    auto start = high_resolution_clock::now();
    sortingFunction(arr);
    auto stop = high_resolution_clock::now();
    duration<double> elapsed = stop - start;
    return elapsed.count(); // in seconds
}

int main() {
    srand(time(0));
    vector<int> inputSizes = {100, 500, 1000, 5000, 10000}; // Varying input sizes
    cout << "Input Size\tSelectionSort\tInsertionSort\tMergeSort\n";

    for (int size : inputSizes) {
        vector<int> arr = generateRandomArray(size);

        double time_selection = measureTime(selectionSort, arr);
        double time_insertion = measureTime(insertionSort, arr);
        double time_merge = measureTime([&](vector<int> a){ mergeSort(a, 0, a.size()-1); }, arr);

        cout << size << "\t\t"
             << time_selection << "s\t"
             << time_insertion << "s\t"
             << time_merge << "s\n";
    }

    return 0;
}