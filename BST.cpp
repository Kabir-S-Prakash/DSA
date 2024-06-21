#include<iostream>
#include<map>
using namespace std;

class Node{
  public:
    Node *left;
    Node *right;
    Node *parent;
    int key;
    int data;

    Node(int k,int d){
        left = NULL;
        right = NULL;
        parent = NULL;
        key = k;
        data = d;
    }

    ~Node(){
    }
};

int search(Node *root,int key){
    if(key == root->key) return root->data;
    if(key > root->key) return search(root->right,key);
    if(key < root->key) return search(root->left,key);
    return -1;
}

void insertNode(Node *root,int key,int data){
    Node *y = NULL;
    Node *x = root;
    while(x != NULL){
        y = x;
        if(key < x->key){
            x = x->left;
        }
        else x = x->right;
    }
    Node *temp = new Node(key,data);
    if(y == NULL){
        root = temp;
        return;
    }
    else if(key < y->key){
        y->left = temp;
        temp->parent = y;
        return;
    }
    else{
        y->right = temp;
        temp->parent = y;
        return;
    }
}

map<string,int> minKey(Node *root){
    Node *y = NULL;
    Node *x = root;
    while(x != NULL){
        y = x;
        x = x->left;
    }
    map<string,int> ans;
    ans["key"] = y->key;
    ans["value"] = y->data;
    return ans;
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

map<string,int> maxKey(Node *root){
    Node *y = NULL;
    Node *x = root;
    while(x != NULL){
        y = x;
        x = x->right;
    }
    map<string,int> ans;
    ans["key"] = y->key;
    ans["value"] = y->data;
    return ans;
}

Node* maxNode(Node *root){
    Node *y = NULL;
    Node *x = root;
    while(x != NULL){
        y = x;
        x = x->right;
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

Node* predecessor(Node *x){
    if(x->left != NULL){
        return maxNode(x->left);
    }
    else{
        Node *y = x->parent;
        while(x != y->right){
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
        Node *z = x->left;
        Node *y = x->parent;
        if(y->left == x) y->left = z;
        else y->right = z;
        delete x;
        return;
    }
    else if(x->left == NULL && x->right != NULL){
        Node *z = x->right;
        Node *y = x->parent;
        if(y->left == x) y->left = z;
        else y->right = z;
        delete x;
        return;
    }
    else{
        Node *y = successor(x);
        x->key = y->key;
        x->data = y->data;
        deleteNode(y);
    }
}

void getLevel(Node *root,int &level,map<int,vector<int> > &Node_level){
    if(root == NULL) return;
    if(level != 0){
        Node_level[level].push_back(root->key);
    }
    int Level = level+1;
    getLevel(root->left,Level,Node_level);
    getLevel(root->right,Level,Node_level);
}

void inOrder(Node *root){
    if (root == NULL)
    {
        return;
    }
    inOrder(root->left);
    cout<<root->key<<endl;
    inOrder(root->right);
}

int main(){
    // Node *root = new Node(0,10);
    // insert(root,5,10);
    // insert(root,3,10);
    // insert(root,2,10);
    // insert(root,8,10);
    // insert(root,7,20);
    // insert(root,6,20);
    // insert(root,9,10);

    Node *root = new Node(5,10);
    insertNode(root,3,10);
    insertNode(root,10,10);
    insertNode(root,2,10);
    insertNode(root,7,10);
    insertNode(root,11,10);
    insertNode(root,4,10);

    // //BST before deletion
    // int level = 0;
    // map<int,vector<int> > Node_level;
    // vector<int> Root;
    // Root.push_back(root->key);
    // Node_level[level] = Root;
    // getLevel(root,level,Node_level);
    // for(map<int,vector<int> >::iterator i=Node_level.begin(); i!=Node_level.end(); ++i){
    //     cout<<i->first<<" : ";
    //     for(int j=0; j<i->second.size(); j++){
    //         cout<<i->second[j]<<" ";
    //     }
    //     cout<<endl;
    // }

    inOrder(root);
    map<string,int> minValue = minKey(root);
    map<string,int> maxValue = maxKey(root);
    cout<<minValue["key"]<<endl;
    cout<<maxValue["key"]<<endl;

    cout<<successor(root)->key<<endl;
    cout<<predecessor(root)->key<<endl;

    //BST after deletion
    deleteNode(root);
    int level = 0;
    map<int,vector<int> > Node_level;
    vector<int> Root;
    Root.push_back(root->key);
    Node_level[level] = Root;
    getLevel(root,level,Node_level);
    for(map<int,vector<int> >::iterator i=Node_level.begin(); i!=Node_level.end(); ++i){
        cout<<i->first<<" : ";
        for(int j=0; j<i->second.size(); j++){
            cout<<i->second[j]<<" ";
        }
        cout<<endl;
    }

    inOrder(root);
}