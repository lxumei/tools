#include<iostream>
#include<vector>
using namespace std;

void print(vector<vector<int>> A, int x, int y){
    cout<<x<<" "<<y<<endl;

    if(x >= 0 && x < A.size() && y >= 0 && y < A[0].size())
        A[x][y] = 1 - A[x][y];
}
int main(){

    vector<vector<int>> A;
    vector<vector<int>> f;

    A.push_back({0,0,1,1});
    A.push_back({1,0,1,0});
    A.push_back({0,1,1,0});
    A.push_back({0,0,1,0});

    f.push_back({2,2});
    f.push_back({3,3});
    f.push_back({4,4});

    for(auto cur : f){
        int x = cur[0];
        int y = cur[1];
        
        print(A, x, y);
    }

    return 0;
}
