//
//  main.cpp
//  Shredding
//
//  Created by cmm on 2018/8/29.
//  Copyright © 2018年 bingyan. All rights reserved.
//  暴利深度优先搜索解决碎纸问题 http://bailian.openjudge.cn/practice/1416/
//

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
using namespace std;

int aim;  //目标数
int result;  //最优划分的和
int sum;   //某种划分的和
short visit[1000000];  //记录每个sum出现的次数
int path;
int bestPath;


//得到数字字符串s start 后 num 位的值
int getValue(char* s,short start, short num){
    int k = 0;
    int sum = 0;
    while(num){
        num--;
        sum +=(s[start + num] - '0') * pow(10, k);
        k++;
    }
    return sum;
}

// 获取字符串的最小value也即各位的数字之和
int getMinValue(char*s, short len){
    int min = 0;
    while(len){
        len--;
        min += (s[len]-'0');
    }
    return min;
}

void DFS(char*s, short start, short num){
    if (num == 0){
        visit[sum]++;
        if(sum>result && sum<=aim){
            result=sum;
            bestPath = path;
        }
        return;
    }

    for(int i = 1;i<=num; i++){
        int a = getValue(s, start, i);
        sum += a;  //部分和
        if(sum>aim) { //剪枝，部分和已经大于aim，无需继续往下搜索
            sum -= a;
            continue;
        }

        path = path*10+i;
        start += i;
        num -= i;

        DFS(s, start, num);

        // 回溯
        start -= i;
        num += i;
        sum -= a;
        path /=10;
    }
    return;
}

void printPath(char*s, int path){
    string str = to_string(path);
    string s_str = string(s);
    short temp = 0;
    for(short i=0; i< str.length(); i++){
        cout<<s_str.substr(temp, (str[i]-'0'))<<" ";
        temp += (str[i]-'0');
    }
    cout<<endl;
}

int main(int argc, const char * argv[]) {
    while(true){
        char s[7];  //打印纸上的数字
        cin>>aim>>s;

        short len=strlen(s), minValue = getMinValue(s, len);
        int maxValue = getValue(s, 0, len);

        if(!aim && !maxValue)
            break;

        //目标值与打印纸上的数字一致
        if(aim==maxValue){
            cout<<aim<<' '<<maxValue<<endl;
            continue;
        }

        if(minValue > aim) {
            cout<<"error"<<endl;
            continue;
        }

        memset(visit, 0 ,sizeof(visit));
        result = -1;
        sum = 0;
        path = 0;
        bestPath = 0;

        DFS(s, 0, len);

        if(visit[result] > 1)
            cout<<"rejected"<<endl;
        else if(visit[result]==1){
            cout<<result<<" ";
            printPath(s, bestPath);

        }
    }
    return 0;
}
