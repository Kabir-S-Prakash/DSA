#include<iostream>
#include<vector>
#include<map>
using namespace std;

class Node{
  public:
    int key;
    Node *parent;
    Node *left;
    Node *right;
    string color;

    Node(){
    }

    Node(int k){
        key = k;
        parent = left = right = NULL;
    }

    Node(int k,string c){
        key = k;
        color = c;
        parent = left = right = NULL;
    }

    ~Node(){
    }
};

void getLevel(Node *root,int &level,map<int,vector<int> > &Node_level){
    if(root == NULL) return;
    Node_level[level].push_back(root->key);
    int Level = level+1;
    getLevel(root->left,Level,Node_level);
    getLevel(root->right,Level,Node_level);
}

Node* searchKey(Node *root,int key){
    Node* temp = root;
    while(temp->key != key){
        if(key < temp->key) temp = temp->left;
        else temp = temp->right;
    }
    return temp;
}

Node* minNode(Node *root){
    Node *y = NULL;
    Node *x = root;
    while(x != NULL){
        y = x;
        x = x->left;
    }
    return y;
}

Node* successor(Node *x){
    if(x->right != NULL){
        return minNode(x->right);
    }
    else{
        Node *y = x->parent;
        while(x != y->left){
            x = y;
            y = y->parent;
        }
        return y;
    }
}

void deleteNode(Node *x){
    if(x->left == NULL && x->right == NULL){
        Node *y = x->parent;
        if(x == y->left){
            y->left = NULL;
        }
        else y->right = NULL;
        delete x;
        return;
    }
    else if(x->left != NULL && x->right == NULL){
        if(x->color == "black"){
            Node *z = x->left;
            Node *y = x->parent;
            if(y->left == x) y->left = z;
            else y->right = z;
            z->color = "black";
            delete x;
            return;
        }
        else{
            Node *z = x->left;
            Node *y = x->parent;
            if(y->left == x) y->left = z;
            else y->right = z;
            delete x;
            return;
        }
    }
    else if(x->left == NULL && x->right != NULL){
        if(x->color == "black"){
            Node *z = x->right;
            Node *y = x->parent;
            if(y->left == x) y->left = z;
            else y->right = z;
            z->color = "black";
            delete x;
            return;
        }
        else{
            Node *z = x->right;
            Node *y = x->parent;
            if(y->left == x) y->left = z;
            else y->right = z;
            delete x;
            return;
        }
    }
    else{
        Node *y = successor(x);
        x->key = y->key;
        deleteNode(y);
    }
}

// Rotation functions
void rotateClockwise(Node* low,Node* high){
    Node* highParent = high->parent;
    if(highParent == NULL){
        Node* T3 = low->right;
        if(T3 != NULL){
            low->parent = NULL;
            low->right = high;
            high->parent = low;
            high->left = T3;
            T3->parent = high;
            return;
        }
        else{
            low->parent = NULL;
            low->right = high;
            high->parent = low;
            high->left = NULL;
            return;
        }
    }
    else{
        bool decision;
        if(highParent->left == high) decision = true;
        else decision = false;
        Node* T3 = low->right;
        if(T3 != NULL){
            if(decision) highParent->left = low;
            else highParent->right = low;
            low->parent = highParent;
            low->right = high;
            high->parent = low;
            high->left = T3;
            T3->parent = high;
            return;
        }
        else{
            if(decision) highParent->left = low;
            else highParent->right = low;
            low->parent = highParent;
            low->right = high;
            high->parent = low;
            high->left = NULL;
            return;
        }
    }
}

