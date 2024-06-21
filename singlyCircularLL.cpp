#include<iostream>
using namespace std;

class Node{
  public:
    int data;
    Node *next;

    Node(int d){
        this->data = d;
        this->next = NULL;
    }

    ~Node(){
    }
};

int getLength(Node *node){
    int size = 0;
    if (node->next == NULL)
    {
        return 1;
    }
    else{
        Node *temp = node;
        bool first = true;
        while (first == true || temp != node)
        {
            first = false;
            size++;
            temp = temp->next;
        }
        return size;
    }
}

void print(Node *node){
    Node *temp = node;
    int c = 0;
    while ((temp != node || c==0) && getLength(node) != 1)
    {
        c++;
        cout<<temp->data<<" ";
        temp = temp->next;
    }
    if (getLength(node) == 1)
    {
        cout<<temp->data;
    }
    cout<<endl;
}

void insertNode(Node * &node, int d){
    Node *temp = new Node(d);
    if (getLength(node) == 1)
    {
        node->next = temp;
        temp->next = node;
    }
    else{
        Node *next = node->next;
        node->next = temp;
        temp->next = next;
    }
}

void deleteNode(Node * &node, int value){
    Node *temp1 = node;                 // previous node
    Node *temp2 = temp1;                // node to be deleted
    int iteration = 1;
    while (temp1->data != value)
    {
        if (iteration == 1)
        {
            temp1 = temp1->next;
        }
        else{
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        iteration++;
    }
    temp2->next = temp1->next;
    delete temp1;
}

int main(){
    Node *node1 = new Node(10);
    print(node1);
    cout<<getLength(node1)<<endl;
    insertNode(node1,20);
    insertNode(node1,30);
    insertNode(node1,40);
    print(node1);
    cout<<getLength(node1)<<endl;

    deleteNode(node1,20);
    print(node1);
    cout<<getLength(node1)<<endl;
}