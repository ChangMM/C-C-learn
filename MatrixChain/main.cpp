//
//  main.cpp
//  MatrixChain
//
//  Created by cmm on 2018/8/13.
//  Copyright © 2018年 bingyan. All rights reserved.
//
//

#include<iostream>
using namespace std;

#define maxvalue 1000000

void matrix_chain_order(int p[],int len,int **m,int **s)
{
    int n=len-1;
        //A[i][i]只有一个矩阵，所以相乘次数为0，即m[i][i]=0;
    for(int i=1;i<=n;i++)
        {
        m[i][i]=0;
        }
    for(int L=2;L<=n;L++)//l为chain length
        {
        for(int i=1;i<=n-L+1;i++) ///从第一矩阵开始算起，计算长度为L的最少代价,不是从0
            {
            int j=i+L-1;
            m[i][j]=maxvalue;
            for(int k=i;k<j;k++)
                {
                int q=m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
                if(q<m[i][j])
                    {
                    m[i][j]=q;
                    s[i][j]=k;
                    }
                }
            }
        }
}

void print_optimal_parents(int **s,int i,int j)
{
    if(i==j)
        {
        cout<<"A"<<i;
        }
    else
        {
        cout<<"(";
        print_optimal_parents(s,i,s[i][j]);
        print_optimal_parents(s,s[i][j]+1,j);
        cout<<")";
        }
}


int main()
{
    /*
     现有矩阵A1(30×35)、A2(35×15)、A3(15×5)、A4(5×10)、A5(10×20)、A6(20×25)，得到p=<30,35,15,5,10,20,25>
     */
    int p[]={30,35,15,5,10,20,25};
    int len=sizeof(p)/sizeof(int);
    int **m,**s;
    m=new int*[len];
    s=new int*[len];
    for(int i=1;i<len;i++){
        m[i]=new int[len];
        s[i]=new int[len];
    }
    for(int i=1;i<len;i++){
        for(int j=1;j<len;j++){
            m[i][j]=0;
            s[i][j]=0;
        }
    }
    matrix_chain_order(p,len,m,s);
    print_optimal_parents(s,1,6);
}
