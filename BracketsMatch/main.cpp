//
//  main.cpp
//  BracketsMatch
//
//  Created by cmm on 2018/8/17.
//  Copyright © 2018年 bingyan. All rights reserved.
//  栈解决括号匹配问题
//

#include <iostream>
#include <stack>
#include <string>
using namespace std;

struct Node{
    char bracket;
    int index;
};
stack<Node> brackets;
string str;

void result(string str, int i) {
    char s = str[i];
    Node node;
    if (s == '('){
        node.bracket = '(';
        node.index = i;
        brackets.push(node);
    } else if (s ==')'){
        if (!brackets.empty() && brackets.top().bracket == '('){
            brackets.pop();
        } else {
            node.bracket = ')';
            node.index = i;
            brackets.push(node);
        }
    } else if (s == '\0'){
        return;
    }
    result(str, ++i);
}

int main(int argc, const char * argv[]) {
    cin>>str;
    result(str, 0);
    cout<<str<<endl;
    Node node;
    for(int len = int(str.length()); len>=0; len--){
        if(brackets.empty()){
            str[len] = ' ';
        } else {
            node = brackets.top();
            if (len == node.index) {
                if (node.bracket == '(') {
                    str[len] = '$';
                } else {
                    str[len] = '?';
                }
                brackets.pop();
            } else {
                str[len] = ' ';
            }
        }
    }
    cout<<str<<endl;
    return 0;
}
