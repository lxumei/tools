#include<iostream>
#include<vector>
#include<math.h>
using namespace std;

void print(vector<vector<char>> &g, int x, int y, int n){
    if(n == 1){
        g[x][y] = 'o';
        return;
    }

    int m = pow(3, n-2);
    print(g, x, y, n-1);
    print(g, x-m, y, n-1);
    print(g, x+m, y, n-1);
    print(g, x, y-m, n-1);
    print(g, x, y+m, n-1);

}
int main(){

    int n;
    cin>>n;
    
    int m = pow(3, n-1);
    int x = m / 2;
    vector<vector<char>> g(m, vector<char>(m, ' '));

    print(g, x, x, n);

    for(int i = 0; i < m; i++){
        for(int j = 0; j < m; j++)
            cout<<g[i][j]<<' ';
        cout<<endl;
    }

    return 0;
}
