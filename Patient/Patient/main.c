//
//  main.c
//  Patient
//
//  Created by cmm on 2018/7/4.
//  Copyright © 2018年 bingyan. All rights reserved.
//  分配病房
//

#include <stdio.h>
struct patient {
    int num;
    float score;
};

int main(int argc, const char * argv[]) {
    int num, isPrint = 0;
    float flag;
    struct patient Patients[51];
    scanf("%d %f", &num, &flag);
    
    for (int i = 0; i < num; i++) {
        scanf("%d %f", &Patients[i].num, &Patients[i].score);
    }
    for (int i = 0; i < num; i++) {
        for (int j = i + 1; j < num; j++) {
            struct patient temp;
            if (Patients[i].score < Patients[j].score) {
                temp = Patients[i];
                Patients[i] = Patients[j];
                Patients[j] = temp;
            }
        }
    }
    for (int i = 0; i < num; i++){
        if (Patients[i].score > flag) {
            isPrint = 1;
            printf("%03d %.1f\n", Patients[i].num, Patients[i].score);
        }
    }
    if (!isPrint){
        printf("None.");
    }
    return 0;
}
