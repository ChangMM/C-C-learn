//
//  main.cpp
//  BigInt
//
//  Created by cmm on 2018/7/8.
//  Copyright © 2018年 bingyan. All rights reserved.
//  大整数的加减乘除(目前只支持正整数)
//

#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;
class BigInt{
private:
    void formatWithChar(string& str1, string& str2, char c) {
        int size1 = str1.size(), size2 = str2.size();
        for (int i = 0; i < abs(size1 - size2); i++){
            if (size1 > size2) {
                str2 = c + str2;
            } else {
                str1 = c + str1;
            }
        }
    }
    
    int compare(string s1, string s2)
    {
        if(s1.size() < s2.size())
            return -1;
        else if(s1.size() > s2.size())
            return 1;
        else
            return s1.compare(s2);
    }
    
public:
    string values;
    bool flag;
    BigInt();
    BigInt(string str);
    BigInt(BigInt& bigint);
    BigInt(string v,bool f);
    // 重载一系列运算符
    BigInt operator+(const BigInt& rhs);
    BigInt operator-(const BigInt& rhs);
    BigInt operator*(const BigInt& rhs);
    BigInt operator/(const BigInt& rhs);
    friend ostream& operator<< (ostream& o, BigInt& rhs);
    friend istream& operator>> (istream& o, BigInt& rhs);
};

BigInt::BigInt():values("0"),flag(true){}
BigInt::BigInt(string str, bool f) {
    values = str;
    flag = true;
}
BigInt::BigInt(string str) {
    values = str;
    flag = true;
}
BigInt::BigInt(BigInt& bigint) {
    values = bigint.values;
    flag = bigint.flag;
}

BigInt BigInt::operator+(const BigInt &rhs) {
    BigInt ret;
    ret.flag = true;
    string Lvalues = values, Rvalues = rhs.values;
    if (Lvalues == "0") {
        ret.values = Rvalues;
        return ret;
    }
    if (Rvalues == "0") {
        ret.values = Lvalues;
        return ret;
    }
    
    formatWithChar(Lvalues, Rvalues, '0');
    
    // 开始处理
    string res = ""; // 储存最后结果
    int n = 0, m = 0; //n保留进位信息, m保留相加的结果
    int len = Lvalues.size();
    for (int i = len-1; i>=0; i--){
        m = Lvalues[i] - '0' + Rvalues[i] - '0' + n; // 4 = '4' - '0'
        n = m/10;
        res = char(m%10 + '0') + res;
    }
    
    if (n == 1) {
        res = "1" + res;
    }
    
    ret.values = res;
    return ret;
}

BigInt BigInt::operator-(const BigInt &rhs) {
    BigInt ret;
    string Lvalues = values, Rvalues = rhs.values;
    if (Lvalues == "0") {
        ret.values = Rvalues;
        ret.flag = false;
        return ret;
    }
    if (Rvalues == "0") {
        ret.values = Lvalues;
        ret.flag = true;
        return ret;
    }
    
    formatWithChar(Lvalues, Rvalues, '0');
    
    //确定符号 以及左值永远大于右值
    int t = compare(Lvalues, Rvalues);
    if (t < 0){
        ret.flag = false;
        string temp;
        temp = Lvalues;
        Lvalues = Rvalues;
        Rvalues = temp;
    } else if (t > 0){
        ret.flag = true;
    } else {
        ret.values = "0";
        ret.flag = true;
        return ret;
    }
    
    // 开始处理
    string res = "";
    int n = 0, m = 0; //n保留借位信息, m保留相减的结果

    int len = Lvalues.size();
    for (int i = len-1; i>=0; i--){
        m = Lvalues[i] - Rvalues[i] + n;
        if (m < 0) {
            m = m + 10;
            n = -1;
        } else {
            n = 0;
        }
        res = char(m + '0') + res;
    }
    
    ret.values = res.erase(0, res.find_first_not_of('0'));
    return ret;
}

// 相乘
BigInt BigInt::operator*(const BigInt &rhs) {
    BigInt ret, tempRet;
    ret.flag = true;
    string Lvalues = values, Rvalues = rhs.values;
    if (Lvalues == "0" || Rvalues == "0") {
        ret.values = "0";
        return ret;
    }
    
    int Lsize = Lvalues.size(), Rsize = Rvalues.size();
    if (Rsize > Lsize) {
        string temp;
        temp = Lvalues;
        Lvalues = Rvalues;
        Rvalues = temp;
        Lsize = Lvalues.size();
        Rsize = Rvalues.size();
    }
    
    // 开始处理
    string res = "" ,tempStr = ""; // 储存最后结果
    int n = 0, m = 0; //n保留进位信息, m保留相乘的结果
    
    for (int i = Rsize-1; i>=0; i--){
        for(int j = Lsize-1; j >=0; j--) {
            m = (Lvalues[j] - '0')*(Rvalues[i] - '0') + n; // 4 = '4' - '0'
            n = m/10;
            tempStr = char(m%10 + '0') + tempStr;
        }
        if (n > 0) {
           tempStr = char(n + '0') + tempStr;
        }
        for (int k = 0; k < Rsize-1 - i; k++) {
            tempStr = tempStr + '0';
        }
        tempRet = tempStr;
        ret = tempRet + ret;
        tempStr = ""; //需要清空下
        n = 0;
    }
    
    return ret;
}

BigInt BigInt::operator/(const BigInt &rhs) {
    BigInt ret;
    string lvalues(values), rvalues(rhs.values);
    //处理特殊情况
    if(rvalues == "0"){
        ret.values = "error";//输出错误
        ret.flag = true;
        return ret;
    }
    
    if(lvalues == "0"){
        ret.values = "0";
        ret.flag = true;
        return ret;
    }
    
    string quotient;
    if(compare(lvalues, rvalues) < 0){
        ret.values = "0";
        ret.flag = true;
        return ret;
    } else if(compare(lvalues, rvalues) == 0) {
        ret.values = "1";
        ret.flag = true;
        return ret;
    } else {
        string temp;
        BigInt s, t;
        int lsize = lvalues.size(), rsize = rvalues.size();
        temp.append(lvalues, 0, rsize);
        for (int i = rsize; i <= lsize; i++){
            for(char c = '9'; c >= '0'; c--) {
                t = BigInt(rvalues) * BigInt(string(1, c));
                s = (BigInt)temp - t;
                
                if(s.flag == true)
                {
                    temp = s.values;
                    quotient = quotient + c;
                    break;
                }
            }
            temp = temp + lvalues[i];
        }
    }
    //去除前导零
    quotient.erase(0, quotient.find_first_not_of('0'));
    ret.values = quotient;
    return ret;
}

ostream& operator<< (ostream& o, BigInt& rhs){
    if (!rhs.flag) {
        o<< "-";
    }
    o << rhs.values;
    return o;
}

istream& operator>> (istream& i, BigInt& rhs){
    string str;
    i>>str;
    rhs.flag = true;
    rhs.values = str;
    return i;
}

int main(int argc, const char * argv[]) {
    BigInt a, b, result;
    char op;
    cin >> a >> op >> b;
    switch(op)
    {
        case '+':result = a + b; break;
        case '-':result = a - b; break;
        case '*':result = a * b; break;
        case '/':result = a / b; break;
        default:break;
    }
    cout << result << endl;
    return 0;
    
    return 0;
}
