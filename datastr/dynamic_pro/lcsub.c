/**
 * longest common substring
 * @author lxumei
 */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAXLINE 5001

int dp[MAXLINE][MAXLINE];

void lcsub(char* str1, char* str2 ) {
    // write code here
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int maxlen = 0, index = 0;
    memset(dp, 0, sizeof(dp));

    if(len1 == 0 || len2 == 0){
        printf("Running result: maxlen = %d, index = %d, longest common substring = \"\"\n", maxlen, index);
        return;
    }

    for(int i=1; i <= len1; i++){
        for(int j=1; j <= len2; j++){
            if(str1[i-1] == str2[j-1]){
                dp[i][j] = dp[i-1][j-1] + 1;
                if(dp[i][j] > maxlen){
                    maxlen = dp[i][j];
                    index = i-1;
                }
            }else
                dp[i][j] = 0;
        }
    }

    if(maxlen == 0){
        printf("Running result: maxlen = %d, index = %d, longest common substring = \"\"\n", maxlen, index);
        return;
    }
    char *res = (char *)malloc((maxlen+1)* sizeof(char));
    memset(res, 0, maxlen+1);
    memcpy(res, str1+index-maxlen+1, maxlen);
    printf("Running result: maxlen = %d, index = %d, longest common substring = \"%s\"\n", maxlen, index, res);
}

int main(){
    char *str1, *str2;
    str1 = (char*)malloc(MAXLINE*sizeof(char));
    str2 = (char*)malloc(MAXLINE*sizeof(char));

    printf("Please input the str1: ");
    if(fgets(str1, MAXLINE, stdin) == NULL)
        printf("str1 error\n");
    str1[strlen(str1)-1] = '\0';                    /* replace \n with \0 */
    
    printf("Please input the str2: ");
    if(fgets(str2, MAXLINE, stdin) == NULL)
        printf("str1 error\n");
    str2[strlen(str2)-1] = '\0';

    lcsub(str1, str2);

    return 0;
}
