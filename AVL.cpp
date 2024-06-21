#include<iostream>
#include<vector>
#include<map>
using namespace std;

class Node{
  public:
    Node *left;
    Node *right;
    Node *parent;
    int key;

    Node(int k){
        left = NULL;
        right = NULL;
        parent = NULL;
        key = k;
    }

    ~Node(){
    }
};

// Find height of tree
int height(Node* node){
    if(node == NULL) return 0;
    if(node->left == NULL && node->right == NULL) return 1;
    else if(node->left == NULL && node->right != NULL){
        return 1 + height(node->right);
    }
    else if(node->left != NULL && node->right == NULL){
        return 1 + height(node->left);
    }
    else{
        return 1 + max(height(node->left),height(node->right));
    }
}

// Check for balanced tree
bool isBalanced(Node *root){
    int heightLeft = height(root->left);
    int heightRight = height(root->right);
    if(abs(heightLeft-heightRight) <= 1) return true;
    else return false;
}

// Insert a node in BST
Node* insertBST(Node *root,int key){
    Node *y = NULL;
    Node *x = root;
    while(x != NULL){
        y = x;
        if(key < x->key){
            x = x->left;
        }
        else x = x->right;
    }
    Node *temp = new Node(key);
    if(y == NULL){
        root = temp;
        return root;
    }
    else if(key < y->key){
        y->left = temp;
        temp->parent = y;
        return temp;
    }
    else{
        y->right = temp;
        temp->parent = y;
        return temp;
    }
}

//Create BST
Node* createBST(vector<int> keys){
    Node *root = new Node(keys[0]);
    for(int i=1; i<keys.size(); i++){
        Node* temp = insertBST(root,keys[i]);
    }
    return root;
}

// Getting Levels
void getLevel(Node *root,int &level,map<int,vector<int> > &Node_level){
    if(root == NULL) return;
    Node_level[level].push_back(root->key);
    int Level = level+1;
    getLevel(root->left,Level,Node_level);
    getLevel(root->right,Level,Node_level);
}

// Minimum key node in BST
Node* minNode(Node *root){
    Node *y = NULL;
    Node *x = root;
    while(x != NULL){
        y = x;
        x = x->left;
    }
    return y;
}

// Successor in BST
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

// Delete node in a BST which returns it's parent
Node* deleteBST(Node *x){
    if(x->left == NULL && x->right == NULL){
        Node *y = x->parent;
        if(x == y->left){
            y->left = NULL;
        }
        else y->right = NULL;
        delete x;
        return y;
    }
    else if(x->left != NULL && x->right == NULL){
        Node *z = x->left;
        Node *y = x->parent;
        if(y->left == x) y->left = z;
        else y->right = z;
        delete x;
        return y;
    }
    else if(x->left == NULL && x->right != NULL){
        Node *z = x->right;
        Node *y = x->parent;
        if(y->left == x) y->left = z;
        else y->right = z;
        delete x;
        return y;
    }
    else{
        Node *y = successor(x);
        x->key = y->key;
        Node *z = y->parent;
        deleteBST(y);
        return z;
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

// Insert a node in AVL
void insertAVL(Node* &root,int key){
    Node* temp1 = insertBST(root,key);
    Node* x = temp1->parent;
    Node* y = x->parent;
    Node* z = y->parent;
    while(isBalanced(z) && z!=NULL){
        x = y;
        y = z;
        z = z->parent;
    }
    if(z == NULL) return;
    if(z->left == y && y->left == x){
        rotateClockwise(y,z);
        return;
    }
    else if(z->right == y && y->right == x){
        rotateAntiClockwise(y,z);
        return;
    }
    else if(z->right == y && y->left == x){
        rotateClockwise(x,y);
        rotateAntiClockwise(x,z);
        return;
    }
    else if(z->left == y && y->right == x){
        rotateAntiClockwise(x,y);
        rotateClockwise(x,z);
        return;
    }
}

// Delete in an AVL
void deleteAVL(Node *v){
    Node* z = deleteBST(v);
    Node* y;
    Node* x;

    // Finding first imbalance z
    while(isBalanced(z) && z!= NULL) z = z->parent;
    while(isBalanced(z) == false && z != NULL){
        // Taking y as child with greater height
        if(height(z->left)>height(z->right)) y = z->left;
        else y = z->right;

        // Taking x as child with greater height
        if(height(y->left)>height(y->right)) x = y->left;
        else x = y->right;

        if(z->left == y && y->left == x){
            rotateClockwise(y,z);
            z = y->parent;
        }
        else if(z->right == y && y->right == x){
            rotateAntiClockwise(y,z);
            z = y->parent;
        }
        else if(z->left == y && y->right == x){
            rotateAntiClockwise(x,y);
            rotateClockwise(x,z);
            z = x->parent;
        }
        else if(z->right == y && y->left == x){
            rotateClockwise(x,y);
            rotateAntiClockwise(x,z);
            z = x->parent;
        }
    }
    if(z == NULL) return;
}

int main(){

    vector<int> nums;
    nums.push_back(44);
    nums.push_back(17);
    nums.push_back(78);
    nums.push_back(32);
    nums.push_back(50);
    nums.push_back(88);
    nums.push_back(48);
    nums.push_back(62);

    // Creating initial BST
    Node* root = createBST(nums);
    // Checking Levels
    int RootLevel = 0;
    map<int,vector<int> > Node_level;
    getLevel(root,RootLevel,Node_level);
    for(map<int,vector<int> >::iterator i=Node_level.begin(); i!=Node_level.end(); i++){
        cout<<i->first<<" : ";
        vector<int> temp = i->second;
        for(int j=0; j<temp.size(); j++){
            cout<<temp[j]<<" ";
        } cout<<endl;
    }

    // Checking balanced
    cout<<isBalanced(root)<<endl;

    // Node* temp = insertBST(root,54);
    // // Checking balanced
    // cout<<isBalanced(root)<<endl;

    insertAVL(root,54);

    // Checking Levels
    int RootLevel2 = 0;
    map<int,vector<int> > Node_level2;
    getLevel(root,RootLevel2,Node_level2);
    for(map<int,vector<int> >::iterator i=Node_level2.begin(); i!=Node_level2.end(); i++){
        cout<<i->first<<" : ";
        vector<int> temp = i->second;
        for(int j=0; j<temp.size(); j++){
            cout<<temp[j]<<" ";
        } cout<<endl;
    }
    // Checking balanced
    cout<<isBalanced(root)<<endl;

    deleteAVL(root->left->right);

    // Checking Levels
    int RootLevel3 = 0;
    map<int,vector<int> > Node_level3;
    getLevel(root,RootLevel3,Node_level3);
    for(map<int,vector<int> >::iterator i=Node_level3.begin(); i!=Node_level3.end(); i++){
        cout<<i->first<<" : ";
        vector<int> temp = i->second;
        for(int j=0; j<temp.size(); j++){
            cout<<temp[j]<<" ";
        } cout<<endl;
    }
    // Checking balanced
    cout<<isBalanced(root)<<endl;
}