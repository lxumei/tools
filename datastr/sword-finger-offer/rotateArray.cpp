#include<iostream>
using namespace std;

int minNumberInRotateArray(vector<int> rotateArray) {
    int len = rotateArray.size();
    if(len == 0)
        return 0;
    int left = 0, right = len - 1, mid;
    
    while(left < right){
        mid = left + (right - left) / 2;
        if(rotateArray[left] < rotateArray[right])
            return rotateArray[left];
        if(rotateArray[left] < rotateArray[mid])
            left = mid;
        else if(rotateArray[right] > rotateArray[mid])
            right = mid;
        else 
            left++;     
    }
    
    return rotateArray[left];
}

/*
   如果输入的数据没有重复的数字，那么是不需要18-19行、12-13行。
   如果有重复的数据，例如(1,0,1,1,1) 或 (1,1,1,0,1)，就需要上面这几行完成
   left逐渐指向数组中最大的元素，right逐渐指向数组中最小的元素
   当left中的值小于right中的值时，说明left移动到了最小的元素，立即返回
   最后返回rotateArray[left]和rotateArray[right]都是可以的，理论上走到这步的时候left == right
 */
