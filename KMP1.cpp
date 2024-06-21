#include<iostream>
#include<vector>
using namespace std;

vector<int> prefix_function(string P){
    int m = P.size();
    vector<int> h(m);
    for(int i=0; i<m; i++){
        for(int k=0; k<=i; k++){
            if(P.substr(0,k) == P.substr(i+1-k,k)) h[i] = k;
        }
    }
    return h;
}

bool isPresent(string s,string P,vector<int> h){
    int j = 0;
    int i = 0;
    int start = 0;
    while(j < s.size()){
        if(s[j] == P[start+i]){
            j++;
            i++;
        }
        else{
            start += i-h[i];
        }
        if(start+i == s.size()-1) return true;
    }
    return false;
}

int main(){
    string P;
    cin>>P;
    int m = P.size();
    vector<int> h = prefix_function(P);
    string s;
    cin>>s;
    cout<<isPresent(s,P,h);
}