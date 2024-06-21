#include<iostream>
#include<vector>
using namespace std;

class Heap{
  public:
    int *arr;
    int N; // Max size
    int size;

    Heap(){
        int N = 1024;
        arr = new int[N];
        for(int i=0; i<N; i++) arr[i] = INT16_MIN;
        size = 0;
    }

    Heap(int maxSize){
        N = maxSize;
        arr = new int[N];
        for(int i=0; i<N; i++) arr[i] = INT16_MIN;
        size = 0;
    }

    ~Heap(){
    }

    int height(){
        return floor(log(this->size)/log(2));
    }

    int parentIndex(int i){
        return floor(i/2);
    }

    int rightIndex(int i){
        return 2*i+1;
    }

    int leftIndex(int i){
        return 2*i;
    }

    void insert(int x){
        this->arr[size] = x;
        size++;
        if(size==1) return;
        int childIndex = size;
        int parentIndex = this->parentIndex(childIndex);
        while(arr[childIndex-1] < arr[parentIndex-1]){
            int temp = this->arr[childIndex-1];
            this->arr[childIndex-1] = this->arr[parentIndex-1];
            this->arr[parentIndex-1] = temp;
            childIndex = parentIndex;
            parentIndex = this->parentIndex(parentIndex);
        }
        return;
    }

    bool isHeap(int i){
        if(arr[leftIndex(i)-1] == INT16_MIN && arr[rightIndex(i)-1] == INT16_MIN) return true;
        else if(arr[leftIndex(i)-1] == INT16_MIN){
            if(arr[i-1] > arr[rightIndex(i)-1]) return false;
            else return true;
        }
        else if(arr[rightIndex(i)-1] == INT16_MIN){
            if(arr[i-1] > arr[leftIndex(i)-1]) return false;
            else return true;
        }
        else if(arr[i-1] > arr[leftIndex(i)-1] || arr[i-1] > arr[rightIndex(i)-1]) return false;
        else return true;
    }

    void heapify(int i){
        int j,temp;
        while(!isHeap(i)){
            if(arr[leftIndex(i)-1] == INT16_MIN) j = rightIndex(i);
            else if(arr[rightIndex(i)-1] == INT16_MIN) j = leftIndex(i);
            else if(arr[leftIndex(i)-1] < arr[rightIndex(i)-1]) j = leftIndex(i);
            else j = rightIndex(i);
            temp = arr[i-1];
            arr[i-1] = arr[j-1];
            arr[j-1] = temp;
            i = j;
        }
        return;
    }

    void print(){
        for(int i=0; i<size; i++){
            cout<<this->arr[i]<<" ";
        } cout<<endl;
    }

    int deleteMin(){
        int temp = arr[0];
        arr[0] = arr[size-1];
        arr[size-1] = INT16_MIN;
        size--;
        heapify(1);
        return temp;
    }
};

Heap* buildHeap(int A[],int n){
    Heap* heap = new Heap();
    for (int i = 0; i < n; i++)
    {
        heap->arr[i] = A[i];
        heap->size++;
    }
    for(int i= floor(heap->size/2); i>0; i--){    //O(n)
        heap->heapify(i);
    }
    // for(int i=0; i<n; i++){
    //     heap->insert(A[i]);                  //O(nlogn)
    // }
    return heap;
}

void heapSort(int A[],int n){
    Heap *heap = buildHeap(A,n);
    int B[n];
    for(int i=0; i<n; i++){
        B[i] = heap->deleteMin();
    }
    for(int i=0; i<n; i++){
        A[i] = B[i];
    }
    return;
}

int main(){
    // //Creating a heap
    // Heap* heap = new Heap();
    // heap->insert(11);
    // heap->insert(17);
    // heap->insert(13);
    // heap->insert(18);
    // heap->insert(21);
    // heap->insert(19);
    // heap->insert(17);
    // heap->insert(43);
    // heap->insert(23);
    // heap->insert(26);
    // heap->insert(29);
    // heap->insert(31);

    int arr[12] = {11,17,13,18,21,19,17,43,23,26,29,31};
    Heap* heap = buildHeap(arr,12);

    cout<<heap->size<<endl;
    cout<<heap->isHeap(floor(heap->size/2))<<endl;
    cout<<heap->arr[heap->parentIndex(2)-1]<<endl;
    cout<<heap->arr[heap->leftIndex(1)-1]<<endl;
    cout<<heap->arr[heap->rightIndex(0)-1]<<endl;
    heap->print();

    heap->deleteMin();
    heap->print();
    cout<<heap->size<<endl;

    int A[5] = {5,4,3,2,1};
    heapSort(A,5);
    for(int i=0; i<5; i++){
        cout<<A[i]<<" ";
    } cout<<endl;
}