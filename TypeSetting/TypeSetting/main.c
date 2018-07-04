//
//  main.c
//  TypeSetting
//
//  Created by cmm on 2018/7/4.
//  Copyright © 2018年 bingyan. All rights reserved.
//  文字排版
//

#include <stdio.h>
#include <string.h>

int main(int argc, const char * argv[]) {
    int wordLen = 0, totalNum = 0, MAX = 80;
    char word[41] = {0};
    scanf("%d", &wordLen);
    
    for (int i = 0; i < wordLen; i++) {
        scanf("%s",word);
        if (strlen(word) + totalNum + 1> MAX){
            printf("\n");
            totalNum = 0;
        } else if (i > 0) {
            printf(" ");
            totalNum++;
        }
        printf("%s", word);
        totalNum = totalNum + strlen(word);
    }
    return 0;
}
