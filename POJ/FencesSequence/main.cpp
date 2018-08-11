//
//  main.cpp
//  FencesSequence
//
//  Created by cmm on 2018/8/11.
//  Copyright © 2018年 bingyan. All rights reserved.
//  动态规划之美丽栅栏问题
//
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int UP = 0;
const int DOWN = 1;
const int MAXN = 21;
long long C[MAXN][MAXN][2];
// C[i][k][UP] 表示的是 i个木棒中以长度为k的木棒开头且第二个木棒比k长的栅栏排列数。

void initFences(int n) {
    memset(C, 0, sizeof(C));
    C[1][1][UP] = C[1][1][DOWN] = 1;
    for(int i=2; i<=n; i++){
        for(int k=1;k<=n;k++){
            for(int M=k;M<=i-1;M++){
                C[i][k][UP] +=C[i-1][M][DOWN];
            }
            for(int N=1;N<=k-1;N++){
                C[i][k][DOWN] +=C[i-1][N][UP];
            }
        }
    }
}

void sortSequence(int n, long long cc){
    long long skipped = 0;
    int seq[MAXN];
    int used[MAXN];
    memset(used, 0, sizeof(used));
    for(int i=1; i<=n; i++){ // i 表示木棒的位置
        int No = 0;
        for(int k=1; k<=i; k++){ // k 表示位置i的木棒长度
            skipped = 0;
            if(!used[k]) {
                No++;
                if(i==1){
                    skipped = C[n][No][UP] + C[n][No][DOWN];
                } else {
                    if(k>seq[i-1] && (i<=2 || seq[i-2] > seq[i-1]))
                        skipped = C[n-i+1][No][DOWN];
                    else if(k<seq[i-1] && (i<=2 || seq[i-2] < seq[i-1]))
                        skipped = C[n-i+1][No][UP];
                }

                if(skipped >= cc){
                    used[k] = true;
                    seq[i] = k;
                    break;
                } else {
                    cout<<"h";
                    cc -= skipped;
                }
            }
        }
    }
    for(int i=1; i<=n; i++)
        cout<<seq[i];
    cout<<endl;
}

void solve(int n, long long cc)
{
    long long skipped = 0;
    int a[MAXN];
    int used[MAXN];
    memset(used, 0, sizeof(used));
    for (int i = 1; i <= n; i++) { //确定位置i该放什么长度的木棒
        int k = 0;
        for (int j = 1; j <= n; j++) {
            skipped = 0;
            if (!used[j]) { //是第k短的木棒
                k++;
                if (i == 1) { //位置1无法用前一项判断升降趋势，直接算总和。
                    skipped = C[n][k][UP] + C[n][k][DOWN];
                }
                else {
                    //找下降趋势木棒a形状只能是/\(i>2)或\(i=2)，只找到i-1根木棒，所以a集合的中还有n-i+1根木棒。
                    if (a[i - 1] < j && (i <= 2 || a[i - 2] > a[i - 1])) {
                        skipped = C[n - i + 1][k][DOWN];
                    }
                    //找上升趋势方案数
                    else if (a[i - 1] > j && (i <= 2 || a[i - 2] < a[i - 1])) {
                        skipped = C[n - i + 1][k][UP];
                    }
                }
                if (skipped >= cc) {
                    used[j] = true;
                    a[i] = j;
                    break;
                }
                else {
                    cc -= skipped;
                }
            }
        }
    }
    for(int i=1; i<=n; i++)
        cout<<a[i];
    cout<<endl;
}

int main(int argc, const char * argv[]) {
    int times, n;
    long long number;
    cin>>times;
    while(times--){
        cin>>n>>number;
        initFences(n);
        sortSequence(n, number);
    }
    return 0;
}
