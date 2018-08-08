//
//  main.cpp
//  BoardGame
//
//  Created by cmm on 2018/8/7.
//  Copyright © 2018年 bingyan. All rights reserved.
//  Help Jimmy(POJ1661)
//

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

#define MAX_N 1001
#define INFINITE 1000000

struct Platform{
    int Lx, Rx, h;
    bool operator < (const Platform & p2) const {
        return h > p2.h;
    }
};

Platform platForms[MAX_N];
int leftMinTime[MAX_N];
int rightMinTime[MAX_N];
int platformCount, maxHeight;

int minTime(int l,bool bLeft){
    int y = platForms[l].h;
    int x;
    if(bLeft)
        x = platForms[l].Lx;
    else
        x = platForms[l].Rx;
    int i;
    for( i = l+1; i<=platformCount; i++ ) {
        if( platForms[i].Lx <= x && platForms[i].Rx >= x)
            break;
    }
    if(i<=platformCount){
        if(y-platForms[i].h > maxHeight)
            return INFINITE;
    } else {
        if(y>maxHeight)
            return INFINITE;
        else
            return y;
    }
    int nLeftTime = y - platForms[i].h + x - platForms[i].Lx;
    int nRightTime = y - platForms[i].h + platForms[i].Rx - x;
    if(leftMinTime[i] == -1)
        leftMinTime[i] = minTime(i,true);

    if(rightMinTime[i] == -1)
        rightMinTime[i] = minTime(i, false);

    nLeftTime = nLeftTime + leftMinTime[i];
    nRightTime = nRightTime + rightMinTime[i];

    return min(nLeftTime, nRightTime);
}

int main(int argc, const char * argv[]) {
    int times;
    int init_x, init_y;
    cin>>times;
    for(int i=0;i<times;i++){
        memset(leftMinTime, -1, sizeof(leftMinTime));
        memset(rightMinTime, -1, sizeof(leftMinTime));
        cin>>platformCount>>init_x>>init_y>>maxHeight;
        platForms[0].Rx = init_x;
        platForms[0].Lx = init_x;
        platForms[0].h = init_y;
        for(int j=1; j<=platformCount; j++){
            cin>>platForms[j].Lx>>platForms[j].Rx>>platForms[j].h;
        }
        sort(platForms, platForms+platformCount+1);
        cout<<minTime(0, true);
    }
    return 0;
}
