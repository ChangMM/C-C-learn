//
//  main.cpp
//  POJ3278
//
//  Created by cmm on 2018/8/27.
//  Copyright © 2018年 bingyan. All rights reserved.
//  广度优先搜索解决 POJ3278
//

#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
int N,K; // N表示初始位置， K表示目标位置
const int MAXN = 100000;
int visited[MAXN+10]; //判重标记,visited[i] = true表示i已经扩展过
struct Step{
    int x; //当前位置
    int steps; //到达x所需的步数
    Step(int x,int s):x(x),steps(s){}
};
queue<Step> openQ; //队列,即Open表

void PrintPath(int start, int end){
    if(end == start){
        cout<<start;
        return;
    } else {
        PrintPath(start, visited[end]);
        cout<<"-->"<<end;
    }
}

int main(int argc, const char * argv[]) {
    cin >> N >> K;
    memset(visited,-1,sizeof(visited));
    openQ.push(Step(N,0));
    visited[N] = N;
    while(!openQ.empty()){
        Step s = openQ.front();
        if(s.x == K) { //找到目标
            cout<<"min path steps is:"<<s.steps<<endl;
            PrintPath(N,K);
            cout<<endl;
            return 0;  //需要另做处理
        } else {
            if(s.x-1 >= 0 && visited[s.x-1] == -1) {
                openQ.push(Step(s.x-1,s.steps+1));
                visited[s.x-1] = s.x;
            }
            if(s.x+1 <= MAXN && visited[s.x+1] == -1) {
                openQ.push(Step(s.x+1,s.steps+1));
                visited[s.x+1] = s.x;
            }
            if(s.x*2 <= MAXN && visited[s.x*2] == -1) {
                openQ.push(Step(s.x*2,s.steps+1));
                visited[s.x*2] = s.x;
            }
            openQ.pop();
        }
    }
    cout<<N<<K;
    return 0;
}
