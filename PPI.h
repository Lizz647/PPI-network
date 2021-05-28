//
// Created by admin on 2021/5/25.
//

#ifndef MYPPI_PPI_H
#define MYPPI_PPI_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//*********INFinite*********//
#define INF 1000000000

// ****************************** 从string文件中提取数据 ***************************************
// ******************************************************************************************

struct Data{
    int score;
    char *name1;
    char *name2;
    int position1;
    int position2;
};

struct Net{
    char ** protein;
    int ** PPI;
    int number;
};

//for qsort (sort the protein to optimize the find
int cmp (const void *a, const void *b);
// get_data函数用于将文件每行内容存储到一个Data结构体中：
struct Data get_data(char *line, char *ifs);
//is_exist函数用于判断新读到的蛋白是否与之前重复
int is_exist(char * name, char ** protein, int count);
struct Net create_net(FILE * fp);

// ******************************************************************************************
// ****************************** 从string文件中提取数据 ***************************************


// ******************************** 队列数据结构的实现 ******************************************
// *******************************************************************************************

/* 队列的节点NODE */
typedef struct stNode
{
    int data;
    struct stNode* next;
}NODE;

/* 队列QUEUE */
typedef struct stQueue
{
    NODE* head; //队列的头
    NODE* tail; //队列的尾
}QUEUE;

/* 初始化队列,不带头结点*/
int initQueue(QUEUE* INQueue);

/* 从队尾插入一个元素 */
int enQueue(QUEUE* InQueue,int InData);

/* 遍历该队列 */
int visitQueue(QUEUE InQueue);

/* 出队列 */
int deQueue(QUEUE* InQueue);

/* 判断队列是否是空队列 */
int isEmptyQueue(QUEUE InQueue);

// *******************************************************************************************
// ******************************** 队列数据结构的实现 ******************************************


// ******************************** 算法与输出的实现 ********************************************
// *******************************************************************************************

void Floyd(struct Net G);
void Dijkstra(struct Net G, int vs);
void Bellman_ford(struct Net G, int vs);
void SPFA(struct Net G, int vs);
// void dijkstraWithBinaryHeap(struct Net G,int vs)  二叉堆优化的dijkstra 还未实现

// 帮助显示具体路径的函数
void show_path(struct Net G, int vs, int i, int prev[]);

//二分查找蛋白质
int binary_search(char * name, char ** protein, int count);

// *******************************************************************************************
// ******************************** 算法与输出的实现 ********************************************



/* ***************************  以上是最小二叉堆数据结构 还没实现 先注释掉 **************************
typedef struct heapNode{
    int key;
    int i;
}HEAPNODE;

typedef struct minHeap{
    int currentSize;
    HEAPNODE *array;
    int maxSize;
}HEAP;

int initHeapNode(HEAPNODE *a,int value_key,int value_i);

int initHeap(HEAP* heap);

void delHeap(HEAP* heap);

int isEmptyHeap(HEAP* heap);

HEAPNODE getHeapHead(HEAP* heap);

void enQueueHeap(HEAP* heap,HEAPNODE x);

void percolateDown(HEAP* heap,int hole);

HEAPNODE deQueueHeap(HEAP* heap);

int buildHeap(HEAP* heap, struct Net G, int vs);

******************** 以上是最小二叉堆数据结构 还没实现 先注释掉 ***********************     */


#endif //MYPPI_PPI_H
