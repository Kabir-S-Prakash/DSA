#include<iostream>
#include<vector>
using namespace std;

class Node{
  public:
    vector<char> Node_text;
    Node *parent;
    bool leaf;

    Node(string s){
        for (int i = 0; i < s.size(); i++)
        {
            Node_text.push_back(s[i]);
        }
        leaf = false;
        parent = NULL;
    }
    Node(){
        leaf = false;
        parent = NULL;
    }
};

Node* createSuffixTree(string s){
    Node *root = new Node();
    int c = 0;
    for (int i = s.size(); i >=0; i--)
    {
        string sub = s.substr(c,i);
    }
    
}

int manin(){

}