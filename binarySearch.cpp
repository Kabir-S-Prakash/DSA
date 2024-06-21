#include<iostream>
using namespace std;

int binarySearch(int *arr,int k,int low, int high){
    int s = low;
    int e = high;
    int mid = (s+e)/2;
    if (arr[mid] == k)
    {
        return mid;
    }
    else if (arr[mid]>k)
    {
        e = mid-1;
        return binarySearch(arr,k,s,e);
    }
    else if (arr[mid]>k){
        s = mid+1;
        return binarySearch(arr,k,s,e);
    }
    return -1;
}

int main(){
    int arr[5] = {11,23,44,56,78};
    cout<<binarySearch(arr,99,0,4);
}