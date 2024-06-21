#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Node {
public:
    Node *parent;
    Node *left;
    Node *mid1;
    Node *mid2;
    Node *right;
    vector<int> keys;

    Node(int k1, int k2, int k3) {
        parent = NULL;
        left = NULL;
        mid1 = NULL;
        mid2 = NULL;
        right = NULL;
        keys.push_back(k1);
        keys.push_back(k2);
        keys.push_back(k3);
        sort(keys.begin(), keys.end());
    }

    Node(int k1, int k2) {
        parent = NULL;
        left = NULL;
        mid1 = NULL;
        mid2 = NULL;
        right = NULL;
        keys.push_back(k1);
        keys.push_back(k2);
        sort(keys.begin(), keys.end());
    }

    Node(int k1) {
        parent = NULL;
        left = NULL;
        mid1 = NULL;
        mid2 = NULL;
        right = NULL;
        keys.push_back(k1);
    }

    ~Node() {}

    int size() {
        return keys.size();
    }

    void insertKey(int key) {
        keys.push_back(key);
        sort(keys.begin(), keys.end());
    }

    void removeKey(int key) {
        keys.erase(remove(keys.begin(), keys.end(), key), keys.end());
    }
};

class TwoThreeFourTree {
private:
    Node* root;

    Node* findLeaf(Node* node, int key) {
        while (node->left != NULL) {
            if (key < node->keys[0]) {
                node = node->left;
            } else if (node->size() == 1 || (node->size() == 2 && key < node->keys[1])) {
                node = node->mid1;
            } else if (node->size() == 3 && key < node->keys[2]) {
                node = node->mid2;
            } else {
                node = node->right;
            }
        }
        return node;
    }

    void split(Node* node) {
        if (node->size() < 3) return;

        Node* parent = node->parent;
        Node* newLeft = new Node(node->keys[0]);
        Node* newRight = new Node(node->keys[2]);
        
        if (node->left) {
            newLeft->left = node->left;
            newLeft->mid1 = node->mid1;
            newRight->left = node->mid2;
            newRight->mid1 = node->right;

            if (newLeft->left) newLeft->left->parent = newLeft;
            if (newLeft->mid1) newLeft->mid1->parent = newLeft;
            if (newRight->left) newRight->left->parent = newRight;
            if (newRight->mid1) newRight->mid1->parent = newRight;
        }

        if (parent == NULL) {
            root = new Node(node->keys[1]);
            root->left = newLeft;
            root->mid1 = newRight;
            newLeft->parent = root;
            newRight->parent = root;
        } else {
            parent->insertKey(node->keys[1]);
            if (parent->left == node) {
                parent->left = newLeft;
                parent->mid2 = parent->mid1;
                parent->mid1 = newRight;
            } else if (parent->mid1 == node) {
                parent->mid2 = newRight;
            } else {
                parent->right = newRight;
            }
            newLeft->parent = parent;
            newRight->parent = parent;
            split(parent);
        }

        delete node;
    }