void rotateAntiClockwise(Node* low,Node *high){
    Node* highParent = high->parent;
    if(highParent == NULL){
        Node* T2 = low->left;
        if(T2 != NULL){
            low->parent = NULL;
            low->left = high;
            high->parent = low;
            high->right = T2;
            T2->parent = high;
            return;
        }
        else{
            low->parent = NULL;
            low->left = high;
            high->parent = low;
            high->right = NULL;
            return;
        }
    }
    else{
        bool decision;
        if(highParent->left == high) decision = true;
        else decision = false;
        Node* T2 = low->left;
        if(T2 != NULL){
            if(decision) highParent->left = low;
            else highParent->right = low;
            low->parent = highParent;
            low->left = high;
            high->parent = low;
            high->right = T2;
            T2->parent = high;
            return;
        }
        else{
            if(decision) highParent->left = low;
            else highParent->right = low;
            low->parent = highParent;
            low->left = high;
            high->parent = low;
            high->right = NULL;
            return;
        }
    }
}

void deleteKey(Node *root,int key){
    Node* x = searchKey(root,key);
    Node* a;
    bool decision1;
    if(x->left != NULL && x->right != NULL){
        Node *y = successor(x);
        if(y->color == "red"){
            deleteNode(x);
            return;
        }
        a = y->parent;
        if(a->left == y) decision1 = true;
        else decision1 = false;
        deleteNode(x);
    }
    else{
        if(x->color == "red"){
            deleteNode(x);
            return;
        }
        a = x->parent;
        deleteNode(x);
    }
    Node *b;
    if(decision1) b = a->right;
    else b = a->left;

    // Case 1.1 Some c is red
    Node *c;
    if(b->right->color == "red" && b->left->color != "red") c = b->right;
    else if(b->left->color == "red") c = b->left;
    if(a->color == "red" && b->color == "black" && c->color == "red"){
        if(a->left == b && b->left == c){
            rotateClockwise(b,a);
            b->color = "red";
            a->color = "black";
            c->color = "black";
        }
        else if(a->left == b && b->right == c){
            rotateAntiClockwise(c,b);
            rotateClockwise(c,a);
            c->color = "red";
            b->color = "black";
            a->color = "black";
        }
        else if(a->right == b && b->right == c){
            rotateAntiClockwise(b,a);
            b->color = "red";
            a->color = "black";
            c->color = "black";
        }
        else{
            rotateClockwise(c,b);
            rotateAntiClockwise(c,a);
            c->color = "red";
            b->color = "black";
            a->color = "black";
        }
    }
}

int blackHeight(Node *root){
    Node *temp = root;
    int height = 0;
    while(temp != NULL){
        if(temp->color == "black") height++;
        temp = temp->right;
    }
    return height;
}

int main(){

    // Example RBT
    Node *root = new Node(9,"black");
    Node *node1 = new Node(4,"red");
    root->left = node1;
    node1->parent = root;
    Node *node2 = new Node(13,"red");
    root->right = node2;
    node2->parent = root;
    Node *node3 = new Node(2,"black");
    node1->left = node3;
    node3->parent = node1;
    Node *node4 = new Node(7,"black");
    node1->right = node4;
    node4->parent = node1;
    Node *node5 = new Node(11,"black");
    node2->left = node5;
    node5->parent = node2;
    Node *node6 = new Node(19,"black");
    node2->right = node6;
    node6->parent = node2;
    Node* node7 = new Node(1,"red");
    node3->left = node7;
    node7->parent = node3;
    Node *node8 = new Node(3,"red");
    node3->right = node8;
    node8->parent = node3;
    Node *node9 = new Node(5,"red");
    node4->left = node9;
    node9->parent = node4;
    Node* node10 = new Node(17,"red");
    node6->left = node10;
    node10->parent = node6;

    // Initial Levels
    int level = 0;
    map<int,vector<int> > Node_level;
    getLevel(root,level,Node_level);
    for(map<int,vector<int> >::iterator i=Node_level.begin(); i!=Node_level.end(); ++i){
        cout<<i->first<<" : ";
        for(int j=0; j<i->second.size(); j++){
            cout<<i->second[j]<<" ";
        }
        cout<<endl;
    }

    // Initial black height
    cout<<blackHeight(root)<<endl;
}