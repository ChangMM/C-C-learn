//
//  main.cpp
//  TurnOffLights
//
//  Created by cmm on 2018/7/10.
//  Copyright © 2018年 bingyan. All rights reserved.
//  POJ 熄灯问题
//

#include <iostream>
using namespace std;
int puzzle[6][8] = {0}, press[6][8] = {0};

bool guess(){
    for(int r = 1; r<5; r++){
        for(int c = 1; c < 7; c++){
            press[r+1][c] = (puzzle[r][c] + press[r][c] + press[r-1][c] + press[r][c-1] + press[r][c+1])%2;
        }
    }
    for(int c = 1;c < 7; c++){
        if ((press[5][c-1]+press[5][c]+press[5][c+1]+press[4][c])%2 != puzzle[5][c]) {
            return false;
        }
    }
    return true;
}

void enumerate() {
    int c;
    while(!guess()){
        press[1][1]++;
        c = 1;
        while(press[1][c]>1){
            press[1][c] = 0;
            c++;
            press[1][c]++;
        }
    }
}

int main(int argc, const char * argv[]) {
    int r = 0, c = 0;
    // 输入灯原有的状态
    for(r=1; r<6; r++) {
        for(c=1; c<7; c++) {
            scanf("%d", &puzzle[r][c]); //读入输入数据
        }
    }
    enumerate();
    // 输出结果
    for (r=1; r<6; r++) {
        for (c=1; c<7; c++) {
            printf("%d ", press[r][c]);
        }
        printf("\n");
    }
    return 0;
}
