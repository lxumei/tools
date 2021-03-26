#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int partition1(vector<int> &nums, int left, int right){
    int key = nums[right];
    int i = left;                                                                                                               
    //将小于key的数从位置left开始存在数组里
    for(int j = left; j <= right-1; j++){
        if(nums[j] < key){
            swap(nums[i], nums[j]);
            i++;
        }
    }
    
    //for循环结束，此时比key小的数都放在了i之前；
    //将key放在位置i处。
    swap(nums[i], nums[right]);
    return i;
}

int partition2(vector<int> &nums,int left, int right){
    int key = nums[left];

    while(left < right){
        while(left < right && nums[right] > key)
            right--;
        nums[left] = nums[right];

        while(left < right && nums[left] <= key)
            left++;
        nums[right] = nums[left];
    }

    nums[left] = key;
    return left;
}

void quickSort(vector<int> &nums, int left, int right){
    if(left >= right)
        return;
    
    int partition_index = partition1(nums, left, right);
    quickSort(nums, left, partition_index - 1);
    quickSort(nums, partition_index + 1, right);
}

int main(){
    
    int n;
    
    while(cin>>n){
        vector<int> nums(n, 0);

        for(int i = 0; i < n; i++){
            cin>>nums[i];
        }

        quickSort(nums, 0, n-1);

        for(int i = 0; i < n; i++){
            cout<<nums[i]<<" ";
        }

        cout<<endl<<endl;
    }

    return 0;
}
