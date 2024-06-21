#include<iostream>
using namespace std;

class ArrayQueue{

  public:
    int *arr;
    int f,r;
    int n;
    ArrayQueue(){
        n = 1024;
        arr = new int[n];
        f = -1;
        r = -1;
    }

    int size(){
        if (r>f)
        {
            return r-f;
        }
        else{
            return n+r-f;
        }
    }

    bool isEmpty(){
        if (r == f)
        {
            return true;
        }
        else{
            return false;
        }   
    }

    void dequeue(){
        if (!this->isEmpty())
        {
            arr[f] = -1;
            f++;
        }
        // isEmpty exception remaining
    }

    void enqueue(int e){
        if (this->size() != n-1 && this->isEmpty())
        {
            r++;
            arr[r] = e;
            r++;
            f++;
        }
        else if (this->size() != n-1 && !this->isEmpty())
        {
            arr[r] = e;
            r++;
        }
        // isFull exception remaining
    }

    int front(){
        if (!this->isEmpty())
        {
            return arr[f];
        }
        // empty exception remaining
    }
};

int main(){
    ArrayQueue queue1;
    queue1.enqueue(1);
    queue1.enqueue(2);
    queue1.enqueue(3);
    for (int i = queue1.f; i < queue1.r; i++)
    {
        cout<<queue1.arr[i]<<endl;
    }
    cout<<endl;
    queue1.dequeue();
    for (int i = queue1.f; i < queue1.r; i++)
    {
        cout<<queue1.arr[i]<<endl;
    }
}