#include<iostream>
#include<vector>
using namespace std;

// int to binary number
vector<bool> intToBinary(int x) {
    vector<bool> ans;
    if (x == 0) {
        ans.push_back(0);
        return ans;
    }
    while (x > 0) {
        ans.push_back(x % 2);
        x /= 2;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

// create binary array out of int array
pair<vector<vector<bool> >, int> intToBinaryArray_maxBit(int A[], int n) {
    vector<vector<bool> > ans;
    int maxBit = 0;
    for (int i = 0; i < n; i++) {
        vector<bool> binary = intToBinary(A[i]);
        if (binary.size() > maxBit) {
            maxBit = binary.size();
        }
        ans.push_back(binary);
    }

    for (int i = 0; i < n; i++) {
        while (ans[i].size() < maxBit) {
            ans[i].insert(ans[i].begin(), 0);
        }
    }

    return make_pair(ans, maxBit);
}

// partition into top and bottom subarray
int partition(vector<vector<bool> >& binaryArray, int bit, int s, int e) {
    int left = s;
    int right = e;

    while (true) {
        while (left <= e && binaryArray[left][bit] == 0) left++;
        while (right >= s && binaryArray[right][bit] == 1) right--;

        if (left < right) {
            swap(binaryArray[left], binaryArray[right]);
        } else {
            return right;
        }
    }
}

// sort the binary array
void Sort(vector<vector<bool> >& binaryArray, int bit, int s, int e) {
    if (s >= e || bit >= binaryArray[0].size()) return;

    int j = partition(binaryArray, bit, s, e);
    Sort(binaryArray, bit + 1, s, j);
    Sort(binaryArray, bit + 1, j + 1, e);
}

// radix sort
void radixExchangeSort(int A[], int n) {
    pair<vector<vector<bool> >,int> binaryData = intToBinaryArray_maxBit(A, n);
    vector<vector<bool> > binaryArray = binaryData.first;
    int bits = binaryData.second;

    Sort(binaryArray, 0, 0, n - 1);

    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = 0; j < binaryArray[i].size(); j++) {
            sum = (sum << 1) | binaryArray[i][j];
        }
        A[i] = sum;
    }
}

int main(){
    int A[7] = {3,32,17,44,36,22,18};
    radixExchangeSort(A,7);
    for(int i=0; i<7; i++){
        cout<<A[i]<<" ";
    } cout<<endl;
}