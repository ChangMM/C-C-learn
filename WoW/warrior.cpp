//
//  warrior.cpp
//  WoW
//
//  Created by cmm on 2018/7/9.
//  Copyright © 2018年 bingyan. All rights reserved.
//  Warrior类 及其派生类
//
#include <iostream>
#include<iomanip>
using namespace std;
extern class Warrior;
extern class Dragon;
extern class Ninja;
extern class Lion;
extern class Wolf;
extern class Iceman;

static string* weaponNames = new string[3]{"sword", "bomb", "arrow"}; // 这个初始化赋值的方法可以再看下

class Warrior{
    int id;
    int lifeValue;
public:
    Warrior():id(0), lifeValue(0){}
    
    Warrior(int theId, int theLifeValue):id(theId), lifeValue(theLifeValue) {
    }
    
    int getId() {
        return id;
    }
    
};

class Dragon:public Warrior{
    float morale;
public:
    Dragon(int id, int lifeValue, int warriorAllLifeValue):Warrior(id, lifeValue){
        morale = (float)(warriorAllLifeValue) / lifeValue;
    }
    float getMorale() {
        return morale;
    }
    string getWeapons(){
        int index = this->getId() % 3;
        return weaponNames[index];
    }
    
    void printInfo() {
        cout<<"It has a "<< getWeapons() <<",and it's morale is "<< setprecision(2) << fixed << getMorale() <<endl;
    }
};

class Ninja:public Warrior{
public:
    Ninja(int theId, int theLifeValue):Warrior(theId, theLifeValue) {}
    string* getWeapons() {
        string * temp = new string[2];
        int index1 = getId() % 3, index2 = (getId() + 1) % 3;
        *temp = weaponNames[index1], *(temp + 1) = weaponNames[index2];
        return temp;
    }
    void printInfo() {
        cout<<"It has a "<< *getWeapons() <<" and a "<< *(getWeapons() + 1) <<endl;
    }
};

class Iceman:public Warrior {
public:
    Iceman(int theId, int theLifeValue):Warrior(theId, theLifeValue) {}
    string getWeapons() {
        int index = this->getId() % 3;
    return weaponNames[index];
     }
    void printInfo() {
        cout<<"It has a "<<getWeapons()<<endl;
    }
};

class Lion:public Warrior {
private:
    int loyalty;
public:
    Lion(int theId, int theLifeValue, int headquarterLifeValue):Warrior(theId, theLifeValue) {
        loyalty = headquarterLifeValue;}
    int getLoyalty() {
        return loyalty;
    }
    void printInfo() {
        cout<<"It's loyalty is "<<getLoyalty()<<endl;
    }
};
class Wolf:public Warrior {
public:
    Wolf(int theId, int theLifeValue):Warrior(theId, theLifeValue) {}
};
