#include<iostream>
#include<vector>
using namespace std;

void prefix_table(string &pattern, vector<int> &prefix, int n){
    prefix[0] = 0;
    int len = 0;
    int i = 1;

    while(i < n){
        if(pattern[i] == pattern[len]){
            len++;
            prefix[i] = len;
            i++;
            continue;
        }
        if(len > 0)
            len = prefix[len - 1];
        else{
            i++;
            prefix[i] = 0;
        }
    } 
}

void move_prefix_table(vector<int> &prefix, int n){
    int i;
    for(int i = 1; i < n; i++)
        prefix[i] = prefix[i-1];
    prefix[0] = -1;
}

void kmp_search(string& text, string& pattern){
    int n = pattern.size();
    int m = text.size();
    vector<int> prefix(pattern.size());
    prefix_table(pattern, prefix, n);
    move_prefix_table(prefix, n);
    
    //text[i] len(text) = m
    //pattern[j] len(pattern) = n

    int i = 0, j = 0;
    while(i < m){
        if(j == n-1 && text[i] == pattern[j]){
            cout<<"Found pattern at " << i - j <<endl;
            j = prefix[j];
        }
        else if(text[i] == pattern[j]){
            i++;
            j++;
        }else{
            j = prefix[j];
            if(j == -1){
                i++;
                j++;
            }
        }
    }

}

int main(){

    string str1 = "ABABCABAA";
    string str2 = "ABABCABAABABCABAA";
    kmp_search(str2, str1);

    return 0;
}
