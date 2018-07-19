    //
    //  main.cpp
    //  LianlianGame
    //
    //  Created by cmm on 2018/7/20.
    //  Copyright © 2018年 bingyan. All rights reserved.
    //  地柜解决练练看小游戏
    //

#include <iostream>
#include <memory.h>

using namespace std;
#define MAX 75
char board[MAX+2][MAX+2];
bool mark[MAX+2][MAX+2];
int minStep, w, h, direction[4][2]={{0,1},{0,-1},{-1,0},{1,0}};

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
        if (minStep > step) {
            minStep = step;
        }
        return ;
    }
    for (int i = 0; i<4; i++) {
        int x = now_x + direction[i][0];
        int y = now_y + direction[i][1];
        if((x>-1)&&(x<w+2)&&(y>-1)&&(y<h+2)&&(((board[y][x]==' ')&&(mark[y][x]==false))||((x==end_x)&&(end_y==y)&&(board[y][x]=='X')))){
            mark[y][x] = true;
            if(f==i) {
                Search(x, y, end_x, end_y, step, i);
            } else {
                Search(x, y, end_x, end_y, step+1, i);
            }
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
            minStep = 10000;
            memset(mark, false, sizeof(mark));
            Search(begin_x, begin_y, end_x, end_y, 0, -1);
            if (minStep < 10000)
                printf("Pair %d: %d segments.\n", count, minStep);
            else
                printf("Pair %d: impossible.\n", count);
        }
    }

    return 0;
}

