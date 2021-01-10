#include<iostream>
#include<vector>
using namespace std;

void max_heapify(vector<int> &nums, int i, int end){
    int left_id = i * 2 + 1;
    int right_id = i * 2 + 2;
    int largest = i;

    if(left_id <= end && nums[left_id] > nums[largest])
        largest = left_id;

    if(right_id <= end && nums[right_id] > nums[largest])
        largest = right_id;

    if(largest == i)
        return;
    
    swap(nums[i], nums[largest]);
    max_heapify(nums, largest, end);
}

void heapSort(vector<int> &nums, int n){
    int i;

    for(i = n / 2 - 1; i >=0; i--)
        max_heapify(nums, i, n - 1);

    for(i = n - 1; i > 0; i--){
        swap(nums[0], nums[i]);
        max_heapify(nums, 0, i-1);
    }
}

int main(){
    
    int n;
    
    while(cin>>n){
        vector<int> nums(n, 0);

        for(int i = 0; i < n; i++){
            cin>>nums[i];
        }

        heapSort(nums, n);

        for(int i = 0; i < n; i++){
            cout<<nums[i]<<" ";
        }

        cout<<endl<<endl;
    }

    return 0;
}
