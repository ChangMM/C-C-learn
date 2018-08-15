//
//  main.cpp
//  Frog
//
//  Created by cmm on 2018/7/16.
//  Copyright © 2018年 bingyan. All rights reserved.
//  POJ 青蛙路径问题
//

#include <iostream>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef struct Plant {
    int x;
    int y;
} PLANT;
PLANT plants[5001];

bool operator<(const PLANT &p1, const PLANT &p2) {
    if (p1.x == p2.x) {
        return p1.y<p2.y;
    } else {
        return p1.x<p2.x;
    }
}

int searchPath(PLANT secPlant, int dX, int dY, int r, int c, int n) {
    int steps = 0;
    PLANT plant;
    plant.x = secPlant.x + dX;
    plant.y = secPlant.y + dY;
    steps = 2;
    while(plant.x<=r && plant.x>=1 && plant.y<=c && plant.y>=1) {
        if (!binary_search(plants, plants+n, plant)) {
            steps = 0;
            break;
        }
        plant.x += dX;
        plant.y += dY;
        steps++;
    }
    return steps;
}

int main(int argc, const char * argv[]) {
    int row, col, num; // 稻田的行列值 以及 被践踏的水稻的数量
    scanf("%d %d", &row, &col);
    scanf("%d", &num);
    for(int i=0; i < num; i++) {
        scanf("%d %d", &plants[i].x, &plants[i].y);
    }
    sort(plants, plants+num);
    int pY, pX, dX, dY, max = 2, steps = 0;
    for(int i = 0; i< num-2; i++) {
        for(int j=i+1; j< num-1; j++){
            dX = plants[j].x-plants[i].x;
            dY = plants[j].y-plants[i].y;
            pX = plants[i].x-dX;
            pY = plants[i].y-dY;
            if (pX<=row && pX>=1 && pY<=col && pY>=1){
                continue;
            }
            if((plants[i].x + (max-1)*dX)>row){
                break;
            }
            int nY = plants[i].y+(max-1)*dY;
            if (nY>col || nY<1) {
                continue;
            }
            steps = searchPath(plants[i], dX, dY, col, row, num);
            if (steps>max) {
                max = steps;
            }
        }
    }
    if (max == 2) {
        max = 0;
    }
    printf("%d\n", max);
    return 0;
}
