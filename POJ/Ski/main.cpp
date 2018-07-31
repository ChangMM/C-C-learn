//
//  main.cpp
//  Ski
//
//  Created by cmm on 2018/7/31.
//  Copyright © 2018年 bingyan. All rights reserved.
//  滑雪问题
//

#include <iostream>
using namespace std;
int point[100][100];
int MAX[100][100]={0};
int row, col;

int calMax(int i, int j){
    int max = 0;
    if(MAX[i][j]>0)
        return MAX[i][j];
    if(i-1>=0 && point[i][j]>point[i-1][j] && max<calMax(i-1,j))
        max = calMax(i-1, j);
    if(i+1<=row && point[i][j]>point[i+1][j] && max<calMax(i+1,j))
        max = calMax(i+1, j);
    if(j-1>=0 && point[i][j]>point[i][j-1] && max<calMax(i,j-1))
        max = calMax(i, j-1);
    if(j+1<=col && point[i][j]>point[i][j+1] && max<calMax(i,j+1))
        max = calMax(i, j+1);
    MAX[i][j] = max +1;
    return MAX[i][j];
}

int main(int argc, const char * argv[]) {
    int maxStep=0;
    cin>>row>>col;
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            cin>>point[i][j];
        }
    }

    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            calMax(i, j);
            if(maxStep<MAX[i][j])
                maxStep = MAX[i][j];
        }
    }
    cout<<maxStep;
    return 0;
}
