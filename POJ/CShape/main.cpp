//
//  main.cpp
//  CShape
//
//  Created by cmm on 2018/7/6.
//  Copyright © 2018年 bingyan. All rights reserved.
//  多态的应用 按面积大小输出
//

#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

class Shape {
public:
    virtual double area() = 0;
    virtual void printInfo() = 0;
};

class Circle:public Shape {
public:
    int r;
    virtual double area();
    virtual void printInfo();
};

class Rectangle:public Shape {
public:
    int w;
    int h;
    virtual double area();
    virtual void printInfo();
};

class Triangle:public Shape {
public:
    int a,b,c;
    virtual double area();
    virtual void printInfo();
};

double Circle::area(){
    double s = 3.14*this->r*this->r;
    return s;
};
void Circle::printInfo(){
    cout<<"Circle area:"<<this->area()<<endl;
};

double Rectangle::area(){
    double s = this->w * this->h;
    return s;
};
void Rectangle::printInfo(){
    cout<<"Rectangle area:"<<this->area()<<endl;
};

double Triangle::area(){
    double p = (this->a+this->b+this->c)/2;
    double s = sqrt(p*(p - this->a)*(p-this->b)*(p-this->c));
    return s;
};

void Triangle::printInfo(){
    cout<<"Triangle area:"<<this->area()<<endl;
};

Shape* shapeArray[5];
int compare(const void*a, const void*b){
    // 这一部分太绕了需要多看下
    Shape** p = (Shape**)a;
    Shape** q = (Shape**)b;
    if ((*p)->area() < (*q)->area()){
        return -1;
    } else {
        return 1;
    }
};

int main(int argc, const char * argv[]) {
    Rectangle * p1;
    Triangle * p2;
    Circle * p3;
    for (int i= 0; i<3;i++){
        char c;
        cin>>c;
        switch (c) {
            case 'R':
                p1 = new Rectangle();
                cin>>p1->w>>p1->h;
                shapeArray[i] = p1;
                break;
            case 'T':
                p2 = new Triangle();
                cin>>p2->a>>p2->b>>p2->c;
                shapeArray[i] = p2;
                break;
            case 'C':
                p3 = new Circle();
                cin>>p3->r;
                shapeArray[i] = p3;
                break;
            default:
                break;
        }
    }
    qsort(shapeArray, 3, sizeof(Shape*), compare);
    
    for(int i = 0;i<3;i++){
        shapeArray[i]->printInfo();
    }
    return 0;
}
