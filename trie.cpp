#include<iostream>
#include<vector>
using namespace std;

class Node{
  public:
    char data;
    bool isTerminal;
    vector<Node*> children;
    Node *parent;

    Node(char ch){
        data = ch;
        isTerminal = false;
        parent = NULL;
    }

    Node(){
        isTerminal = false;
        parent = NULL;
    }

    ~Node(){
    }
};

int findInVector(vector<Node*> children,char c){
    for(int i=0; i<children.size(); i++){
        if(children[i]->data == c){
            return i;
            break;
        }
    }
    return -1;
}

bool isPresent(string s,Node *root){
    int i=0;
    Node *temp = root;
    while(i<s.size() && temp->isTerminal == false){
        int index = findInVector(temp->children,s[i]);
        if(index != -1){
            i++;
            temp = temp->children[index];
        }
        else return false;
    }
    if(i == s.size() && temp->isTerminal == false){
        if(findInVector(temp->children,'$') != -1) return true;
        else return false;
    }
    else if(temp->isTerminal == true && i<s.size()) return false;
    return true;
}

void insertWord(string s,Node *root){
    int i=0;
    Node *temp = root;
    while(i<s.size()){
        int index = findInVector(temp->children,s[i]);
        if(index != -1 && temp->isTerminal == false){
            i++;
            temp = temp->children[index];
        }
        else if(index != -1 && temp->isTerminal == true) i++;
        else break;
    }
    while(i<s.size()-1){
        Node *newNode = new Node(s[i]);
        newNode->parent = temp;
        temp->children.push_back(newNode);
        temp = newNode;
        i++;
    }
    if(i == s.size()-1){
        Node *newNode = new Node(s[i]);
        newNode->isTerminal = true;
        newNode->parent = temp;
        temp->children.push_back(newNode);
        temp = newNode;
        i++;
    }
    if(i == s.size() && temp->isTerminal == false){
        Node *newNode = new Node('$');
        newNode->isTerminal = true;
        newNode->parent = temp;
        temp->children.push_back(newNode);
        temp = newNode;
    }
    if(i == s.size() && temp->isTerminal == true) return;
}

void deleteWord(string s,Node *root){
    if(!isPresent(s,root)) return;
    Node *temp = root;
    int i=0;
    while(i<s.size()){
        int index = findInVector(temp->children,s[i]);
        if(index != -1){
            i++;
            temp = temp->children[index];
        }
    }
    if(temp->isTerminal == false){
        int index = findInVector(temp->children,'$');
        vector<Node*>::iterator i = temp->children.begin();
        Node *temp2 = temp->children[index];
        temp->children.erase(i+index);
        delete temp2;
        return;
    }
    else{
        Node *temp3 = temp->parent;
        while(temp3 != NULL && temp3->children.size() <=1){
            vector<Node*>::iterator j = temp3->children.begin();
            temp3->children.erase(j);
            delete temp;
            temp = temp3;
            temp3 = temp3->parent;
        }
        if(temp3 == NULL){
            return;
        }
        else{
            char c = temp->data;
            int index = findInVector(temp3->children,c);
            vector<Node*>::iterator j = temp3->children.begin();
            temp3->children.erase(j+index);
            delete temp;
            return;
        }
    }
}

int main(){
    Node *root = new Node();
    insertWord("ARM",root);
    insertWord("DO",root);
    insertWord("TIME",root);
    insertWord("TIM",root);
    insertWord("ARC",root);

    cout<<isPresent("ARC",root)<<endl;

    deleteWord("TIM",root);

    cout<<isPresent("TIME",root)<<endl;
}