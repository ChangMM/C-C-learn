//
//  main.cpp
//  RiseSubSequence
//
//  Created by cmm on 2018/8/6.
//  Copyright © 2018年 bingyan. All rights reserved.
//  最长上升子序列的问题
//

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN =1010;
int a[MAXN];
int maxLen[MAXN];

int main(int argc, const char * argv[]) {
    int N;
    cin>>N;
    for(int i=1; i<=N; i++){
        cin>>a[i];
        maxLen[i] = 1;
    }

    for(int i=1; i<=N; i++){
        for(int j=i+1; j<=N; j++){
            if(a[j]>a[i]){
                maxLen[j] = max(maxLen[j], maxLen[i]+1);
            }
        }
    }
    cout<<*max_element(maxLen+1, maxLen+N+1);
    return 0;
}