    void merge(Node* node) {
        Node* parent = node->parent;

        if (parent == NULL) {
            if (node->size() == 0 && node->left != NULL) {
                root = node->left;
                root->parent = NULL;
                delete node;
            }
            return;
        }

        Node* leftSibling = NULL;
        Node* rightSibling = NULL;
        if (parent->left == node) {
            rightSibling = parent->mid1;
        } else if (parent->mid1 == node) {
            leftSibling = parent->left;
            rightSibling = parent->mid2;
        } else if (parent->mid2 == node) {
            leftSibling = parent->mid1;
            rightSibling = parent->right;
        } else if (parent->right == node) {
            leftSibling = parent->mid2;
        }

        if (leftSibling && leftSibling->size() > 1) {
            node->keys.insert(node->keys.begin(), parent->keys.back());
            parent->keys.back() = leftSibling->keys.back();
            leftSibling->keys.pop_back();

            if (leftSibling->right) {
                node->left = node->mid1;
                node->mid1 = leftSibling->right;
                node->mid1->parent = node;
                leftSibling->right = leftSibling->mid2;
                leftSibling->mid2 = NULL;
            }
        } else if (rightSibling && rightSibling->size() > 1) {
            node->keys.push_back(parent->keys.front());
            parent->keys.front() = rightSibling->keys.front();
            rightSibling->keys.erase(rightSibling->keys.begin());

            if (rightSibling->left) {
                node->mid1 = node->left;
                node->left = rightSibling->left;
                node->left->parent = node;
                rightSibling->left = rightSibling->mid1;
                rightSibling->mid1 = rightSibling->mid2;
                rightSibling->mid2 = rightSibling->right;
                rightSibling->right = NULL;
            }
        } else {
            if (leftSibling) {
                leftSibling->keys.push_back(parent->keys.back());
                leftSibling->keys.insert(leftSibling->keys.end(), node->keys.begin(), node->keys.end());
                leftSibling->right = node->left;
                if (leftSibling->right) leftSibling->right->parent = leftSibling;
                leftSibling->mid2 = node->mid1;
                if (leftSibling->mid2) leftSibling->mid2->parent = leftSibling;

                parent->keys.pop_back();
                parent->mid1 = parent->mid2;
                parent->mid2 = parent->right;
                parent->right = NULL;
            } else if (rightSibling) {
                node->keys.push_back(parent->keys.front());
                node->keys.insert(node->keys.end(), rightSibling->keys.begin(), rightSibling->keys.end());
                node->right = rightSibling->right;
                if (node->right) node->right->parent = node;
                node->mid2 = rightSibling->mid1;
                if (node->mid2) node->mid2->parent = node;

                parent->keys.erase(parent->keys.begin());
                parent->mid1 = parent->mid2;
                parent->mid2 = parent->right;
                parent->right = NULL;
            }

            delete node;
            if (parent->size() == 0) {
                merge(parent);
            }
        }
    }

