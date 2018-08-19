//
//  main.cpp
//  HeapSort
//
//  Created by cmm on 2018/8/19.
//  Copyright © 2018年 bingyan. All rights reserved.
//  算法导论 堆排序算法实现 利用了最大堆
//

#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;
vector<int> int_array;

int parent_node(int i){
    return floor(i/2);
}

int left_node(int i){
    return 2*i;
}

int right_node(int i){
    return 2*i+1;
}

// 维护某个节点的最大堆性质
void max_heapify(vector<int> &array, int heap_size, int i){
    int left = left_node(i),
                 right = right_node(i),
                 largest = 0;
    if(left<=heap_size && array[left-1]>array[i-1])
        largest = left;
    else
        largest = i;
    if(right<=heap_size && array[right-1]>array[largest-1])
        largest = right;
    if (largest != i){
        swap(array[i-1],array[largest-1]);
        max_heapify(array, heap_size, largest);
    }
}

// 构建最大堆
void build_max_heap(vector<int> &array, int heap_size){
    for(int i = floor(heap_size/2);i>=1;i--)
        max_heapify(array, heap_size, i);
}

// 堆排序算法实现
void heap_sort(vector<int> &array){
    int heap_size = int(array.size());
    build_max_heap(array, heap_size);
    for(int i = heap_size; i>=1;i--){
        swap(array[0], array[i-1]);
        heap_size = heap_size - 1;
        max_heapify(array, heap_size, 1);
    }
}

int main(int argc, const char * argv[]) {
    int count, temp;
    cin>>count;
    for(int i=1; i<=count;i++){
        cin>>temp;
        int_array.push_back(temp);
    }
    heap_sort(int_array);
    for(int i=0; i<=count-1;i++){
        cout<<int_array[i]<<' ';
    }
    return 0;
}
//输入的数据
//10
//16 4 10 14 7 9 3 2 8 1
