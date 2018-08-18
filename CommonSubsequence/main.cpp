//
//  main.cpp
//  CommonSubsequence
//
//  Created by cmm on 2018/8/7.
//  Copyright © 2018年 bingyan. All rights reserved.
//  1、最长公共子序列的最长长度
//  2、打印出所有的最长公共子序列
//

#include <iostream>
#include <cstring>
using namespace std;
char sz1[1000];
char sz2[1000];
int maxLen[1000][1000];
char flag[1000][1000];

int LCS(int length1, int length2){
    for(int i=1; i<=length1; i++){
        for(int j=1; j<=length2; j++){
            if(sz1[i-1]==sz2[j-1]){
                maxLen[i][j] = maxLen[i-1][j-1]+1;
                flag[i][j] = 'H';
            } else if (maxLen[i][j-1] <= maxLen[i-1][j]){
                maxLen[i][j] = maxLen[i-1][j];
                flag[i][j] = 'U';
            } else {
                maxLen[i][j] = maxLen[i][j-1];
                flag[i][j] = 'L';
            }
        }
    }
    return maxLen[length1][length2];
}

void printLCS(int i, int j){
    if(i == 0 || j == 0){
        return;
    }
    if(flag[i][j] == 'H'){
        cout<<i<<j<<'H'<<' ';
        printLCS(i-1, j-1);
        cout<<sz1[i-1];
    } else if(flag[i][j] == 'U') {
        cout<<i<<j<<'U'<<' ';
        printLCS(i-1, j);
    } else {
        cout<<i<<j<<'L'<<' ';
        printLCS(i, j-1);
    }
}

int main(int argc, const char * argv[]) {
    while(cin>>sz1>>sz2){
        int length1 = strlen(sz1), length2 = strlen(sz2);
        for(int i=0; i<length1; i++){
            maxLen[i][0] = 0;
        }
        for(int i=0; i<length2; i++){
            maxLen[0][i] = 0;
        }
        int max = LCS(length1, length2);
        cout<<max<<endl;
        for(int i=max;i<=length1;i++){
            if(maxLen[i][length2]==max&&flag[i][length2] != 'U'){
                printLCS(i, length2);
                cout<<endl;
            }
        }
        for(int j=max;j<=length2;j++){
            if(maxLen[length1][j]==max&&flag[length1][j] != 'U'){
                printLCS(length1, j);
                cout<<endl;
            }
        }
    }
    return 0;
}
