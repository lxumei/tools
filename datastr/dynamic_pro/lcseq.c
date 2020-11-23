/**
 * longest common sequence
 * @author lxumei
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXLINE 1001

int dp[MAXLINE][MAXLINE], all = 0;
char res[MAXLINE], str1[MAXLINE], str2[MAXLINE];

void traceback(int i, int j, int index);
void lcseq_all();
char* lcseq_one();

int main(){
    printf("Please input the str1: ");
    if(fgets(str1, MAXLINE, stdin) == NULL)
        printf("str1 error\n");
    str1[strlen(str1)-1] = '\0';                /* replace \n with \0 */

    printf("Please input the str2: ");
    if(fgets(str2, MAXLINE, stdin) == NULL)
        printf("str1 error\n");
    str2[strlen(str2)-1] = '\0';

    lcseq_all();

    return 0;
}

void lcseq_all(){
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int i, j, index = 0;
    
    memset(dp, 0, sizeof(dp));
    
    for(i = 1; i <= len1; i++){
        for(j = 1; j <= len2; j++){
            if(str1[i-1] == str2[j-1]){
                dp[i][j] = dp[i-1][j-1] + 1;
            }else{
                dp[i][j] = dp[i][j-1] > dp[i-1][j] ? dp[i][j-1] : dp[i-1][j];
            }
        }
    }
    
    printf("The length of longest common sequence is : %d\n", dp[len1][len2]);
    traceback(len1, len2, dp[len1][len2]-1);
}

void traceback(int i, int j, int index){
    while(i > 0 && j > 0){
        if(str1[i-1] == str2[j-1]){
            res[index] = str1[i-1];
            //printf("%c %d\n", str1[i-1], index);
            index--;
            i--;
            j--;
        }else if(dp[i-1][j] > dp[i][j-1]){
            i--;
        }else if(dp[i-1][j] < dp[i][j-1]){
            j--;
        }else{
            traceback(i-1, j, index);
            traceback(i, j-1, index);
            return;
        }
    }
    printf("%s\n", res);
}

char* lcseq_one(){
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int dp[len1+1][len2+1];
    int i, j, maxlen, index = 0;
    
    if(len1 == 0 || len2 == 0)
        return "-1";
    
    memset(dp, 0, sizeof(dp));
    for(i = 1; i <= len1; i++){
        for(j = 1; j <= len2; j++){
            if(str1[i-1] == str2[j-1]){
                dp[i][j] = dp[i-1][j-1] + 1;
            }else{
                dp[i][j] = dp[i][j-1] > dp[i-1][j] ? dp[i][j-1] : dp[i-1][j];
            }
        }
    }
    
    maxlen = dp[len1][len2];
    if(maxlen == 0)
        return "-1";
    
    char* res_one = (char *)malloc((maxlen+1) * sizeof(char));
    memset(res_one, 0, maxlen + 1);
    index = maxlen - 1;
    i = len1;
    j = len2;
    while(i > 0 && j > 0){
        if(str1[i-1] == str2[j-1]){
            *(res_one + index) = str1[i-1];
            index--;
            i--;
            j--;
        }else if(dp[i-1][j] > dp[i][j-1]){
            i--;
        }else{
            j--;
        }
    }
    
    return res_one;
}
