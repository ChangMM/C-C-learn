    //
    //  main.cpp
    //  LianlianGame
    //
    //  Created by cmm on 2018/7/20.
    //  Copyright © 2018年 bingyan. All rights reserved.
    //  递归解决练练看小游戏
    //

#include <iostream>
#include <memory.h>
#include <deque>

using namespace std;
#define MAX 75
char board[MAX+2][MAX+2];
bool mark[MAX+2][MAX+2];
int minStep, w, h, direction[4][2]={{0,1},{0,-1},{-1,0},{1,0}};
deque<int*> path;

void clear(){
    for(int i=0; i<MAX+2; i++){
        for(int j=0; j<MAX+2; j++){
            board[i][j] = ' ';
        }
    }
}
void Search(int now_x, int now_y, int end_x, int end_y, int step, int f) {
    if (step > minStep) {
        return ;
    }
    if (now_x== end_x&&now_y==end_y) {
        minStep = step;
        cout<<"路径为：";
        for (int i = 0; i < path.size(); i++){
            cout<<"("<<path[i][0]<<", "<<path[i][1]<<")";
        }
        cout<<endl;
        return ;
    }
    int item[2] ={0};
    for (int i = 0; i<4; i++) {
        int x = now_x + direction[i][0];
        int y = now_y + direction[i][1];
        if((x>-1)&&(x<w+2)&&(y>-1)&&(y<h+2)&&(((board[y][x]==' ')&&(mark[y][x]==false))||((x==end_x)&&(end_y==y)&&(board[y][x]=='X')))){
            mark[y][x] = true;
            item[0] = x;
            item[1] = y;
            path.push_back(item);
            if(f==i) {
                Search(x, y, end_x, end_y, step, i);
            } else {
                Search(x, y, end_x, end_y, step+1, i);
            }
            path.pop_back();
            mark[y][x] = false;
        }
    }
}

int main(int argc, const char * argv[]) {
    int times = 0;
    while(cin>>w>>h){
        if(w==0&&h==0){
            break;
        }
        times++;
        cout<<"Board #"<< times <<":"<<endl;
        clear(); //清空画板

        for(int i=1; i<=h; i++) {
            getchar();
            for(int j=1; j<=w; j++)
                board[i][j] = getchar();
        }

        int begin_x, begin_y, end_x, end_y, count=0;
        while(cin>>begin_x>>begin_y>>end_x>>end_y && begin_x>0){
            if(begin_x==0&&begin_x==0&&end_x==0&end_y==0){
                break;
            }
            count++;

            // 初始化最小路径值、清空标记以及路径栈
            minStep = 10000;
            memset(mark, false, sizeof(mark));
            path.clear();

            Search(begin_x, begin_y, end_x, end_y, 0, -1);
            if (minStep < 10000){
                cout<<"Pair "<<count<<": "<<minStep<<" segments."<<endl;
            }else{
                cout<<"Pair "<<count<<": impossible."<<endl;
            }

        }
    }

    return 0;
}

