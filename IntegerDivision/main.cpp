//
//  main.cpp
//  IntegerDivision
//
//  Created by cmm on 2018/9/5.
//  Copyright © 2018年 bingyan. All rights reserved.
//  动态规划经典问题 整数划分问题的各种情形
/*  1、N划分成若干个可相同正整数之和
 *  2、N划分成若干个不同正整数之和
 *  3、N划分成K个正整数之和
 *  4、N划分成若干个奇正整数之和
 */
//
/*
 整数划分问题这几个变形确实很经典，需要一个个说明下：
 1、设dp[n][m]表示数n划分方案中，每个数 不大于m 的划分数。
 N划分成若干个可相同正整数之和
 划分分两种情况：
 划分中每个数都小于m：则划分数为dp[n][m-1]。
 划分中至少有一个数等于m：则从n中减去去m，然后从n-m中再划分，则划分数为dp[n-m][m]。
 动态转移方程：dp[n][m]=dp[n][m-1]+dp[n-m][m]。


 2、N划分成若干个不同正整数之和
 设dp[n][m]表示数n划分方案中，每个数 不大于m 的划分数
 划分分两种情况：
 划分中每个数都小于m：则划分数为dp[n][m-1]。
 划分中至少有一个数等于m：则从n中减去m，然后从n-m中再划分，且再划分的数中每个数要小于m, 则划分数为dp[n-m][m-1]。
 动态转移方程：dp[n][m]=dp[n][m-1]+dp[n-m][m-1]。

 3、N划分成K个正整数之和
 设dp[n][k]表示数n划分成k个正整数之和时的划分数。
 划分分两种情况：
 划分中不包含1：则要求每个数都大于1，可以先拿出k个1分到每一份，之后在n-k中再划分k份，即dp[n-k][k]。
 划分中包含1：则从n中减去1，然后从n-1中再划分k-1份, 则划分数为dp[n-1][k-1]。
 动态转移方程：dp[n][k]=dp[n-k][k]+dp[n-1][k-1]。

 4、N划分成若干个奇正整数之和
 设f[i][j]表示将数i分成j个正奇数，g[i][j]表示将数i分成j个正偶数。
 首先如果先给j个划分每个分个1，因为奇数加1即为偶数，所以可得：
 f[i-j][j] = g[i][j]。
 划分分两种情况：
 划分中不包含1：则要求每个数都大于1，可以先拿出k个1分到每一份，刚可将问题转换为”从i-j中划分j个偶数”，即g[i-j][j]。
 划分中包含1：则从n中减去1，然后从n-1中再划分k-1份, 则划分数为dp[n-1][k-1]。
 动态转移方程：f[i][j]=f[i-1][j-1]+g[i-j][j]。
 */
#include <iostream>
#include <cstring>
using namespace std;
#define N 51
int dp1[N][N];    //N划分成K个正整数之和的划分数目。
int dp2[N][N];    //N划分成若干个不同正整数之和的划分数目。
int dp3[N][N];    //N划分成若干个可相同的正整数之和的划分数目。
int f[N][N];      //N划分成K个奇正整数之和的划分数目。
int g[N][N];      //N划分成K个偶正整数之和的划分数目。

void initDivideInt() {
    memset(dp1, 0, sizeof(dp1));  //dp[n][k]=dp[n-k][k]+dp[n-1][k-1]
    memset(dp2, 0, sizeof(dp2));  //dp[n][m]=dp[n][m-1]+dp[n-m][m-1]
    memset(dp3, 0, sizeof(dp3));  //dp[n][m]=dp[n][m-1]+dp[n-m][m]
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < N; j++) {
            if (i < j) {
                dp1[i][j] = 0;
                dp2[i][j] = dp2[i][i];
                dp3[i][j] = dp3[i][i];
            }
            else if (i == j) {
                dp1[i][j] = 1;
                dp2[i][j] = dp2[i][j - 1] + 1;
                dp3[i][j] = dp3[i][j - 1] + 1;
            }
            else {
                dp1[i][j] = dp1[i - j][j] + dp1[i - 1][j - 1];
                dp2[i][j] = dp2[i][j - 1] + dp2[i - j][j - 1];
                dp3[i][j] = dp3[i][j - 1] + dp3[i - j][j];
            }
        }
    }
}

//f[i][j]=f[i-1][j-1]+g[i-j][j]
void initDivideOdd() {
    f[0][0] = 1;
    g[0][0] = 1;
    for (int i = 1; i < N; i++) {
        for (int j = 1; j <= i; j++) {
            g[i][j] = f[i - j][j];
            f[i][j] = f[i - 1][j - 1] + g[i - j][j];
        }
    }
}

int main(int argc, const char * argv[]) {
    int n=5, k=2;
    initDivideInt();
    initDivideOdd();

    cout << dp3[n][n] << endl;
    cout << dp1[n][k] << endl;
    cout << dp2[n][n] << endl;

    int sum = 0;
    for (int i = 0; i <= n; i++) {
        sum += f[n][i];
    }
    cout << sum << endl;
    return 0;
    return 0;
}
