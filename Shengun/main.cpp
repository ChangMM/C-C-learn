//
//  main.cpp
//  Shengun
//
//  Created by cmm on 2018/8/20.
//  Copyright © 2018年 bingyan. All rights reserved.
//  深度搜索之神棍问题 POJ-1011
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N; // 木棒的总数
int L; // 要拼成棍子的长度
vector<int> anLength; // 每一根木棒的长度
int anUsed[65]; //是否用过的标记

bool DFS(int R, int M){
    if(R==0&&M==0)
        return true;
    if(M==0) //一根刚刚拼完，开始新的一根
        M=L;
    for(int i=0;i<N;i++){
        if(!anUsed[i]&&anLength[i]<=M){
            if(i>0&&!anUsed[i-1]&&anUsed[i-1]==anUsed[i])
                continue;
            anUsed[i] = 1;
            if(DFS(R-1, M-anLength[i]))
                return true;
            else{
                anUsed[i] = 0;
                if(M==L || anLength[i] == M)
                    return false;
            }
        }
    }
    return false;
}

int main(int argc, const char * argv[]) {
    cin>>N;
    int nTotalLen = 0; // 所有木棒的总长度
    for( int i = 0; i < N; i ++ ) {
        int n;
        cin >> n;
        anLength.push_back(n);
        nTotalLen += anLength[i];
    }
    sort(anLength.begin(), anLength.end(), greater<int>()); // 木棒从长到段的排序
    for(L=anLength[0];L<=nTotalLen/2;L++){
        if(nTotalLen%L) //如果不能整除直接略过
            continue;
        memset(anUsed, 0, sizeof(anUsed));
        if(DFS(anLength.size(), L)){
            cout<<L<<endl;
            break;
        }
    }
    if(L>nTotalLen/2)
        cout<<nTotalLen<<endl;
    return 0;
}
