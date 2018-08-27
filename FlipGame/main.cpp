//
//  main.cpp
//  FlipGame
//
//  Created by cmm on 2018/8/28.
//  Copyright © 2018年 bingyan. All rights reserved.
//  翻转棋盘游戏，输出最小翻转的步数，并打印出翻转的路径， http://cxsjsxmooc.openjudge.cn/test2/G/
//  利用广度搜索 加 状态压缩结题
//


/*
 简单分析：根据输入要求，b代表黑棋(black)，w代表白棋(white)。因为总共才16个位置，且只有黑白两种表示，此时，可对每一次状态进行二进制压缩(其中b代表1,w代表0)，例如：
 bwwb
 bbwb
 bwwb
 bwww
 即可表示为1001 1101 1001 1000，其十进制值为40344。同时，计算可知根据黑白棋的摆放情况，总共有2^16种不同的状态。每一次经过有效的操作后，状态都会发生改变，此时，可借助二进制位运运算实现状态的改变，即对原有状态(相应的十进制表示)进行异或操作，以此来改变其对应二进制数的相关位置的值(1变0，0变1)。
 例如：
 先假设前一个状态为：
 wwww
 wwww
 wwww
 wwww
 即二进制表示为0000 0000 0000 0000，十进制对应为0。若此时选定左上角第一个棋子进行操作，根据规则，它右边和下边的也要同时进行变换(因为其左边和上边为空，不做考虑)，之后，相应的状态用二进制表示，应变为：1100 1000 0000 0000，十进制值为51200。这个过程相当于对十进制数51200进行对十进制数0的异或操作，即next=0^(51200)，而51200这个数则可以根据对十进制数1进行相应的左移操作得到。同时，我们知道，棋牌总共有16个位置，也就是说相应的不同的操作也有16种，即有16个不同的数经过异或操作用来改变前一个状态的值。
 */
#include <iostream>
#include <queue>
#include <string>
#include <memory.h>
using namespace std;


short dir[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
unsigned short change[4][4];
unsigned short initState = 0;  // 初始棋盘的状态
bool visited[65536];
struct Node{
    unsigned short state;
    unsigned short step;
};

struct Flag{
    unsigned short moveState;  // 保存到这一步的转换动作
    unsigned short prevState;  // 保存到这一步的上一个状态
};
Flag flags[65536];

    // 计算16个转换的状态
void calState(){
    short x,y;
    unsigned short temp;
    for(short i=0;i<4;++i){
        for(short j=0;j<4;++j){
            temp = 0;
            temp ^= (1<<((3-i)*4+3-j));   //第一行代表16位的高4位，同理第一列也代表高位，所以棋盘(i,j)处在16位中的位置是((3-i)*4+3-j)
            for(short t=0;t<4;++t){
                x = i + dir[t][0];
                y = j + dir[t][1];
                if(x<0 || y<0 || x>3 || y>3)
                    continue;
                temp ^= (1<<((3-x)*4+3-y));
            }
            change[i][j] = temp;
        }
    }
}

string getPointFromState(unsigned short state){
    for(short i=0;i<4;++i){
        for(short j=0;j<4;++j){
            if(change[i][j] == state){
                return "(" + to_string(i) + "," + to_string(j) +")";
            }
        }
    }
    return "(no state)";
}

void printPath(unsigned short state){
    Flag tempState = flags[state];
    if (state == tempState.prevState){
        return;
    } else {
        printPath(tempState.prevState);
        cout<< getPointFromState(tempState.moveState) ;
    }
}

// 广度搜索计算路径 以及 翻转的步数
void BFS(int state){
    queue<Node>q;
    Node cur, next;
    Flag flagState;

    cur.state = state;
    cur.step = 0;
    flagState.moveState = 0;
    flagState.prevState = state;

    q.push(cur);
    visited[state] = true;
    flags[state] = flagState;

    while(!q.empty()){
        cur = q.front();
        q.pop();
        if(cur.state == 0 || cur.state == 0xffff){
            cout<<"Find a path, it needs "<< cur.step << " steps" <<endl;
            cout<<"The path is: ";
            printPath(cur.state);
            cout<<endl;
            return;
        }
        for(short i=0;i<4;i++){
            for(short j=0;j<4;j++){
                next.state = cur.state^change[i][j];
                if(visited[next.state])
                    continue;
                Flag nextFlagState;
                next.step = cur.step + 1;

                visited[next.state] = true;

                nextFlagState.moveState = change[i][j];
                nextFlagState.prevState = cur.state;

                flags[next.state] = nextFlagState;

                q.push(next);
            }
        }
    }
    cout<<"No path!"<<endl;
    return;
}

int main(int argc, const char * argv[]) {
    char board[4][4] = {
        'b', 'w', 'w', 'b',
        'b', 'b', 'w', 'b',
        'b', 'w', 'w', 'b',
        'b', 'w', 'w', 'w',
    };
    for(short i = 0 ; i < 4 ; ++i){
        for(short j = 0 ; j < 4 ; ++j){
            initState <<= 1;
            if(board[i][j] == 'b')
                initState += 1;
        }
    }
    calState();
    memset(visited,false,sizeof(visited));
    BFS(initState);
    return 0;
}
