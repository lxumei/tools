/*
Levenshtein 距离，又称编辑距离，指的是两个字符串之间，由一个转换成另一个所需的最少编辑操作次数。
许可的编辑操作包括将一个字符替换成另一个字符，插入一个字符，删除一个字符。
编辑距离的算法是首先由俄国科学家Levenshtein提出的，故又叫Levenshtein Distance。

Ex：

字符串A:abcdefg

字符串B: abcdef

通过增加或是删掉字符”g”的方式达到目的。这两种方案都需要一次操作。把这个操作所需要的次数定义为两个字符串的距离。

要求：

给定任意两个字符串，写出一个算法计算它们的编辑距离。
*/

#include<iostream>
#include<vector>
using namespace std;

int main(){
    string str1, str2;
    
    while(cin>>str1>>str2){
        int len1 = str1.size();
        int len2 = str2.size();
        
        vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));
        dp[0][0] = 0;
        
        for(int i = 1; i <= len1; i++)
            dp[i][0] = i;
        for(int i = 1; i <= len2; i++)
            dp[0][i] = i;
        
        for(int i = 1; i <= len1; i++){
            for(int j = 1; j <= len2; j++){
                dp[i][j] = min(min(dp[i-1][j], dp[i][j-1]) + 1, 
                               (str1[i-1] == str2[j-1] ? 0 : 1) + dp[i-1][j-1]);
            }
        }
        
        cout<<dp[len1][len2]<<endl;
    }
    
    return 0;
}
