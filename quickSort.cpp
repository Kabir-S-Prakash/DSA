#include<iostream>
using namespace std;

int partition(int* arr,int s,int e){
    int x = arr[s];
    int p1 = s;
    int p2 = e;
    int cnt = 0;
    for(int i=s+1; i<=e; i++){
        if(arr[i]<=x) cnt++;
    }
    int pivot = s+cnt;
    swap(arr[s],arr[pivot]);
    while(p1<pivot && p2>pivot){
        while(arr[p1]<pivot) p1++;
        while(arr[p2]>pivot) p2--;
        if(p1<pivot && p2>pivot) swap(arr[p1],arr[p2]);
    }
    return pivot;
}

void quickSort(int* arr,int s,int e){
    if(s>=e) return;
    int pivot = partition(arr,s,e);
    quickSort(arr,s,pivot-1);
    quickSort(arr,pivot+1,e);
}

int main(){
    int n;
    cin>>n;
    int* arr = new int[n];
    for(int i=0; i<n; i++){
        cin>>arr[i];
    }
    quickSort(arr,0,n-1);
    for(int i=0; i<n; i++){
        cout<<arr[i]<<" ";
    } cout<<endl;
}