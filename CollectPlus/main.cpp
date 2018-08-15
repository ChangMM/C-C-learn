//
//  main.cpp
//  CollectPlus
//
//  Created by cmm on 2018/7/31.
//  Copyright © 2018年 bingyan. All rights reserved.
//  不知道利用动态规划怎么解决这个问题
//

#include <iostream>
using namespace std;

int main(int argc, const char * argv[]) {
    int n ,s, A[10001], B[10001], aNum, bNum, num;
    cin>>n;
    while(n--){
        num = 0;
        cin>>s>>aNum;
        for(int i=0;i<aNum;i++){
            cin>>A[i];
        }
        cin>>bNum;
        for(int i=0;i<bNum;i++){
            cin>>B[i];
        }
        for(int i = 0; i < aNum; i++)
            {
            for(int j = 0; j < bNum; j++)//依次遍历(i,j)的每一种取值即可
                {
                if(A[i] + B[j] == s)
                    num++;
                }
            }
        cout << num << endl;
    }
    return 0;
}