    void fixTree(Node* node) {
        if (node->size() >= 1) return;

        Node* parent = node->parent;
        if (parent == NULL) {
            if (node->left != NULL) {
                root = node->left;
                root->parent = NULL;
                delete node;
            }
            return;
        }

        if (parent->left == node) {
            if (parent->mid1->size() > 1) {
                node->keys.push_back(parent->keys[0]);
                parent->keys[0] = parent->mid1->keys.front();
                parent->mid1->keys.erase(parent->mid1->keys.begin());

                node->mid1 = node->left;
                node->left = parent->mid1->left;
                if (node->left) node->left->parent = node;
                parent->mid1->left = parent->mid1->mid1;
                parent->mid1->mid1 = parent->mid1->mid2;
                parent->mid1->mid2 = NULL;
            } else {
                node->keys.push_back(parent->keys[0]);
                node->keys.push_back(parent->mid1->keys.front());
                node->mid1 = node->left;
                node->left = parent->mid1->left;
                node->mid2 = parent->mid1->mid1;
                if (node->left) node->left->parent = node;
                if (node->mid2) node->mid2->parent = node;

                delete parent->mid1;
                parent->mid1 = parent->mid2;
                parent->mid2 = parent->right;
                parent->right = NULL;

                parent->keys.erase(parent->keys.begin());
                if (parent->size() == 0) {
                    fixTree(parent);
                }
            }
        } else if (parent->mid1 == node) {
            if (parent->left->size() > 1) {
                node->keys.insert(node->keys.begin(), parent->keys[0]);
                parent->keys[0] = parent->left->keys.back();
                parent->left->keys.pop_back();

                node->mid1 = node->left;
                node->left = parent->left->right;
                if (node->left) node->left->parent = node;
                parent->left->right = parent->left->mid2;
                parent->left->mid2 = NULL;
            } else if (parent->mid2 && parent->mid2->size() > 1) {
                node->keys.push_back(parent->keys[1]);
                parent->keys[1] = parent->mid2->keys.front();
                parent->mid2->keys.erase(parent->mid2->keys.begin());

                node->mid1 = node->left;
                node->left = parent->mid2->left;
                if (node->left) node->left->parent = node;
                parent->mid2->left = parent->mid2->mid1;
                parent->mid2->mid1 = parent->mid2->mid2;
                parent->mid2->mid2 = NULL;
            } else {
                node->keys.insert(node->keys.begin(), parent->keys[0]);
                if (parent->mid2) {
                    node->keys.push_back(parent->mid2->keys.front());
                    node->mid1 = node->left;
                    node->left = parent->left->right;
                    if (node->left) node->left->parent = node;
                    node->mid2 = parent->mid2->left;
                    if (node->mid2) node->mid2->parent = node;

                    delete parent->mid2;
                    parent->mid2 = parent->right;
                    parent->right = NULL;

                    parent->keys.erase(parent->keys.begin() + 1);
                } else {
                    node->keys.push_back(parent->left->keys.back());
                    parent->left->keys.pop_back();

                    node->mid1 = node->left;
                    node->left = parent->left->right;
                    if (node->left) node->left->parent = node;
                    parent->left->right = parent->left->mid2;
                    parent->left->mid2 = NULL;
                }

                delete parent->mid1;
                parent->mid1 = parent->mid2;
                parent->mid2 = parent->right;
                parent->right = NULL;

                parent->keys.erase(parent->keys.begin());
                if (parent->size() == 0) {
                    fixTree(parent);
                }
            }
        } else if (parent->mid2 == node) {
            if (parent->mid1->size() > 1) {
                node->keys.insert(node->keys.begin(), parent->keys[1]);
                parent->keys[1] = parent->mid1->keys.back();
                parent->mid1->keys.pop_back();

                node->mid1 = node->left;
                node->left = parent->mid1->right;
                if (node->left) node->left->parent = node;
                parent->mid1->right = parent->mid1->mid2;
                parent->mid1->mid2 = NULL;
            } else if (parent->right && parent->right->size() > 1) {
                node->keys.push_back(parent->keys[2]);
                parent->keys[2] = parent->right->keys.front();
                parent->right->keys.erase(parent->right->keys.begin());

                node->mid1 = node->left;
                node->left = parent->right->left;
                if (node->left) node->left->parent = node;
                parent->right->left = parent->right->mid1;
                parent->right->mid1 = parent->right->mid2;
                parent->right->mid2 = NULL;
            } else {
                node->keys.insert(node->keys.begin(), parent->keys[1]);
                if (parent->right) {
                    node->keys.push_back(parent->right->keys.front());
                    node->mid1 = node->left;
                    node->left = parent->mid1->right;
                    if (node->left) node->left->parent = node;
                    node->mid2 = parent->right->left;
                    if (node->mid2) node->mid2->parent = node;

                    delete parent->right;
                    parent->right = NULL;

                    parent->keys.erase(parent->keys.begin() + 1);
                } else {
                    node->keys.push_back(parent->mid1->keys.back());
                    parent->mid1->keys.pop_back();

                    node->mid1 = node->left;
                    node->left = parent->mid1->right;
                    if (node->left) node->left->parent = node;
                    parent->mid1->right = parent->mid1->mid2;
                    parent->mid1->mid2 = NULL;
                }

                delete parent->mid2;
                parent->mid2 = parent->right;
                parent->right = NULL;

                parent->keys.erase(parent->keys.begin());
                if (parent->size() == 0) {
                    fixTree(parent);
                }
            }
        } else if (parent->right == node) {
            if (parent->mid2->size() > 1) {
                node->keys.insert(node->keys.begin(), parent->keys[2]);
                parent->keys[2] = parent->mid2->keys.back();
                parent->mid2->keys.pop_back();

                node->mid1 = node->left;
                node->left = parent->mid2->right;
                if (node->left) node->left->parent = node;
                parent->mid2->right = parent->mid2->mid2;
                parent->mid2->mid2 = NULL;
            } else if (parent->mid1 && parent->mid1->size() > 1) {
                node->keys.push_back(parent->keys[2]);
                parent->keys[2] = parent->mid1->keys.back();
                parent->mid1->keys.pop_back();

                node->mid1 = node->left;
                node->left = parent->mid1->right;
                if (node->left) node->left->parent = node;
                parent->mid1->right = parent->mid1->mid2;
                parent->mid1->mid2 = NULL;
            } else {
                node->keys.insert(node->keys.begin(), parent->keys[2]);
                if (parent->mid1) {
                    node->keys.push_back(parent->mid1->keys.back());
                    parent->mid1->keys.pop_back();

                    node->mid1 = node->left;
                    node->left = parent->mid1->right;
                    if (node->left) node->left->parent = node;
                    node->mid2 = parent->mid1->mid2;
                    if (node->mid2) node->mid2->parent = node;

                    delete parent->mid1;
                    parent->mid1 = parent->mid2;
                    parent->mid2 = parent->right;
                    parent->right = NULL;

                    parent->keys.erase(parent->keys.begin() + 1);
                } else {
                    node->keys.push_back(parent->mid2->keys.back());
                    parent->mid2->keys.pop_back();

                    node->mid1 = node->left;
                    node->left = parent->mid2->right;
                    if (node->left) node->left->parent = node;
                    parent->mid2->right = parent->mid2->mid2;
                    parent->mid2->mid2 = NULL;
                }

                delete parent->right;
                parent->right = NULL;

                parent->keys.erase(parent->keys.begin());
                if (parent->size() == 0) {
                    fixTree(parent);
                }
            }
        }
    }

