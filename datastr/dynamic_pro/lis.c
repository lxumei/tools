
int *res;
int flag = 0;
int *min_res;
int dp[10001];
int global_max_len;

int cmp(int* arr1, int* arr2){
    for(int i=0; i<global_max_len; i++){
        if(arr1[i] < arr2[i])
            return 1;
        else if(arr1[i] > arr2[i])
            return 0;
    }
    return 0;
}

/* dp[index] = maxlen */
void traceback(int index, int* nums, int maxlen){
    if(maxlen==1){
        res[maxlen-1] = nums[index];
        if(flag == 0 || cmp(res, min_res)){
            flag = 1;
            for(int i=0; i<global_max_len; i++)
                min_res[i] = res[i];
            for(int i=0; i<global_max_len; i++)
                printf("%d ", res[i]);
            printf("\n");
        }
        return;
    }
    
    res[maxlen-1] = nums[index];
    
    for(int i=0; i<index; i++){
        if(dp[i] == maxlen-1 && nums[i] < nums[index]){
            traceback(i, nums, maxlen-1);
        }
    }
}

int lengthOfLIS(int* nums, int numsSize){
    int maxlen = 1;
    
    for(int i=0; i<numsSize; i++){
        dp[i] = 1;
        for(int j=0; j<i; j++){
            if(nums[i] > nums[j]){
                dp[i] = dp[j]+1 > dp[i] ? dp[j]+1 : dp[i];
            }
        }
        if(maxlen < dp[i])
            maxlen = dp[i];
    }
    
    global_max_len = maxlen;
    res = malloc(maxlen*4);
    min_res = malloc(maxlen*4);

    printf("Longest increase sequence includes: \n");
    for(int i=0; i<numsSize; i++){
        if(dp[i] == maxlen)
            traceback(i, nums, maxlen);
    }
    
    printf("The smallest dict sequence is: \n");
    for(int i=0; i<maxlen; i++)
        printf("%d ", min_res[i]);
    
    free(min_res);
    free(res);
    return maxlen;
}

