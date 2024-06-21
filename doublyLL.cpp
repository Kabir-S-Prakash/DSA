#include<iostream>
using namespace std;

class Node{
  public:
    int data;
    Node *next;
    Node *prev;

    Node(int d){
        this->data = d;
        this->next = NULL;
        this->prev = NULL;
    }

    ~Node(){
    }
};

void print(Node *head){
    Node *temp = head;
    while (temp != NULL)
    {
        cout<<temp->data<<" ";
        temp = temp->next;
    }
    cout<<endl;
}

int getLength(Node *head){
    Node *temp = head;
    int c = 0;
    while (temp != NULL)
    {
        c++;
        temp = temp->next;
    }
    return c;
}

void insertAtHead(Node * &head,int d){
    Node *temp = new Node(d);
    temp->next = head;
    head->prev = temp;
    head = temp;
}

void insertAtTail(Node * &tail, int d){
    Node *temp = new Node(d);
    tail->next = temp;
    temp->prev = tail;
    tail = temp;
}

void insertAtPosition(Node * &head, int pos, int d){
    Node *temp = new Node(d);
    Node *temp1 = head;
    int counter = 0;
    while (counter<pos)
    {
        temp1 = temp1->next;
        counter++;
    }
    Node *previous = temp1->prev;
    Node *next = temp1;
    previous->next = temp;
    temp->prev = previous;
    temp->next = next;
    next->prev = temp;
}

void deleteNode(Node * &head, int pos){
    Node *temp1 = head;
    int counter = 0;
    while (counter<pos)
    {
        temp1 = temp1->next;
        counter++;
    }
    Node *previous = temp1->prev;
    Node *next = temp1->next;
    previous->next = next;
    next->prev = previous;
    delete temp1;
}

int main(){
    Node *node1 = new Node(10);
    Node *head = node1;
    Node *tail = node1;
    print(head);
    cout<<getLength(head)<<endl;

    insertAtHead(head,20);
    insertAtHead(head,30);
    print(head);
    cout<<getLength(head)<<endl;

    insertAtTail(tail,40);
    insertAtTail(tail,50);
    print(head);
    cout<<getLength(head)<<endl;

    insertAtPosition(head,1,60);
    insertAtPosition(head,4,70);
    print(head);
    cout<<getLength(head)<<endl;

    deleteNode(head,3);
    print(head);
    cout<<getLength(head)<<endl;
}