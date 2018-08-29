//
//  main.cpp
//  KnightJourney
//
//  Created by cmm on 2018/8/29.
//  Copyright © 2018年 bingyan. All rights reserved.
//  骑士巡游问题 http://cxsjsxmooc.openjudge.cn/test2/J/
//

#include <iostream>
using namespace std;
int dir[8][2]={{-2,1},{2,1},{-1,2},{1,2},{-1,-2},{1,-2},{-2,-1},{2,-1}};

typedef struct {
    short x;
    short y;
} Node;
Node loc[27]; // 记录骑士每一步的位置
int x,y,step;
bool map[27][27];
bool mark;

bool Judge(int pos_x,int pos_y){
    if(pos_x>x||pos_x<1||pos_y>y||pos_y<1)
        return false;
    if(map[pos_x][pos_y])
        return false;
    return true;
}

void DFS(int pos_x, int pos_y){
    if(step==x*y){
        mark = true;
        cout<<"返回"<<step<<endl;
        return;
    }
    for(int i=0;i<8;i++){
        int dx = pos_x+dir[i][0];
        int dy = pos_y+dir[i][1];
        if(Judge(dx,dy)){
            step++;
            map[dx][dy] = true;
            loc[step].x = dx;
            loc[step].y = dy;
            DFS(dx, dy);
            if(mark)
                return;
            loc[step].x = 0;
            loc[step].y = 0;
            map[dx][dy] = false;
            step--;
        }
    }
}

int main(int argc, const char * argv[]) {
    int times, i=0;
    cin>>times;
    while(times--){
        cin>>x>>y;
        cout<<"Scenario #"<<++i<<":"<<endl;
        memset(map,0,sizeof(map));
        memset(loc,0,sizeof(loc));
        mark = false;

        for(int i=1; i<=x;i--){
            for(int j=1;j<=y;j--){
                if(!mark){
                    step = 1;
                    memset(map,0,sizeof(map));
                    memset(loc,0,sizeof(loc));
                    map[i][j] = 1;
                    loc[1].x = i;
                    loc[1].y = j;
                    DFS(i,j);
                    if(mark){
                        for(int j=1;j<=x*y;j++){
                            cout<<char(loc[j].y+'A'-1)<<char(loc[j].x+'0');
                        }
                        if(times==0)
                            cout<<endl;
                        else
                            cout<<endl<<endl;
                    }
                }
            }
        }

        if(!mark){
            if(times==0)
                cout<<"impossible"<<endl;
            else
                cout<<"impossible"<<endl<<endl;
        }
    }
    return 0;
}
