#include<iostream>
using namespace std;

class Node{
  public:
    int data;
    Node *parent;
    Node *left;
    Node *right;

    Node(int d){
        data = d;
        parent = NULL;
        left = NULL;
        right = NULL;
    }
};

void insertChild(Node *node, int data){
    if(data%2==0){
        Node *leftChild = new Node(data);
        node->left = leftChild;
        leftChild->parent = node;
    }
    else{
        Node *rightChild = new Node(data);
        node->right = rightChild;
        rightChild->parent = node;
    }
    return;
}

void preOrder(Node *root){
    if(root == NULL) return;
    cout<<root->data<<endl;
    preOrder(root->left);
    preOrder(root->right);
}

void postOrder(Node *root){
    if(root == NULL) return;
    postOrder(root->left);
    postOrder(root->right);
    cout<<root->data<<endl;
}

void inOrder(Node *root){
    if (root == NULL)
    {
        return;
    }
    inOrder(root->left);
    cout<<root->data<<endl;
    inOrder(root->right);
}

int main(){
    Node *root = new Node(1);
    insertChild(root,2);
    insertChild(root,3);
    Node *L1ch1 = root->left;
    Node *L1ch2 = root->right;
    insertChild(L1ch1,4);
    insertChild(L1ch1,5);
    insertChild(L1ch2,6);
    insertChild(L1ch2,7);
    
    Node *leaf1 = L1ch1->left;
    Node *leaf2 = L1ch1->right;
    Node *leaf3 = L1ch2->left;
    Node *leaf4 = L1ch2->right;
    
    preOrder(root);cout<<endl;
    postOrder(root);cout<<endl;
    inOrder(root);
}