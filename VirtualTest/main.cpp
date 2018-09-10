//
//  main.cpp
//  VirtualTest
//
//  Created by cmm on 2018/9/10.
//  Copyright © 2018年 bingyan. All rights reserved.
//

#include <iostream>
using namespace std;

class parent{
public:
    int a;
    virtual void print(){
        cout<<"parent"<<endl;
    }
};

class son:public parent{
public:
    int b;
    void print(){
        cout<<"son"<<endl;
    }
};

int main(int argc, const char * argv[]) {
    son s;
    parent *p = &s;
    p->print();
    return 0;
}
