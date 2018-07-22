//
//  main.cpp
//  CheckerBoard
//
//  Created by cmm on 2018/7/23.
//  Copyright © 2018年 bingyan. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

int s[9][9];//每个格子的分数
int sum[9][9];//(1,1)到(i,j)的矩形的分数之和
int res[15][9][9][9][9];//fun记录表

int cal_sum(int x1, int y1, int x2, int y2){
    return sum[x2][y2]-sum[x2][y1-1]-sum[x1-1][y2]+sum[x1-1][y1-1];
}

int fun(int n, int x1, int y1, int x2, int y2){
    //以(x1,y1)为左上角，(x2,y2)为右上角的棋盘分割成n份后的最小平方和
    int MIN = 1000000;
    if (res[n][x1][y1][x2][y2] != -1){
        return res[n][x1][y1][x2][y2]; //返回已经计算过的值
    }
    if (n==1) {
        int t = cal_sum(x1, y1, x2, y2);
        res[n][x1][y1][x2][y2] = t*t;
        return t*t;
    }
    int sum1, sum2, result;
    for(int a=x1;a<x2;a++){ //沿x方向分割
        sum1 = cal_sum(x1, y1, a, y2);
        sum2 = cal_sum(a+1, y1, x2, y2);
        result = min(fun(n-1,x1,y1,a,y2)+sum2*sum2, fun(n-1,a+1,y1,x2,y2)+sum1*sum1);
        if (MIN > result) {
            MIN = result;
        }
    }

    for(int b=y1;b<y2;b++){ //沿y方向分割
        sum1 = cal_sum(x1,y1,x2,b);
        sum2 = cal_sum(x1,b+1,x2,y2);
        result = min(fun(n-1,x1,y1,x2,b)+sum2*sum2, fun(n-1,x1,b+1,x2,y2)+sum1*sum1);
        if(MIN > result){
            MIN = result;
        }
    }
    res[n][x1][y1][x2][y2] = MIN;
    return MIN;
}

int main(int argc, const char * argv[]) {
    memset(sum, 0, sizeof(sum));
    memset(res, -1, sizeof(res));
    int n;
    cin>>n;
    for(int i=1;i<9;i++){
        for(int j=1,rowsum=0;j<9;j++){
            cin>>s[i][j];
            rowsum+=s[i][j];//行之和
            sum[i][j]=sum[i-1][j]+rowsum;//总和
        }
    }
    double result = n*fun(n, 1, 1, 8, 8) - sum[8][8]*sum[8][8];
    printf("%.3lf\n",sqrt(result/(n*n)));
    return 0;
}
