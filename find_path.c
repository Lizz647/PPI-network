//
// Created by admin on 2021/5/28.
//
#include <stdio.h>
#include "PPI.h"
// ******************************** 队列数据结构的实现 ******************************************
// *******************************************************************************************

/* 初始化队列,不带头结点*/
int initQueue(QUEUE* INQueue)
{

    INQueue->head = NULL;
    INQueue->tail = NULL;

    return 0;
}

/* 从队尾插入一个元素 */
int enQueue(QUEUE* InQueue,int InData)
{
    NODE* pNewNode = (NODE*)malloc(sizeof(NODE));
    if (pNewNode == NULL)
    {
        return -1;
    }

    pNewNode->data = InData;
    pNewNode->next = NULL;

    /* 判断，现在队列里面有没有节点 */
    if (InQueue->head == NULL)
    {
        InQueue->head = pNewNode;
        InQueue->tail = pNewNode;
    }
    else
    {
        InQueue->tail->next = pNewNode;
        InQueue->tail = pNewNode;
    }

    return 0;
}

/* 遍历该队列 */
int visitQueue(QUEUE InQueue)
{
    QUEUE* pstTemp = &InQueue;

    /* 判断队列是否为空队列 */
    if (pstTemp->head == NULL)
    {
        printf("visitQueue: this queue is empty\n");
        return -1;
    }

    /* 遍历该队列中的所有元素 */
    while (pstTemp->head->next != NULL)
    {
        printf("%d ", pstTemp->head->data);
        pstTemp->head = pstTemp->head->next;
    }
    printf("%d \n", pstTemp->head->data);

    return 0;
}

/* 出队列 */
int deQueue(QUEUE* InQueue)
{
    int OutData;
    if (InQueue->head == NULL)
    {
        printf("delQueue: this queue is empty\n");
        return -1;
    }

    OutData = InQueue->head->data;

    NODE* pstTemp = InQueue->head;
    InQueue->head = InQueue->head->next;

    return OutData;
}

/* 判断队列是否是空队列 */
int isEmptyQueue(QUEUE InQueue)
{
    if (InQueue.head == NULL)
    {
        return 1; //是空队列
    }
    return 0; //不是空队列
}

// *******************************************************************************************
// ******************************** 队列数据结构的实现 ******************************************


// ******************************** 算法与输出的实现 ********************************************
// *******************************************************************************************

void Floyd(struct Net G) {
    int i,j,k,tmp;
    int **path = (int**) malloc(sizeof(int*)*G.number);
    for(i=0;i<G.number;i++) path[i] = (int*) malloc(sizeof(int)*G.number);

    //初始化path
    for(i=0;i<G.number;i++){
        for(j=0;j<G.number;j++){
            if(i==j) path[i][j] = -1;
            else path[i][j] = i;
        }
    }

    for(k=0;k<G.number;k++){
        for(i=0;i<G.number;i++){
            for(j=0;j<G.number;j++){
                tmp = G.PPI[i][k]+G.PPI[k][j];
                if(tmp<G.PPI[i][j]){
                    G.PPI[i][j] = tmp;
                    path[i][j] = k;
                }
            }
        }
    }

    /*做检验
    for (j = 0; j < G.number; j++) {
        printf("path[1][%d]:%d ",j,path[0][j]);
        if(j%6==0) printf("\n");
    }
    printf("\n");
    */

    //显示路径
    int vs;
    for(vs=0; vs<G.number ; vs++){
        for (j = 0; j < G.number; j++) {
            printf("  shortest(%s, %s)=%d\n", G.protein[vs], G.protein[j], G.PPI[vs][j]);
            printf("  path(%s,%s):\n", G.protein[vs], G.protein[j]);
            show_path(G, vs, j, path[vs]);
            printf("\n\n");
        }
    }

    // 释放空间
    for(i=0;i<G.number;i++) free(path[i]);
    free(path);
}

