//
//  main.cpp
//  BlockGame
//
//  Created by cmm on 2018/8/7.
//  Copyright © 2018年 bingyan. All rights reserved.
//  方盒游戏：动态规划
//

#include <iostream>
#include <cstring>
using namespace std;
struct Block {
    int len;
    int color;
};
struct Block segment[200];
int score[200][200][200]; // 存放计算结果，避免重复计算

int click_box(int start, int end, int ex_len){
    int i, result, temp;

    if(score[start][end][ex_len] > 0) { // 避免重复计算
        return score[start][end][ex_len];
    }
    result = segment[end].len + ex_len;
    result = result*result; //end 和 ex_len一块消除得分

    if (start == end) { // 递归结束项
        score[start][end][ex_len]= result;
        return score[start][end][ex_len];
    }

    result = result + click_box(start, end-1, 0);
    i = end -1;
    for (i = end - 1; i >= start; i--) {
        if(segment[i].color != segment[end].color) {
            continue;
        } else {
            temp = click_box(start, i, ex_len + segment[end].len) + click_box(i+1, end-1, 0);
            if (temp < result) {
                continue;
            } else {
                result = temp;
            }
        }
    }
    score[start][end][ex_len] = result;
    return score[start][end][ex_len];
}

int main(int argc, const char * argv[]) {
    int t,n,color,end;
    cin>>t;
    for (int i=0;i<t;i++) {
        cin >> n;
        end = 0;
        cin >> segment[end].color;
        segment[end].len = 1;
        for (int j=1;j<n;j++) {
            cin >> color;
            if (color==segment[end].color){
                segment[end].len++;
            } else {
                end++;
                segment[end].color = color;
                segment[end].len = 1;
            }
        }
        memset(score,0,sizeof(score));
        cout << "Case " << i+1 << ": " << click_box(0,end,0) << endl;
    }
    return 0;
}
