//
//  main.cpp
//  SimpleFindPath
//
//  Created by cmm on 2018/8/17.
//  Copyright © 2018年 bingyan. All rights reserved.
//  POJ 1724简单的寻路问题
//


#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
#define INFINITY (1<<30) //后面不可以加逗号

int K,N,R,S,D,L,T; // K 💰、N 城市、R 路的数目、
struct Road {
    int d,L,t; // d 路的终点城市、L 路的长度、 t 路的花费
};
vector<vector<Road> > cityMap(110); //邻接表。cityMap[i]是从点i有路连到的城市集合
int minLen = INFINITY; //当前找到的最优路径的长度
int totalLen; //正在走的路径的长度
int totalCost ; //正在走的路径的花销
int visited[110]; //城市是否已经走过的标记
int minL[110][10100]; //minL[i][j]表示从1到i点的，花销为j的最短路的长度

void DFS(int s){
    if(s == N) {
        minLen = min(minLen, totalLen);
        return;
    }

    for(int i=0; i<cityMap[s].size(); i++){
        int d = cityMap[s][i].d; //s有到d的路
        if(!visited[d]) {
            int cost = totalCost = cityMap[s][d].t;
            if(cost>K)
                continue;

            int pathLen = totalLen + cityMap[s][i].L;
            if( pathLen >= minLen || pathLen > minL[d][cost])
                continue;

            totalLen += cityMap[s][i].L;
            totalCost += cityMap[s][i].t;
            minL[d][totalCost] = totalLen;
            visited[d] = 1;
            DFS(d);
            visited[d] = 0;
            totalLen -= cityMap[s][i].L;
            totalCost -= cityMap[s][i].t;
        }
    }
}

int main(){
    cin>> K >> R >> N;
    for(int i=0; i<N; i++){
        int s;
        Road r;
        cin>>s>>r.d>>r.L>>r.t;
        if(s != r.d){
            cityMap[s].push_back(r);
        }
    }
    for(int i=0;i<110;i++){
        for(int j=0;j<10100;j++)
            minL[i][j] = INFINITY;
    }
    memset(visited, 0, sizeof(visited));
    totalLen = 0;
    totalCost = 0;
    visited[1] = 1;
    minLen = INFINITY;
    DFS(1);
    if(minLen<INFINITY){
        cout<<minLen<<endl;
    }else{
        cout<< "-1" <<endl;
    }
    return 0;
}







