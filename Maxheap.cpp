#include <iostream>
#include <vector>
using namespace std;

class MaxHeap {
private:
    vector<int> heap;

    // Returns index of left child
    int left(int i) { return 2 * i + 1; }

    // Returns index of right child
    int right(int i) { return 2 * i + 2; }

    // Returns index of parent
    int parent(int i) { return (i - 1) / 2; }

    // Max-Heapify function
    void maxHeapify(int i) {
        int l = left(i);
        int r = right(i);
        int largest = i;

        if (l < heap.size() && heap[l] > heap[largest])
            largest = l;
        if (r < heap.size() && heap[r] > heap[largest])
            largest = r;
        if (largest != i) {
            swap(heap[i], heap[largest]);
            maxHeapify(largest);
        }
    }

public:
    // Returns maximum element
    int max() {
        if (heap.empty()) {
            cout << "Heap is empty!" << endl;
            return -1;
        }
        return heap[0];
    }

    // Removes and returns maximum element
    int removeMax() {
        if (heap.empty()) return -1;
        int maxVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        maxHeapify(0);
        return maxVal;
    }

    // Inserts an element into the heap
    void insert(int x) {
        heap.push_back(x);
        int i = heap.size() - 1;

        while (i > 0 && heap[parent(i)] < heap[i]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    // Increases key value of node at index i
    void increaseKey(int i, int k) {
        if (i >= heap.size() || k < heap[i]) return;
        heap[i] = k;
        while (i > 0 && heap[parent(i)] < heap[i]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    // Builds max heap from given array
    void buildHeap(vector<int> &arr) {
        heap = arr;
        for (int i = heap.size() / 2 - 1; i >= 0; i--) {
            maxHeapify(i);
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
    MaxHeap h;

    h.insert(10);
    h.insert(20);
    h.insert(15);
    h.insert(30);
    h.insert(40);

    cout << "Heap after insertions: ";
    h.printHeap();

    cout << "Max Element: " << h.max() << endl;

    cout << "Extracted Max: " << h.removeMax() << endl;
    cout << "Heap after extraction: ";
    h.printHeap();

    vector<int> arr = {3, 5, 9, 6, 8, 20, 10, 12, 18, 9};
    h.buildHeap(arr);
    cout << "Heap after buildHeap: ";
    h.printHeap();

    h.increaseKey(3, 22);
    cout << "Heap after increaseKey(3, 22): ";
    h.printHeap();

    return 0;
}