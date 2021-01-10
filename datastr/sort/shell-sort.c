#include<iostream>
#include<vector>
using namespace std;

void shellSort0(vector<int> &nums, int n){
    int h = 1;
    while(h < n / 3){
        h = 3 * h + 1;
    }

    while(h >= 1){
        for(int i = h; i < n; i++){
            for(int j = i; j >= h && nums[j] < nums[j - h]; j -= h){
                int tmp = nums[j];
                nums[j] = nums[j-h];
                nums[j-h] = tmp;
            }
        }
        h = h / 3;
    }
}

void shellSort(vector<int> &nums, int n){
    int gap, i, j, tmp;
    for(gap = n >> 1; gap > 0; gap >>= 1){
        for(i = gap; i < n; i ++){
            tmp = nums[i];
            j = i - gap;
            while(j >= 0 && nums[j] > tmp){
                nums[j + gap] = nums[j];
                j -= gap;
            }
            nums[j + gap] = tmp;
        }
    }
}

int main(){
    
    int n;
    
    while(cin>>n){
        vector<int> nums(n, 0);

        for(int i = 0; i < n; i++){
            cin>>nums[i];
        }

        shellSort(nums, n);

        for(int i = 0; i < n; i++){
            cout<<nums[i]<<" ";
        }

        cout<<endl<<endl;
    }

    return 0;
}
