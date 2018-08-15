//
//  main.cpp
//  CastleDFS
//
//  Created by cmm on 2018/8/15.
//  Copyright © 2018 bingyan. All rights reserved.
//  深度搜索之城堡问题
//

#include <iostream>
#include <stack>
using namespace std;

int m, n, roomNum = 0, maxRoomAero = 0, curRoomAera;
int map[50][50], color[50][50] = {0};
struct Room{
    int x, y;
    Room(int x, int y):x(x),y(y) {}
};

void dfs(int i, int j) { // 深度搜索解法
    color[i][j] = roomNum;
    curRoomAera++;
    if (((map[i][j] & 1) == 0) && (j > 0) && !color[i][j-1]) dfs(i, j-1);
    if (((map[i][j] & 2) == 0) && (i > 0) && !color[i-1][j]) dfs(i-1, j);
    if (((map[i][j] & 4) == 0) && (j+1 < n) && !color[i][j+1]) dfs(i, j+1);
    if (((map[i][j] & 8) == 0) && (i+1 < m) && !color[i+1][j]) dfs(i+1, j);
}

void dfs_stack(int startX, int startY) { //用栈来代替深度搜索
    stack<Room> stack;
    stack.push(Room(startX, startY));
    int x, y;
    while (!stack.empty()) {
        Room topRoom = stack.top();
        x = topRoom.x;
        y = topRoom.y;
        if (color[x][y])
            stack.pop();
        else {
            curRoomAera++;
            color[x][y] = roomNum;
            if (((map[x][y] & 1) == 0) && (y > 0) && !color[x][y-1])
                stack.push(Room(x, y-1));
            if (((map[x][y] & 2) == 0) && (x > 0) && !color[x-1][y])
                stack.push(Room(x-1, y));
            if (((map[x][y] & 4) == 0) && (y+1 < n) && !color[x][y+1])
                stack.push(Room(x, y+1));
            if (((map[x][y] & 8) == 0) && (x+1 < m) && !color[x+1][y])
                stack.push(Room(x+1, y));
        }
    }
}

int main()
{
    cin >> m >> n;
    for( int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            cin >> map[i][j];
    for( int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (!color[i][j]) {
                roomNum++;
                curRoomAera = 0;
                dfs(i, j);
                if (curRoomAera > maxRoomAero)
                    maxRoomAero = curRoomAera;
            }
    cout << roomNum << endl << maxRoomAero;
}
