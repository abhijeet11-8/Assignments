#include <iostream>
#include <vector>
using namespace std;

class MinHeap {
private:
    vector<int> heap;

    // Returns index of left child
    int left(int i) { return 2 * i + 1; }

    // Returns index of right child
    int right(int i) { return 2 * i + 2; }

    // Returns index of parent
    int parent(int i) { return (i - 1) / 2; }

    // Min-Heapify function
    void minHeapify(int i) {
        int l = left(i);
        int r = right(i);
        int smallest = i;

        if (l < heap.size() && heap[l] < heap[smallest])
            smallest = l;
        if (r < heap.size() && heap[r] < heap[smallest])
            smallest = r;
        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            minHeapify(smallest);
        }
    }

public:
    // Returns minimum element
    int min() {
        if (heap.empty()) {
            cout << "Heap is empty!" << endl;
            return -1;
        }
        return heap[0];
    }

    // Removes and returns minimum element
    int removeMin() {
        if (heap.empty()) return -1;
        int minVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        minHeapify(0);
        return minVal;
    }

    // Inserts an element into the heap
    void insert(int x) {
        heap.push_back(x);
        int i = heap.size() - 1;

        while (i > 0 && heap[parent(i)] > heap[i]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    // Decreases key value of node at index i
    void decreaseKey(int i, int k) {
        if (i >= heap.size() || k > heap[i]) return;
        heap[i] = k;
        while (i > 0 && heap[parent(i)] > heap[i]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    // Builds min heap from given array
    void buildHeap(vector<int> &arr) {
        heap = arr;
        for (int i = heap.size() / 2 - 1; i >= 0; i--) {
            minHeapify(i);
        }
    }

    // Returns the size of heap
    int length() { return heap.size(); }

    // Prints the heap
    void printHeap() {
        for (int num : heap) cout << num << " ";
        cout << endl;
    }
};

int main() {
    MinHeap h;

    h.insert(10);
    h.insert(20);
    h.insert(15);
    h.insert(30);
    h.insert(40);

    cout << "Heap after insertions: ";
    h.printHeap();

    cout << "Min Element: " << h.min() << endl;

    cout << "Extracted Min: " << h.removeMin() << endl;
    cout << "Heap after extraction: ";
    h.printHeap();

    vector<int> arr = {3, 5, 9, 6, 8, 20, 10, 12, 18, 9};
    h.buildHeap(arr);
    cout << "Heap after buildHeap: ";
    h.printHeap();

    h.decreaseKey(3, 2);
    cout << "Heap after decreaseKey(3, 2): ";
    h.printHeap();

    return 0;
}