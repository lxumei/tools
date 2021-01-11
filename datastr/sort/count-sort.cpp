#include<iostream>
#include<vector>
using namespace std;

void countSort(vector<int> &nums, int n, int max){
   vector<int> count(max + 1, 0);
   vector<int> sorted(n, 0);

   for(int i = 0; i < n; i++)
       count[nums[i]]++;

   for(int i = 1; i < max + 1; i++){
       count[i] = count[i] + count[i-1];
   }

   for(int i = 0; i < n; i++){
        sorted[count[nums[i]] - 1] = nums[i];
        count[nums[i]] = count[nums[i]] - 1;
   }

   for(int i = 0; i < n; i++){
       cout<<sorted[i]<<" ";
   }

   cout<<endl;
}

int main(){
    
    int n;
    
    while(cin>>n){
        vector<int> nums(n, 0);
        int max = 0;

        for(int i = 0; i < n; i++){
            cin>>nums[i];
            if(nums[i] > max)
                max = nums[i];
        }
        
        countSort(nums, n, max);
    }

    return 0;
}
