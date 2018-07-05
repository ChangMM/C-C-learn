//
//  main.cpp
//  InputInfo
//
//  Created by cmm on 2018/7/5.
//  Copyright © 2018年 bingyan. All rights reserved.
//  学生成绩的输入处理
//

#include <iostream>
using namespace std;

class student {
    int age, score1, score2, score3, score4, averageScore;
    char name[20], id[20];
    
public:
    void init();
    void getAverageScore();
    void printInfo();
};

void student::init(){
    char temp;
    cin.getline(name, 20, ',');
    cin>>age>>temp;
    cin.getline(id, 20, ',');
    cin>>score1>>temp>>score2>>temp>>score3>>temp>>score4;
}

void student::getAverageScore(){
    averageScore = (int)((score1+score2+score3+score4) / 4);
}

void student::printInfo(){
    cout<<name<<','<<age<<','<<id<<','<<averageScore<<endl;
}


int main(int argc, const char * argv[]) {
    student* tom = new student;
    tom->init();
    tom->getAverageScore();
    tom->printInfo();
    delete tom;
    return 0;
}
