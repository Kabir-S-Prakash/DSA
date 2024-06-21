#include<iostream>
using namespace std;

void merge(int* arr,int s,int e){
    int mid = (s+e)/2;
    int len1 = mid+1-s;
    int len2 = e-mid;

    int* arrLeft = new int[len1];
    int* arrRight = new int[len2];

    int c = 0;
    for(int i=s; i<=mid; i++){
        arrLeft[c] = arr[i];
        c++;
    }
    c = 0;
    for(int i=mid+1; i<=e; i++){
        arrRight[c] = arr[i];
        c++;
    }
    c = s;

    int p1=0, p2=0;
    while(p1<len1 && p2<len2){
        if(arrLeft[p1]<arrRight[p2]){
            arr[c] = arrLeft[p1];
            p1++;
            c++;
        }
        else{
            arr[c] = arrRight[p2];
            p2++;
            c++;
        }
    }
    while(p1<len1){
        arr[c] = arrLeft[p1];
        p1++;
        c++;
    }
    while(p2<len2){
        arr[c] = arrRight[p2];
        p2++;
        c++;
    }
    delete []arrLeft;
    delete []arrRight;
}

void mergeSort(int* arr,int s,int e){
    // Base case
    if(s >= e) return;

    int mid = (s+e)/2;
    // Sort Left Part
    mergeSort(arr,s,mid);

    // Sort Right Part
    mergeSort(arr,mid+1,e);

    // Merge
    merge(arr,s,e);
}

int main(){
    int n;
    cin>>n;
    int arr[n];
    for(int i=0; i<n; i++){
        cin>>arr[i];
    }
    mergeSort(arr,0,n-1);
    for(int i=0; i<n; i++){
        cout<<arr[i]<<" ";
    } cout<<endl;
}