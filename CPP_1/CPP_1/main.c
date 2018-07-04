//
//  main.c
//  CPP_1
//
//  Created by cmm on 2018/7/3.
//  Copyright © 2018年 bingyan. All rights reserved.
//
//
/*
 1:求字母的个数
 查看 提交 统计 提问
 总时间限制: 1000ms 内存限制: 65536kB
 描述
 在一个字符串中找出元音字母a,e,i,o,u出现的次数。
 输入
 输入一行字符串（字符串中可能有空格，请用gets(s)方法把一行字符串输入到字符数组s中），字符串长度小于80个字符。
 输出
 输出一行，依次输出a,e,i,o,u在输入字符串中出现的次数，整数之间用空格分隔。
 */

#include <stdio.h>
#include <string.h>

int main(int argc, const char * argv[]) {
    char str[80];
    int a_len = 0, e_len = 0, i_len = 0, o_len = 0, u_len = 0;
    fgets(str, 80, stdin);
    unsigned long str_len = strlen(str);
    for (int i = 0; i < str_len; i++) {
        switch (str[i]) {
            case 'a':
                a_len++;
                break;
                
            case 'e':
                e_len++;
                break;
                
            case 'i':
                i_len++;
                break;
                
            case 'o':
                o_len++;
                break;
                
            case 'u':
                u_len++;
                break;
                
            default:
                break;
        }
    }
    printf("%d %d %d %d %d \n", a_len, e_len, i_len, o_len, u_len);
    return 0;
}
