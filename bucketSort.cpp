#include<iostream>
#include<vector>
using namespace std;

void bucketSort(int A[],int n){
    int maa = INT16_MIN;
    for(int i=0; i<n; i++){
        maa = max(maa,A[i]);
    }
    int freq[maa+1];
    for(int i=0; i<maa; i++) freq[i] = 0;
    for(int i=0; i<n; i++){
        freq[A[i]]++;
    }
    int B[n];
    int c = 0;
    for(int i=0; i<maa+1; i++){
        for(int j=0; j<freq[i]; j++){
            B[c] = i;
            c++;
        }
    }
    for(int i=0; i<n; i++){
        A[i] = B[i];
    }
}
int main(){
    int arr[10] = {3,2,1,2,3,1,1,2,3,2};
    bucketSort(arr,10);

    for(int i=0; i<10; i++){
        cout<<arr[i]<<" ";
    } cout<<endl;
}