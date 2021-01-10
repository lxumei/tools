#include<iostream>
#include<vector>
using namespace std;

void bubble_sort(vector<int> &nums, int n){
    for(int i = 0; i < n; i++){
        int flag = 1;
        for(int j = 0; j < n - i -1; j++)
            if(nums[j] > nums[j+1]){
                flag = 0;
                int tmp = nums[j];
                nums[j] = nums[j+1];
                nums[j+1] = tmp;
            }
        if(flag)
            break;
    }
}

int main(){
    
    int n;
    
    while(cin>>n){
        vector<int> nums(n, 0);

        for(int i = 0; i < n; i++){
            cin>>nums[i];
        }

        bubble_sort(nums, n);

        for(int i = 0; i < n; i++){
            cout<<nums[i]<<" ";
        }

        cout<<endl<<endl;
    }

    return 0;
}
