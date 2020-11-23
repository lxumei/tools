/**
 * retrun the longest increasing subsequence
 * @param arr int整型一维数组 the array
 * @param arrLen int arr数组长度
 * @return int整型一维数组
 * @return int* return the smallest dict sequence
 */ 

void Reverse(int* arr1, int* arr2, int len){
    for(int i=0; i<len; i++){
        arr1[i] = arr2[len-1-i];
    }
}

void traceback(int* dp, int* min_arr, int index, int* arr, int len, int maxLen){
    if(len-1==0){
        min_arr[maxLen-len] = arr[index];
        //printf("min_arr[%d] = %d\n", maxLen-len, arr[index]);
        return;
    }
    
    int min_value = -1, min_index = -1;
    int flag = 1;
    
    min_arr[maxLen-len] = arr[index];
    //printf("min_arr[%d] = %d\n", maxLen-len, arr[index]);
    
    for(int i=index-1; i>=0; i--){
        if(flag == 1 && dp[i] == len-1){
            min_value = arr[i];
            min_index = i;
            flag = 0;
            continue;
        }
        if(dp[i] == len-1 && arr[i] > arr[index]){
            if(arr[i] < min_value){
                min_value = arr[i];
                min_index = i;
            }
        }
    }
    
    //printf("min_index = %d,  len-1 = %d\n", min_index, len-1);
    traceback(dp, min_arr, min_index, arr, len-1, maxLen);
}

int* LIS(int* arr, int arrLen, int *returnSize){
    int dp[arrLen+1], maxLen = 1;
    int re_arr[arrLen+1];
    
    Reverse(re_arr, arr, arrLen);
    
    for(int i = 0; i < arrLen; i++){
        dp[i] = 1;
        for(int j = 0; j < i; j++){
            if(re_arr[i] < re_arr[j] && dp[i] < dp[j] + 1){
                dp[i] = dp[j] + 1;
            }
        }
        if(maxLen < dp[i])
            maxLen = dp[i];
    }
    
    /*
    for(int i=0; i<arrLen; i++){
        printf("%d %d\n", re_arr[i], dp[i]);
    }
    printf("\n");
    printf("maxLen = %d\n", maxLen);
    */
    
    int min_index = -1, min_value = -1;
    int *min_res = (int*)malloc((maxLen+1)*4);
    for(int i=arrLen-1; i>=0; i--){
        if(min_value == -1 && dp[i] == maxLen){
            min_index = i;
            min_value = re_arr[i];
            continue;
        }
        if(dp[i] == maxLen && re_arr[i] < min_value){
            min_index = i;
            min_value = re_arr[i];
        }
    }
    traceback(dp, min_res, min_index, re_arr, maxLen, maxLen);
    
    *returnSize = maxLen;
    return min_res;
}