    void deleteKey(Node* node, int key) {
        if (node == NULL) return;

        if (find(node->keys.begin(), node->keys.end(), key) != node->keys.end()) {
            if (node->left == NULL) {
                node->removeKey(key);
                fixTree(node);
            } else {
                int index = distance(node->keys.begin(), find(node->keys.begin(), node->keys.end(), key));
                Node* successorNode = node;
                if (index == 0) successorNode = node->left;
                else if (index == 1) successorNode = node->mid1;
                else if (index == 2) successorNode = node->mid2;
                while (successorNode->left != NULL) successorNode = successorNode->left;

                int successorKey = successorNode->keys.front();
                node->keys[index] = successorKey;
                deleteKey(successorNode, successorKey);
            }
        } else {
            Node* nextNode = NULL;
            if (key < node->keys[0]) nextNode = node->left;
            else if (node->size() == 1 || (node->size() == 2 && key < node->keys[1])) nextNode = node->mid1;
            else if (node->size() == 3 && key < node->keys[2]) nextNode = node->mid2;
            else nextNode = node->right;
            deleteKey(nextNode, key);
        }
    }

public:
    TwoThreeFourTree() {
        root = NULL;
    }

    void insert(int key) {
        if (root == NULL) {
            root = new Node(key);
        } else {
            Node* leaf = findLeaf(root, key);
            leaf->insertKey(key);
            split(leaf);
        }
    }

    void remove(int key) {
        if (root == NULL) return;
        deleteKey(root, key);
        if (root->size() == 0 && root->left != NULL) {
            Node* oldRoot = root;
            root = root->left;
            root->parent = NULL;
            delete oldRoot;
        }
    }

    void print(Node* node, int level = 0) {
        if (node != NULL) {
            for (int i = 0; i < level; i++) cout << "  ";
            for (int key : node->keys) cout << key << " ";
            cout << endl;
            print(node->left, level + 1);
            print(node->mid1, level + 1);
            print(node->mid2, level + 1);
            print(node->right, level + 1);
        }
    }

    void display() {
        print(root);
    }
};

int main() {
    TwoThreeFourTree tree;
    tree.insert(5);
    tree.insert(10);
    tree.insert(15);
    tree.insert(20);
    tree.insert(25);
    tree.insert(30);
    tree.insert(35);
    tree.display();

    cout << "Deleting 15" << endl;
    tree.remove(15);
    tree.display();

    cout << "Deleting 25" << endl;
    tree.remove(25);
    tree.display();

    cout << "Deleting 30" << endl;
    tree.remove(30);
    tree.display();

    return 0;
}
