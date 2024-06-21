#include<iostream>
#include<vector>
#include<map>
#include<list>
#include<algorithm>
using namespace std;

class EdgeNode:public vertexNode{
  public:
    vertexNode* v1;
    vertexNode* v2;

	EdgeNode(){
	}

	EdgeNode(vertexNode* u,vertexNode* v){
		v1 = u;
		v2 = v;
	}

	~EdgeNode(){
	}
};

class vertexNode:public EdgeNode{
  public:
	int key;
	EdgeNode* parent;

	vertexNode(){
	}

	vertexNode(int v){
		key = v;
		parent = NULL;
	}

	~vertexNode(){
	}
};

class graph:public EdgeNode{
  public:
	list<vertexNode*> vertexList;
    list<EdgeNode*> edgeList;

	graph(){
	}

    void addVertex(int v){
		for(auto it = vertexList.begin(); it!=vertexList.end(); ++it){
			if((*it)->key == v) return;
		}
		vertexNode* newVertex = new vertexNode(v);
		vertexList.push_back(newVertex);
    }

	void addEdge(int u,int v,bool direction){
		if(u == v) return;
		vertexNode* v1;
		vertexNode* v2;
		bool foundU = false;
		bool foundV = false;
		for(auto it = vertexList.begin(); it!=vertexList.end(); ++it){
			if((*it)->key == u){
				foundU = true;
				v1 = *it;
				break;
			}
		}
		if(!foundU){
			vertexNode* v1 = new vertexNode(u);
			vertexList.push_back(v1);
		}
		for(auto it = vertexList.begin(); it!=vertexList.end(); ++it){
			if((*it)->key == v){
				foundV = true;
				v2 = *it;
				break;
			}
		}
		if(!foundV){
			vertexNode* v2 = new vertexNode(v);
			vertexList.push_back(v2);
		}
		for(auto it=edgeList.begin(); it!=edgeList.end(); ++it){
			if(((*it)->v1->key == u && (*it)->v2->key == v) || ((*it)->v1->key == v && (*it)->v2->key == u)) return;
			else{
				EdgeNode* newEdge = new EdgeNode(v1,v2);
				edgeList.push_back(newEdge);
			}
		}
	}
};

int main(){

}