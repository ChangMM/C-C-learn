//
//  main.cpp
//  SavePrincess
//
//  Created by cmm on 2018/9/10.
//  Copyright © 2018年 bingyan. All rights reserved.
//  拯救公主 POJ 4105 广度优先搜索
//  思考怎么输出路径
//

#include <iostream>
#include <cstring>
#include <queue>
#include <stack>
using namespace std;
#define MAX 201
char a[MAX][MAX];

struct Node{
    int x, y; //坐标。
    int gem = 0; //存储de宝石。
    int deep = 0; //搜索深度。
    Node() {}
    Node(int xx, int yy, int gg, int dd) : x(xx), y(yy), gem(gg), deep(dd) {}
};

int dir[4][2] = {{0, -1},{-1, 0},{0, 1},{1, 0}};
bool visited[MAX][MAX][(1 << 5) - 1];
int r, c, k, doorCount;
Node doors[11];

void print(int result) {
    result == -1 ? (cout << "oop!" << endl) : (cout << result << endl);
}

int bit1Count(int value) {
    unsigned int count = 0;
    while (value > 0) { // until all bits are zero
        if ((value & 1) == 1) // check lower bit
            count++;
        value >>= 1; // shift bits, removing lower bit
    }
    return count;
}

void printQueue(queue<Node> q) {
    while (!q.empty()) {
        Node node = q.front();
        q.pop();
        cout << "(" << node.x << ", " << node.y << ", "
        << bit1Count(node.gem) << ", " << node.deep << ") ";
    }
    cout << endl << endl;
}

int getTarget(Node* node, Node* endNode) {
    return (node->x == endNode->x && node->y == endNode->y && bit1Count(node->gem) >= k);
}

int bfs(Node* startNode, Node* endNode) {
    if (startNode == NULL || endNode == NULL) return -1;
    memset(visited, 0, sizeof(visited));
    visited[startNode->x][startNode->y][0] = 1;
    queue<Node> q;
    q.push(*startNode);
    while (!q.empty()) {
        Node node = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int newX = node.x + dir[i][0];
            int newY = node.y + dir[i][1];
            if (newX < 0 || newX >= r || newY < 0 || newY >= c) continue;
            if (a[newX][newY] == '#' || visited[newX][newY][node.gem]) continue;

            visited[newX][newY][node.gem] = 1;

            //记录宝石数量。
            Node newNode(newX, newY, node.gem, node.deep + 1);
            if (a[newX][newY] >= '0' && a[newX][newY] <= '4') {
//                cout<<newNode.gem<<"|"<<(1 << (a[newX][newY] - '0'))<<"=";
                newNode.gem |= (1 << (a[newX][newY] - '0'));
//                cout<<newNode.gem<<endl;
            }

            if (getTarget(&newNode, endNode)) {
//                    printQueue(q);
                return newNode.deep;
            }

            q.push(newNode);

            //如果是传送门的话就将所有其它传送门加入搜索队列。
            if (a[newX][newY] == '$') {
                for (int j = 0; j < doorCount; j++) {
                    Node currNode = doors[j];
                    if (currNode.x == newX && currNode.y == newY) continue;
                    Node doorNode(currNode.x, currNode.y, newNode.gem, newNode.deep);
                    q.push(doorNode);
                }
            }
        }
//        printQueue(q);
    }
    return -1;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        Node *startNode = NULL, *endNode = NULL;
        cin >> r >> c >> k;
        doorCount = 0;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                cin >> a[i][j];
                //记录所有传送门的位置。
                switch (a[i][j]) {
                    case '$':
                        doors[doorCount++] = Node(i, j, 0, 0);
                        break;
                    case 'S':
                        startNode = new Node(i, j, 0, 0);
                        break;
                    case 'E':
                        endNode = new Node(i, j, 0, 0);
                }
            }
        }
        print(bfs(startNode, endNode));
    }
    return 0;
}