/*
 * Dijkstra最短路径。
 * 即，统计图(G)中"顶点vs"到其它各个顶点的最短路径。
 *
 * 参数说明：
 *        G -- 图
 *       vs -- 起始顶点(start vertex)。即计算"顶点vs"到其它顶点的最短路径。
 *     prev -- 前驱顶点数组。即，prev[i]的值是"顶点vs"到"顶点i"的最短路径所经历的全部顶点中，位于"顶点i"之前的那个顶点。
 *     dist -- 长度数组。即，dist[i]是"顶点vs"到"顶点i"的最短路径的长度。
 */
void Dijkstra(struct Net G, int vs)
{
    int i,j,k;
    int min;
    int tmp;
    int* dist = (int*) malloc(sizeof(int)*G.number);
    int* prev = (int*) malloc(sizeof(int)*G.number);
    int* flag =(int*)malloc(sizeof(int)*G.number);      // flag[i]=1表示"顶点vs"到"顶点i"的最短路径已成功获取。

    // 初始化
    for (i = 0; i < G.number; i++)
    {
        flag[i] = 0;              // 顶点i的最短路径还没获取到。
        prev[i] = vs;              // 顶点i的前驱顶点为-1。
        dist[i] = G.PPI[vs][i];// 顶点i的最短路径为"顶点vs"到"顶点i"的权。
    }

    // 对"顶点vs"自身进行初始化
    flag[vs] = 1;
    dist[vs] = 0;
    prev[vs] = -1;

    // 遍历G.vexnum-1次；每次找出一个顶点的最短路径。
    for (i = 1; i < G.number; i++)
    {
        // 寻找当前最小的路径；
        // 即，在未获取最短路径的顶点中，找到离vs最近的顶点(k)。
        min = INF;
        for (j = 0; j < G.number; j++)
        {
            if (flag[j]==0 && dist[j]<min)
            {
                min = dist[j];
                k = j;
            }
        }
        // 标记"顶点k"为已经获取到最短路径
        flag[k] = 1;

        // 修正当前最短路径和前驱顶点
        // 即，当已经"顶点k的最短路径"之后，更新"未获取最短路径的顶点的最短路径和前驱顶点"。
        for (j = 0; j < G.number; j++)
        {
            tmp = (G.PPI[k][j]==INF ? INF : (min + G.PPI[k][j])); // 防止溢出
            if (flag[j] == 0 && (tmp  < dist[j]) )
            {
                dist[j] = tmp;
                prev[j] = k;
            }
        }
    }

    /*做检验
    for (j = 0; j < G.number; j++) {
        printf("dist[%d]:%d ",j,dist[j]);
        if(j%6==0) printf("\n");
    }
    printf("\n\n");
    for (j = 0; j < G.number; j++) {
        printf("prev[%d]:%d ",j,prev[j]);
        if(j%6==0) printf("\n");
    }
    printf("\n");
     */

    // 打印dijkstra最短路径的结果
    // 打印最段路径线路
    printf("algorithms(%s): \n", G.protein[vs]);
    for (i = 0; i < G.number; i++) {
        printf("  shortest(%s, %s)=%d\n", G.protein[vs], G.protein[i], dist[i]);
        printf("  path(%s,%s):\n", G.protein[vs], G.protein[i]);
        show_path(G, vs, i, prev);
        printf("\n");
    }
    // 释放空间
    free(dist);
    free(prev);
    free(flag);
}

//从prev[]数组中获得具体路径
void show_path(struct Net G, int vs, int i, int prev[]){
    if (prev[i] == -1) printf("  This is me!!\n");
    else if(prev[i] == vs) printf("  %s -> %s ",G.protein[vs],G.protein[i]);
    else {
        show_path(G, vs, prev[i], prev);
        printf("-> %s ",G.protein[i]);
    }
}

//show_path star_net版本
void show_path_star(starNet G, int vs, int i, int prev[]){
    if (prev[i] == -1) printf("  This is me!!\n");
    else if(prev[i] == vs) printf("  %s -> %s ",G.protein[vs],G.protein[i]);
    else {
        show_path_star(G, vs, prev[i], prev);
        printf("-> %s ",G.protein[i]);
    }
}

