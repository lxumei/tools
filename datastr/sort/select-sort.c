#include<iostream>
#include<vector>
using namespace std;

void selectSort(vector<int> &nums, int n){
    for(int i = 0; i < n; i++){
        int min_index = i;
        for(int j = i+1; j < n; j++){
            if(nums[j] < nums[min_index]){
                min_index = j;
            }
        }
        int tmp = nums[i];
        nums[i] = nums[min_index];
        nums[min_index] = tmp;
    }
}

int main(){
    
    int n;
    
    while(cin>>n){
        vector<int> nums(n, 0);

        for(int i = 0; i < n; i++){
            cin>>nums[i];
        }

        selectSort(nums, n);

        for(int i = 0; i < n; i++){
            cout<<nums[i]<<" ";
        }

        cout<<endl<<endl;
    }

    return 0;
}
