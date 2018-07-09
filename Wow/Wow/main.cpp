//
//  main.cpp
//  WoW
//
//  Created by cmm on 2018/7/5.
//  Copyright © 2018年 bingyan. All rights reserved.
//

#include <iostream>
#include<iomanip>
#include <string>
#include "warrior.cpp"
using namespace std;

// define headquarter
class Headquarter {
    string headquarterName;
    string warriorNames[5];
    int warriorAllLifeValue;
    int warriorLifeValues[5];
    int minWarriorLifeValue;
    int warriorNum[5];
    int currentPos;
    int warriorTotalNum;
    
public:
    bool isStop;
    static int time;
    
    Headquarter(string theheadquarterName, int theallLifeValue, const string thepriorallWarriorName[],
                const int thewarriorValue[], const int thewarriorOrder[]);
    void produceWarrior(int time, int position);
    void dispatchWarrior();
};

// 静态变量一定要单独在全局环境下声明
int Headquarter::time = 0;

Headquarter::Headquarter(string theheadquarterName, int theallLifeValue, const string thepriorallWarriorName[],
            const int thewarriorValue[], const int thewarriorOrder[]) {
    headquarterName = theheadquarterName;
    warriorAllLifeValue = theallLifeValue;
    warriorTotalNum = 0;
    currentPos = 0;
    isStop = false;
    
    for (int i = 0; i < 5; i++){
        warriorNum[i] = 0;
        warriorNames[i] = thepriorallWarriorName[thewarriorOrder[i]];
        warriorLifeValues[i] = thewarriorValue[thewarriorOrder[i]];
    }
    
    minWarriorLifeValue = warriorLifeValues[0];
    for (int i = 1; i < 5; i++){
        if (warriorLifeValues[i] < minWarriorLifeValue)
            minWarriorLifeValue = warriorLifeValues[i];
    }
}

void Headquarter::produceWarrior(int time, int position) {
    warriorTotalNum ++;
    warriorNum[position]++;
    cout << setfill('0')<< setw(3) << time << " " << headquarterName << " " << warriorNames[position]
    << ' ' << warriorTotalNum << " born with strength " << warriorLifeValues[position] << "," << warriorNum[position]
    << ' ' << warriorNames[position] << " in " << headquarterName << " headquarter" << endl;
    warriorAllLifeValue -= warriorLifeValues[position];
    string warriorName = warriorNames[position];
    int lifeValue = warriorLifeValues[position];
    if (warriorName == "dragon") {
        Dragon solider(warriorTotalNum, lifeValue, warriorAllLifeValue);
        solider.printInfo();
    } else if (warriorName == "ninja") {
        Ninja solider(warriorTotalNum, lifeValue);
        solider.printInfo();
    } else if (warriorName == "lion") {
        Lion solider(warriorTotalNum, lifeValue, warriorAllLifeValue);
        solider.printInfo();
    } else if (warriorName == "iceman") {
        Iceman solider(warriorTotalNum, lifeValue);
        solider.printInfo();
    } else if (warriorName == "wolf") {
//        todo
    }
}

void Headquarter::dispatchWarrior(){
    if (warriorAllLifeValue < minWarriorLifeValue){
        cout << setfill('0') << setw(3) << time << " " << headquarterName << " headquarter stops making warriors" << endl;
        isStop = true;
    } else {
        while(true) {
            if(warriorAllLifeValue >= warriorLifeValues[currentPos]) {
                produceWarrior(time, currentPos);
                currentPos == 4 ? currentPos = 0 : currentPos++;
                break;
            } else {
                currentPos == 4 ? currentPos = 0 : currentPos++;
            }
        }
    }
}


int main(int argc, const char * argv[]) {
    int loops = 0, allLifeValue = 0;
    string priorallWarriorNames[5] = { "dragon", "ninja", "iceman", "lion", "wolf" };
    int warriorValues[5] = { 0 };
    const int redWarriorOrder[5] = { 2, 3, 4, 1, 0 };
    const int blueWarriorOrder[5] = { 3, 0, 1, 2, 4 };
    
    cin>>loops; //总共的回合数
    for (int i = 1; i<=loops; i++){
        cin >> allLifeValue;
        
        for (int j = 0; j < 5; j++) //输入不同种的武士的生命值
            cin >> warriorValues[j];
        
        cout << "Case:" << i << endl;
        
        Headquarter::time = 0; // 次数清零
        Headquarter redQuarter("red", allLifeValue, priorallWarriorNames, warriorValues, redWarriorOrder);
        Headquarter blueQuarter("blue", allLifeValue, priorallWarriorNames, warriorValues, blueWarriorOrder);
        
        while(!redQuarter.isStop || !blueQuarter.isStop) {
            if (!redQuarter.isStop) {
                redQuarter.dispatchWarrior();
            }
            if (!blueQuarter.isStop){
                blueQuarter.dispatchWarrior();
            }
            Headquarter::time++;
        }
    }
    return 0;
}
