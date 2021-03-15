#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main(){
    int n;
    vector<int> v;
    while(cin>>n){
        for(int i = 0; i < n; i++){
            int tmp;
            cin>>tmp;
            if(find(v.begin(), v.end(), tmp) == v.end())
                v.push_back(tmp);
        }
        sort(v.begin(), v.end());
        for(int i = 0; i < v.size(); i++)
            cout<<v[i]<<endl;
    }
    return 0;
}
