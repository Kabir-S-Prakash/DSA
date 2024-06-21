#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<pair<char,int> >::iterator findIndexOfChar(vector<pair<char,int> > &freq,char c){
    vector<pair<char,int> >::iterator i;
    for(i=freq.begin(); i!=freq.end(); ++i){
        if(i->first == c) return i;
    }
    return freq.end();
}

// Comparision function
bool sortByValue(const pair<char,int> &a,const pair<char,int> &b){
    return a.second < b.second;
}

vector<pair<char,int> > frequency(string s){
    vector<pair<char,int> > freq;
    for(int i=0; i<s.size(); i++){
        vector<pair<char,int> >::iterator it = findIndexOfChar(freq,s[i]);
        if(it == freq.end()){
            pair<char,int> pair1 = make_pair(s[i],1);
            freq.push_back(pair1);
        }
        else{
            it->second += 1;
        }
    }
    sort(freq.begin(),freq.end(),sortByValue);
    return freq;
}

class Node{
  public:
    int freqSum;
    Node *left;
    Node *right;
    bool isLeaf;
    char ch;

    Node(int f){
        freqSum = f;
        left = right = nullptr;
        isLeaf = false;
    }

    ~Node(){
    }
};

// Comparision function
bool sortByFrequency(Node* &a,Node* &b){
    return a->freqSum < b->freqSum;
}

Node* createTree(string s){
    vector<pair<char,int> > freq = frequency(s);
    vector<pair<char,int> >::iterator it;
    vector<Node*> Leaves;
    for(it=freq.begin(); it!=freq.end(); ++it){
        Node *temp = new Node(it->second);
        temp->ch = it->first;
        temp->isLeaf = true;
    }
    int m = Leaves.size();
    for(int i=0; i<m-1; i++){
        sort(Leaves.begin(),Leaves.end(),sortByFrequency);
        Node *temp = new Node(Leaves[0]->freqSum+Leaves[1]->freqSum);
        Node *LeftChild = Leaves[0];
        Node *RightChild = Leaves[1];
        temp->left = LeftChild;
        temp->right = RightChild;
        Leaves.erase(Leaves.begin());
        Leaves.erase(Leaves.begin());
        Leaves.push_back(temp);
    }
    return Leaves[0];
}

int main(){
    // vector<pair<char,int> > freq = frequency("ABRACADABRA");
    // for(vector<pair<char,int> >::iterator i=freq.begin(); i!=freq.end(); i++){
    //     cout<<i->first<<" : "<<i->second<<endl;
    // }

    Node *root = createTree("ABRACADABRA");
    Node *temp = root;
    while(!temp->isLeaf) temp = temp->right;
    cout<<temp->ch;
}