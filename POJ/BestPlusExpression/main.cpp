//
//  main.cpp
//  BestPlusExpression
//
//  Created by cmm on 2018/8/8.
//  Copyright © 2018年 bingyan. All rights reserved.
//  最佳加法表达式 https://d396qusza40orc.cloudfront.net/pkupop/lectures/Week13/W13-04_动归之几个例题.pdf
//

#include <iostream>
#include <algorithm>
#include<cstring>
#include<string>
using namespace std;
int plusCount;
int strlen_n;
string numbers;
string store[51][51];

#define INFINITE "99999999999999999999999999999999999999999999999999";

// 比较两个字符串大小
bool str_num_comp(const string & n1,const string & n2){
    if(n1.length() != n2.length()){
        return n1.length() > n2.length();
    }else{
        unsigned long len = n1.length();
        for(int i=0;i<len;i++){
            if(n1[i]!=n2[i]){
                return n1[i]>n2[i];
            }
        }
        return false;
    }
}

// 两个字符串相加
string add_number(const string & n1,const string & n2){
    string result;
    result=n1;
    const string & n3=n2;
    unsigned long result_len=result.length();
    unsigned long n3_len=n3.length();
    for(int i=1;i<=n3_len;i++){
        result[result_len-i]+=n3[n3_len-i]-'0';
    }
    for(unsigned long i=result_len-1; i>0; i--){ //最高位单独考虑
        while(result[i]>'9'){
            result[i]-=10;
            result[i-1]++;
        }
    }
    char c='0';
    if(result[0]>'9'){
        while(result[0]>'9'){
            c++;
            result[0]-=10;
        }
        result.insert(0,1,c);
    }
    return result;
}

string min_num(int m,int left){
    if(store[m][left] != "") return store[m][left];
    if(m==0){ //加号用完了
        string result = "";
        result.append(numbers, left, strlen_n-left);
        store[m][left]=result;
        return result;
    } else if (m > strlen_n-left-1){ // 加号过多
        store[m][left] = INFINITE;
        return store[m][left];
    }else{
        string str = INFINITE;
        for(int i=left;i<strlen_n;i++){
            string s = "";
            s.append(numbers,left,i-left+1);
            string s1=min_num(m-1,i+1);
            string s2;
            if(s.length()>s1.length()){
                s2=add_number(s,s1);
            }else{
                s2=add_number(s1,s);
            }
            if(str_num_comp(str,s2)){
                str=s2;
            }
        }
        store[m][left]=str;
        return str;
    }
}

int main(int argc, const char * argv[]) {
    while(cin>>plusCount){
        for(int i=0;i<=50;i++){
            for(int j=0;j<=50;j++){
                store[i][j] = "";
            }
        }
        cin>>numbers;
        strlen_n = int(numbers.length());
        cout<<min_num(plusCount,0)<<endl;
    }
    return 0;
}
