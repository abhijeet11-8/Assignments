#include <iostream>
#include <vector>
using namespace std;

class MaxHeap{
    private:
    vector<int> heap;
    void Heapifyup(int index) {
        while (index > 0 && heap[index] > heap[parent(index)]){
            swap(heap[index], heap[parent(index)]);
            index = parent(index);
        }
    }
     void Heapifydown(int index){
        int size = heap.size();
        while (left(index) < size){
            int largest = left(index);
            if (right(index) < size && heap[right(index)] > heap[left(index)]) {
                largest = right(index);
            }
            if (heap[index] >= heap[largest]) break;
            swap(heap[index], heap[largest]);
            index = largest;
        }
    }

    // Helper functions for indexing
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }
    int parent(int i) { return (i - 1) / 2; }
    
    public:
    void insert(int value){
        heap.push_back(value);
        Heapifyup(heap.size()-1);
    }

    int Extractmax(){
        if (heap.empty()) return -1;
        int maxVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        Heapifydown(0);
        return maxVal;
    }

    void Printheap(){
        for (int i : heap){
            cout<< i << " ";
        }
        cout << endl;
    }
};

int main(){
    MaxHeap H;
    H.insert(2);
    H.insert(32);
    H.insert(24);
    H.insert(9);
    H.insert(17);
    H.Printheap();
    cout<< H.Extractmax();
    cout<< endl;

}
