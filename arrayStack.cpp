#include<iostream>
using namespace std;

class ArrayStack{
  public:

    int n;
    int p;
    int *arr;
    int size;
    ArrayStack(){
        n = 1024;
        p = -1;
        arr = new int[n];
    }

    ArrayStack(int a){
        n = a;
        p = -1;
        arr = new int[n];
    }

    void push(int e){
        p++;
        arr[p] = e;
        size = p+1;
    }

    void pop(){
        if(p==-1){
            cout<<"Stack is empty";
        }
        else{
            arr[p] = -1;
            p--;
            size = p+1;
        }
        return;
    }

    int top(){
        if (p == -1)
        {
            cout<<"Stack is empty";
            return -1;
        }
        else{
            return arr[p];
        }
    }

};
int main(){
    ArrayStack stack1;
    stack1.push(3);
    stack1.push(5);
    for (int i = 0; i < stack1.size; i++)
    {
        cout<<stack1.arr[i]<<endl;
    }
    cout<<stack1.top();
}