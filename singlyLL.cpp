#include<iostream>
using namespace std;

class Node{
  public:
    int data;
    Node * next;

    Node(){
        next = NULL;
    }

    Node(int x){
        this->data = x;
        this->next = NULL;
    }

    ~Node(){
    }

};

void insertAtHead(Node * &head, int d){
        Node *temp = new Node(d);
        temp->next = head;
        head = temp;
}

void print(Node * &head){
    Node *temp = head;
    while (temp != NULL)
    {
        cout<<temp->data<<" ";
        temp = temp->next;
    }
}

void insertAtTail(Node * &tail, int d){
    Node *temp = new Node(d);
    tail->next = temp;
    tail = tail->next;
}

void insertAtPosition(Node * &head, int p, int d){
    int counter = 0;
    Node *temp1 = head;
    Node *temp2 = temp1;
    while(counter < p){
        temp2 = temp1;
        temp1 = temp1->next;
        counter++;
    }

    Node *temp = new Node(d);
    temp2->next = temp;
    temp->next = temp1;
}

void deleteNode(Node * &head, int p){
    int counter = 0;
    Node *temp1 = head;
    Node *temp2 = temp1;
    while(counter < p){
        temp2 = temp1;
        temp1 = temp1->next;
        counter++;
    }
    temp2->next = temp1->next;
    delete temp1;
}

int main(){
    Node *node1 = new Node(10);
    Node *head = node1;
    Node *tail = node1;

    insertAtHead(head,20);
    insertAtHead(head,30);
    insertAtHead(head,40);
    print(head);
    
    cout<<endl;
    
    insertAtTail(tail,50);
    insertAtTail(tail,60);
    insertAtTail(tail,70);
    print(head);
    cout<<endl;

    insertAtPosition(head,1,80);
    insertAtPosition(head,3,90);
    print(head);
    cout<<endl;

    deleteNode(head,2);
    deleteNode(head,5);
    print(head);

}