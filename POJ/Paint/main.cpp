//
//  main.cpp
//  Paint
//
//  Created by cmm on 2018/7/16.
//  Copyright © 2018年 bingyan. All rights reserved.
//

#include <iostream>
using namespace std;
int wall[17][17] = {0};
int paints[17][17] = {0};

int guess(int row){
    int steps = 0;
    for (int i = 1; i<row; i++){
        for (int j = 1; j<= row; j++){
            paints[i+1][j] = (wall[i][j] + paints[i-1][j] + paints[i][j] + paints[i][j+1]+ paints[i][j-1]) % 2;
            if (paints[i+1][j]) steps++;
        }
    }

    // 加上第一行的笔数
    for (int i=1; i<=row; i++){
        if (paints[1][i]) steps++;
    }
    for (int i = 1; i < row; i++){
        if((paints[row][i-1]+paints[row][i]+paints[row][i+1]+paints[row-1][i])%2 != wall[row][i])
            return -1;
    }
    return steps;
}

int emumerate(int row) {
    int c, steps = -1;
    while(paints[1][row+1]<1){
        int temp = guess(row);
        if ( temp != -1) {
            if (steps == -1) {
                steps = temp;
            } else {
                steps =  steps > temp ? temp : steps;
            }
        }
        paints[1][1]++;
        c = 1;
        while(paints[1][c]>1){
            paints[1][c] = 0;
            c++;
            paints[1][c]++;
        }
    }
    return steps;
}
void clear (int row) {
    for (int i = 0; i<=row+1; i++){
        for (int j = 0; j<=row+1; j++){
            paints[i][j] = 0;
            wall[i][j] = 0;
        }
    }
}
int main(int argc, const char * argv[]) {
//    int times;
//    cin>>times;
//    while(times--){
        int r = 0;
        char ch;
        cin>>r;
        clear(r); // 每次运行前清空遗留数据
        for (int i = 1; i<=r; i++){
            for (int j = 1; j<=r; j++){
                cin >> ch;
                wall[i][j] = ch=='w' ? 1 : 0;
            }
        }
        int result = emumerate(r);
        if (result >= 0) {
            cout<<result<<endl;
        } else {
            cout<<"inf"<<endl;
        }
//    }
    return 0;
}
