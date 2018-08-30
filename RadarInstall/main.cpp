//
//  main.cpp
//  RadarInstall
//
//  Created by cmm on 2018/8/31.
//  Copyright © 2018年 bingyan. All rights reserved.
//  POJ1328  贪心2分法 解决问题
//

#include <iostream>
#include <algorithm>
#include <math.h>

using namespace std;

#define MAXN (1000+10)

// 线段两端
struct Node {
    double left,  right;
};

int T, n, d;
Node s[MAXN];

// Node按照左端点从小到达排序
bool operator < (const Node &a, const Node &b){
    return a.left < b.left;
}

int Solve(){
    int ans;
    double now;
    //按左端点排序
    sort(s, s+n);
    //若当前线段与目前集合中的线段没有公共交点, 则新加入一个雷达
    ans = 1;
    now = s[0].right;
    for (int i = 1;i < n;++i){
        if (s[i].left <= now)
            now = min(now, s[i].right);
        else {
            ++ans;
            now = s[i].right;
        }
    }
    return ans;
}

int main(int argc, const char * argv[]) {
    int x,  y;
    bool flag;
    T = 0;
    while (1) {
        ++T;
        cin>>n>>d;
        if (n == 0 && d == 0) break;
        flag = true;
        for (int i = 0;i < n;++i){
            cin>>x>>y;
            if (y > d) {
                flag = false;
                break;
            }
            else {
                s[i].left  = x - sqrt( d*d - y*y );
                s[i].right = x + sqrt( d*d - y*y );
            }
        }
        //若有小岛距离x轴大于d,则输出-1
        if (flag)
           cout<<"Case "<<T<<": "<<Solve()<<endl;
        else
            cout<<"Case "<<T<<": -1"<<endl;
    }
    return 0;
}
