//
//  main.c
//  queen
//
//  Created by cmm on 2018/7/4.
//  Copyright © 2018年 bingyan. All rights reserved.
//  Eight Queen!
//

#include <stdio.h>
#include <math.h>
#define LINE 8
int queen[LINE], sum = 0;

// 判断皇后位置是否冲突
int isConflict (int n) {
    for (int i = 0; i < n; i++){
        if (queen[i] == queen[n] || abs(queen[n]-queen[i])==(n-i)) {
            return 0;
        }
    }
    return 1;
}

// 回溯算法 递归版
void EightQueen (int start) {
    if (start >= LINE) {
        printf("第%d种情况：\n", sum++);
        for (int i = 0; i < LINE; i++) {
            printf("(%d,%d) ", i, queen[i]);
        }
        printf("\n");
    } else {
        for (int i = 0; i < LINE; i++) {
            queen[start] = i;
            if (isConflict(start)) {
                EightQueen(start + 1);
            }
        }
    }
    return ;
}

int main(int argc, const char * argv[]) {
    EightQueen(0);
    return 0;
}
