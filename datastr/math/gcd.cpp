#include<iostream>
#include<algorithm>
using namespace std;

int gcd1(int x, int y){
   if(x < y)
       swap(x, y);
   
   int r = x % y;
   while(r){
       x = y;
       y = r;
       r = x % y;
   }

   return y;
}

int gcd2(int x, int y){
    if(x < y)
        swap(x, y);

    if(x % y == 0)
        return y;

    return gcd2(y, x % y);
}

int main(){
    
    int x, y;

    cin>>x>>y;

    cout<<"gcd1: "<<gcd1(x, y)<<endl;
    cout<<"gcd2: "<<gcd2(x, y)<<endl;

    return 0;
}
