//
//  main.cpp
//  CopyingBooks
//
//  Created by cmm on 2018/8/31.
//  Copyright © 2018年 bingyan. All rights reserved.
//  二分加贪心 解决誊抄书籍的问题  poj 1505
//

#include <iostream>
using namespace std;

#define MAXM (500+10)
int N, m, k; // N组数据， m本书， k个抄写员
int a[MAXM]; //每本书的页数

bool check(long long ans){
    int s = 0;
    long long now = 0;

    //从后向前判断每本书, 若可以就放入当前堆
    for (int i = m-1;i >= 0;--i) {
        if (now + a[i] > ans) {
            ++s;
            now = a[i];
        }else{
            now += a[i];
        }
    }
    if (now > 0) ++s;
    //判断最后的总堆数是否小于等于k
    if (s > k)
        return false;
    else
        return true;
}

//用递归的方式输出最后的结果
//当前处理到第book本书, 第scriber堆, 当前堆的页数为now, 每堆页数不能超过ans
void print( int book, long long ans, int scriber, long long now){
    bool sepa = false;
    if (book < 0)
        return ;
    //若当前书不能放入当前堆, 则说明要加入分隔符
    if (book == scriber-1 || now+a[book] > ans) {
        print( book-1, ans, scriber-1, a[book]);
        sepa = true;
    } else print(book-1, ans, scriber, now + a[book]);
    //输出当前书的页数和分隔符
    if (book > 0)
        cout<<" "<<a[book];
    else
        cout<<a[book];
    if (sepa)
        cout<<" /";
}

int main(int argc, const char * argv[]) {
    long long l, r, mid;
    cin>>N;
    for (int i = 0;i < N; ++i) {
        l = 0; r = 0;
        cin>>m>>k;
        for (int j=0; j<m; ++j){
            cin>>a[j];
            r += a[j];
            if (a[j] > l) l = a[j];
        }
        //二分查找, 判断最大堆的页数小于等于mid是否可行
        while (l <= r){
            mid = (l+r)/2;
            if (check(mid)) r = mid - 1;
            else l = mid + 1;
        }
            //递归输出最后结果
        print(m-1, l, k-1, 0);
        cout<<endl;
    }
    return 0;
}
