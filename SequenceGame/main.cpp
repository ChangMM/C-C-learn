//
//  main.cpp
//  SequenceGame
//
//  Created by cmm on 2018/8/16.
//  Copyright © 2018年 bingyan. All rights reserved.
//  递归 排队游戏 http://pkuic.openjudge.cn/hw07/3
//


#include <iostream>
#include <stack>
using namespace std;
char man;
stack<int> stk; //男生栈
stack<int> stk1; // 女生栈

// 队列方法解决
void result(char str[], int s)
{
    if(str[s] == '\0') {
        return;
    } else if (str[s] != man){
        if(stk.empty()){
            stk1.push(s);
        } else {
            cout<<stk.top()<<" "<<s<<endl;
            stk.pop();
        }
        result(str, ++s);
    } else {
        if(stk1.empty()){
            stk.push(s);
        } else {
            cout<<s<<" "<<stk1.top()<<endl;
            stk1.pop();
        }
        result(str, ++s);
    }
}

int main(){
    char str[101] = { 0 };
    cin >> str;
    man = str[0];
    result(str, 0);
    return 0;
}

//非队列方法
//#include <iostream>
//using namespace std;
//char man;
//int founction(char str[], int s)
//{
//    int n;
//    if (str[s] != man){
//        return s;
//    } else {
//        n = founction(str, s + 1);
//        cout << s << ' ' << n << endl;
//        return founction(str, n + 1);
//   }
//}
//int main(){
//    char str[101] = { 0 };
//    cin >> str;
//    man = str[0];
//    int n = founction(str, 1);
//    cout << "0 " << n << endl;
//    return 0;
//}

