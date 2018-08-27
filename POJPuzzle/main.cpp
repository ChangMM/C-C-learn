//
//  main.cpp
//  POJPuzzle
//
//  Created by cmm on 2018/8/27.
//  Copyright © 2018年 bingyan. All rights reserved.
//  广度搜索解决迷宫问题 http://cxsjsxmooc.openjudge.cn/test2/H/
//

#include <iostream>
#include <queue>
using namespace std;

int maze[5][5] = { // 迷宫的路径
    0, 1, 0, 0, 0,
    0, 1, 0, 1, 0,
    0, 0, 0, 0, 0,
    0, 1, 1, 1, 0,
    0, 0, 0, 1, 0,
};

typedef struct{
    short x;
    short y;
} node;

typedef struct{ // 定义每个节点的标记
    bool visited;
    node prevNode;
    node curNode;
} flag;

short dir[4][2] = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};

flag flags[5][5];

queue<flag> openQueue;  // open表

void printPath(int i, int j){
    node curNode = flags[i][j].curNode, prevNode = flags[i][j].prevNode;
    if(curNode.x == prevNode.x && curNode.y == prevNode.y){
        cout<<"("<<curNode.x<<","<<curNode.y<<")";
        return;
    } else {
        printPath(prevNode.x, prevNode.y);
        cout<<"-->"<<"("<<curNode.x<<","<<curNode.y<<")";
    }
}

int main(int argc, const char * argv[]) {
    for(int i=0; i<5;i++)
        for(int j=0; j<5;j++){
            flag flagItem;
            flagItem.visited = false;
            flagItem.prevNode.x = 0;
            flagItem.prevNode.y = 0;
            flagItem.curNode.x = i;
            flagItem.curNode.y = j;
            flags[i][j] = flagItem;
        }

    flags[0][0].visited = true;
    openQueue.push(flags[0][0]);

    while(!openQueue.empty()){
        flag curFlag = openQueue.front();
        node curNode = curFlag.curNode;
        if(curNode.x == 4 && curNode.y ==4) {
            cout<<"Find a path:";
            printPath(4, 4);
            cout<<endl;
            return 0;
        }
        for(int i=0; i<4; i++) { // 四个方向
            int dx = curNode.x + dir[i][0];
            int dy = curNode.y + dir[i][1];
            if(dx>=0&&dx<=4&&dy>=0&&dy<=4&&maze[dx][dy]==0&&!flags[dx][dy].visited) {
                flags[dx][dy].prevNode = curNode;
                flags[dx][dy].visited = true;
                openQueue.push(flags[dx][dy]);
            }
        }
        openQueue.pop();
    }
    return 0;
}
