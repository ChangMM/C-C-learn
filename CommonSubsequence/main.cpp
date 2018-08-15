//
//  main.cpp
//  CommonSubsequence
//
//  Created by cmm on 2018/8/7.
//  Copyright © 2018年 bingyan. All rights reserved.
//  最长公共子序列问题
//

#include <iostream>
#include <cstring>
using namespace std;
char sz1[1000];
char sz2[1000];
int maxLen[1000][1000];

int main(int argc, const char * argv[]) {
    while(cin>>sz1>>sz2){
        int length1 = strlen(sz1), length2 = strlen(sz2);
        cout<<sz1<<sz1<<endl;
        for(int i=0; i<length1; i++){
            maxLen[i][0] = 0;
        }
        for(int i=0; i<length2; i++){
            maxLen[0][i] = 0;
        }
        for(int i=1; i<=length1; i++){
            for(int j=1; j<=length2; j++){
                if(sz1[i-1]==sz2[j-1]){
                    maxLen[i][j] = maxLen[i-1][j-1]+1;
                } else {
                    maxLen[i][j] = max(maxLen[i][j-1], maxLen[i-1][j]);
                }
            }
        }
        cout<<maxLen[length1][length2]<<endl;
    }
    return 0;
}
