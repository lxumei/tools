#include<iostream>
#include<pthread.h>
using namespace std;

int a, b;

void* countA(void *args){
    a = 10;
    cout<<"countA"<<endl;
    //printf("%s", (char *)(0x10000));
    cout<<a<<endl;
}

void* countB(void *args){
    b = 100;
    cout<<"countB"<<endl;
    cout<<b<<endl;
}

int main(){
   
    pthread_t tids[2];

    for(int i = 0; i < 2; i++){
        int ret;
        if(i == 0)
            ret = pthread_create(&tids[i], NULL, countB, NULL);
        else
            ret = pthread_create(&tids[i], NULL, countA, NULL);

        if(ret != 0)
            cout<<"pthread_create error: error_code = "<<ret<<endl;
    }
    cout<<"this is the main function"<<endl;
    cout<<a+b<<endl;
    return 0;
}
