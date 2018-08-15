//
//  main.c
//  Joseph
//
//  Created by cmm on 2018/7/4.
//  Copyright © 2018年 bingyan. All rights reserved.
//  双向链表解决约瑟夫问题
//

#include <stdio.h>
typedef struct node {
    struct node* next;
    struct node* prev;
    int num;
} Node;

    // create node list
Node * CreateNode (int total) {
    Node * head = malloc(sizeof(Node));
    Node * tail = malloc(sizeof(Node));
    head->num = 1;
    tail = head;
    for (int i=2; i<=total;i++){
        Node * p = malloc(sizeof(Node));
        p->num = i;
        tail->next = p;
        p->prev = tail;
        tail = tail->next;
    }
    head->prev = tail;
    tail->next = head;
    return head;
}

    // release node
Node * DeleteNode (Node * head, int m) {
    int count = 1;
    Node* temp = malloc(sizeof(Node));
    temp = head;
    while(count < m) {
        temp = temp->next;
        count++;
    }
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    head = temp->next;
    return head;
}


int main(int argc, const char * argv[]) {
    int total, gap, result[301], count = 0;
    while(scanf("%d%d", &total, &gap)){
        if (total == 0 && gap ==0) {
            break;
        }
        Node* head = CreateNode(total);
        while(head->next != head) {
            head = DeleteNode(head, gap);
        }
            //      printf("%d\n", head->num);  // It does not work printing the result directly. why?
        result[count] = head->num;
        count++;
    }
    for (int i =0; i< count; i++){
        printf("%d\n", result[i]);
    }
    return 0;
}
