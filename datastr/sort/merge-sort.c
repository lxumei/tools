#include<iostream>
#include<vector>
using namespace std;

void mergeArrays(vector<int> &nums, int left, int mid, int right){
    vector<int> num1, num2;
    int len1 = mid - left + 1, len2 = right - mid;

    for(int i = left; i <= mid; i++){
        num1.push_back(nums[i]);
    }
    
    for(int i = mid + 1; i <= right; i++){
        num2.push_back(nums[i]);
    }

    int i = 0, j = 0;
    while(i < len1 && j < len2){
        if(num1[i] <= num2[j]){
            nums[left++] = num1[i++];
        }else{
            nums[left++] = num2[j++];
        }
    }

    while(i < len1){
        nums[left++] = num1[i++];
    }

    while(j < len2){
        nums[left++] = num2[j++];
    }
}

void mergeSort(vector<int> &nums, int left, int right){
    if(left >= right)
        return;
    
    int mid = (left + right)/2;

    mergeSort(nums, left, mid);
    mergeSort(nums, mid + 1, right);
    mergeArrays(nums, left, mid, right);
}

int main(){
    
    int n;
    
    while(cin>>n){
        vector<int> nums(n, 0);

        for(int i = 0; i < n; i++){
            cin>>nums[i];
        }

        mergeSort(nums, 0, n-1);

        for(int i = 0; i < n; i++){
            cout<<nums[i]<<" ";
        }

        cout<<endl<<endl;
    }

    return 0;
}