void Bellman_ford(struct Net G, int vs) {
    int i,j,k,tmp;
    int* dist = (int*) malloc(sizeof(int)*G.number);
    int* prev = (int*) malloc(sizeof(int)*G.number);
    //初始化
    for (i = 0; i < G.number; i++) {
        dist[i] = G.PPI[vs][i];
        prev[i] = vs;
    }
    prev[vs] = -1;

    //松弛n-1次
    for (i = 0; i < G.number - 1; i++) {
        for (j = 0; j < G.number; j++) {
            for (k = 0; k < G.number; k++) {
                tmp = (G.PPI[j][k]==INF ? INF : (dist[j] + G.PPI[j][k])); // 防止溢出
                if (tmp  < dist[k])
                {
                    dist[k] = tmp;
                    prev[k] = j;
                }
            }
        }
    }

    // 确认有没有负环,在这里可省略
    /*
    for (int j = 0; j < G.number; j++) {
        for (int k = 0; k < G.number; k++) {
            if (G.PPI[j][k] != MAXweight) {
                if (d[k] > d[j] + G.PPI[j][k]) {
                    return -1;
                }
            }
        }
    }
    */

    /*做检验
    for (j = 0; j < G.number; j++) {
        printf("dist[%d]:%d ",j,dist[j]);
        if(j%6==0) printf("\n");
    }
    printf("\n\n");
    for (j = 0; j < G.number; j++) {
        printf("prev[%d]:%d ",j,prev[j]);
        if(j%6==0) printf("\n");
    }
    printf("\n\n");
    */

    // 输出结果
    printf("Bellman-ford(%s): \n", G.protein[vs]);
    for (i = 0; i < G.number; i++) {
        printf("  shortest(%s, %s)=%d\n", G.protein[vs], G.protein[i], dist[i]);
        printf("  path(%s,%s):\n", G.protein[vs], G.protein[i]);
        show_path(G, vs, i, prev);
        printf("\n");
    }
    // 释放空间
    free(dist);
    free(prev);
}

void SPFA(struct Net G, int vs) {
    int i,j,k,tmp;
    int* dist = (int*) malloc(sizeof(int)*G.number);
    int* prev = (int*) malloc(sizeof(int)*G.number);
    int* flag = (int*) malloc(sizeof(int)*G.number);  //标记是否在队列中
    //初始化
    for (i = 0; i < G.number; i++) {
        dist[i] = INF;
        prev[i] = vs;
        flag[i] = 0;
    }
    dist[vs] = 0;
    prev[vs] = -1;

    QUEUE queue;
    initQueue(&queue);

    enQueue(&queue,vs);
    flag[vs] = 1;

    int u;
    while (!isEmptyQueue(queue)){
        u = deQueue(&queue);
        flag[u] = 0;

        for(i=0;i<G.number;i++){
            if(G.PPI[u][i]!=INF){
                tmp = dist[u] + G.PPI[u][i];
                if(tmp<dist[i]){
                    dist[i] = tmp;
                    prev[i] = u;
                    if(!flag[i]){
                        enQueue(&queue,i);
                        flag[i] = 1;
                    }
                }
            }
        }
    }

    /*做检验
    for (j = 0; j < G.number; j++) {
        printf("dist[%d]:%d ",j,dist[j]);
        if(j%6==0) printf("\n");
    }
    printf("\n\n");
    for (j = 0; j < G.number; j++) {
        printf("prev[%d]:%d ",j,prev[j]);
        if(j%6==0) printf("\n");
    }
    printf("\n\n");
    */

    // 输出结果
    printf("SPFA(%s): \n", G.protein[vs]);
    for (i = 0; i < G.number; i++) {
        printf("  shortest(%s, %s)=%d\n", G.protein[vs], G.protein[i], dist[i]);
        printf("  path(%s,%s):\n", G.protein[vs], G.protein[i]);
        show_path(G, vs, i, prev);
        printf("\n");
    }

    //释放空间
    free(dist);
    free(prev);
    free(flag);
}

// *******************************************************************************************
// ******************************** 算法与输出的实现 ********************************************