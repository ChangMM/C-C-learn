//
//  main.cpp
//  POJ
//
//  Created by cmm on 2018/7/6.
//  Copyright © 2018年 bingyan. All rights reserved.
//  POJ 上面会有 runtime error的错误
//

#include <iostream>
#include <cstring>
using namespace std;

class Array2{
    int *a;
    int i,j;
public:
    Array2(){
        a = NULL;
    }
    Array2(int m, int n){
        i = m;
        j = n;
        a = new int(m*n);
    }
    Array2(Array2& a_){
        i = a_.i;
        j = a_.j;
        a = new int[i*j];
        memcpy(a, a_.a, sizeof(int)*i*j);
    }
    ~Array2() {
        if (a != NULL)
            delete []a;
    }
    
    Array2& operator= (const Array2 &a_){
        if (a == a_.a){
            return *this;
        }
        if (a != NULL) delete []a;
        i = a_.i;
        j = a_.j;
        a = new int(i*j);
        memcpy(a, a_.a, sizeof(int)*i*j);
        return *this;
        
    }
    
    int* operator[](int m){
        return a + m*j;
    }
    
    int& operator()(int m, int n){
        return a[m*j+n];
    }
};


int main() {
    Array2 a(3,4);
    int i,j;
    for( i = 0;i < 3; ++i )
        for( j = 0; j < 4; j ++ )
            a[i][j] = i * 4 + j;
    for( i = 0;i < 3; ++i ) {
        for( j = 0; j < 4; j ++ ) {
            cout << a(i,j) << ",";
        }
        cout << endl;
    }
    cout << "next" << endl;
    Array2 b; b = a;
    for( i = 0;i < 3; ++i ) {
        for( j = 0; j < 4; j ++ ) {
            cout << b[i][j] << ",";
        }
        cout << endl;
    }
    return 0;
}
