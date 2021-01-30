class Solution {
public:
    /**
     * min edit cost
     * @param str1 string字符串 the string
     * @param str2 string字符串 the string
     * @param ic int整型 insert cost
     * @param dc int整型 delete cost
     * @param rc int整型 replace cost
     * @return int整型
     * 求将字符串str1变为str2的最小编辑代价，ic、dc、rc分别为插入代价、删除代价、替换代价
     */
    int minEditCost(string str1, string str2, int ic, int dc, int rc) {
        int len1 = str1.size();
        int len2 = str2.size();

        vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));
        dp[0][0] = 0;

        for(int i = 1; i <= len1; i++)
            dp[i][0] = i * dc;
        for(int i = 1; i <= len2; i++)
            dp[0][i] = i * ic;

        for(int i = 1; i <= len1; i++){
            for(int j = 1; j <= len2; j++){
                if(str1[i-1] == str2[j-1])
                    dp[i][j] = dp[i-1][j-1];
                else
                    dp[i][j] = min(min(dp[i-1][j] + dc, dp[i][j-1] + ic), dp[i-1][j-1] + rc);
            }
        }

        return dp[len1][len2];        
    }
};
