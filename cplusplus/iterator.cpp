#include<iostream>
#include<vector>
#include<map>
using namespace std;

int main(){
    vector<int> v{1,2,3,4,5,6,7,8,9,10};
    vector<int>::iterator it;
    for(it = v.begin(); it != v.end(); it++)
        cout<<*it<<" ";

    map<int, int> mp;
    mp[0] = 0;
    mp[1] = 1;
    mp[2] = 2;
    mp[3] = 3;
    map<int, int>::iterator mp_it;
    for(mp_it = mp.begin(); mp_it != mp.end(); mp_it++){
        cout<<mp_it->first<<", "<<mp_it->second<<endl;
    }

    return 0;
}
