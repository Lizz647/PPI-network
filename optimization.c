#include "PPI.h"

// ***************************  以下是最小二叉堆数据结构   ********************************************

int initHeapNode(HEAPNODE *a,int value_key,int value_i){
    a->key = value_key;
    a->i = value_i;
    return 0;
}

int initHeap(HEAP* heap, starNet *G)
{
    heap -> currentSize = 0;
    heap -> maxSize = G->Vernum+10;
    heap -> array = (HEAPNODE*) malloc(sizeof(HEAPNODE)*heap->maxSize);
    return 0;
}

void delHeap(HEAP* heap)
{
    free(heap -> array);
}

int isEmptyHeap(HEAP* heap)
{
    return heap->currentSize == 0;
}

HEAPNODE getHeapHead(HEAP* heap){
    return heap->array[1];
}

void enQueueHeap(HEAP* heap,HEAPNODE x){
    int hole=++heap->currentSize;
    heap->array[hole] = x;
    for(;hole>1 && x.key < heap->array[hole/2].key;hole/=2){
        heap->array[hole]=heap->array[hole/2];
        heap->array[hole/2]=x;
    }
}

void percolateDown(HEAP* heap,int hole) {
    int child;
    HEAPNODE tmp = heap->array[hole];
    for(; hole*2 <= heap->currentSize; hole = child){
        child = hole * 2;
        if(child != heap->currentSize && heap->array[child+1].key < heap->array[child].key ) child++;
        if(heap->array[child].key < tmp.key) {
            heap->array[hole] = heap->array[child];
        }
        else break;
    }
    heap->array[hole] = tmp;
    //showarray();
}

HEAPNODE deQueueHeap(HEAP* heap) {
    HEAPNODE minitem = heap->array[1];
    heap->array[1] = heap->array[heap->currentSize--];
    percolateDown(heap,1);
    return minitem;
}

int buildHeap(HEAP* heap, struct Net G, int vs)
{
    int i;
    heap -> currentSize = G.number;
    heap -> maxSize = G.number+10;
    heap -> array = (HEAPNODE*) malloc(sizeof(HEAPNODE)*heap->maxSize);

    for(i=0; i < heap->currentSize ;i++) {
        HEAPNODE tmp;
        initHeapNode(&tmp,G.PPI[vs][i],i);
        heap->array[i+1] = tmp;
    }

    for(i=heap->currentSize/2;i>0;i--){
        percolateDown(heap,i);
    }
    return 0;
}

// ************************* 以上是最小二叉堆数据结构 **********************************     */


// **************************** 链式前向星 **********************************

void initstarNet(starNet *G, int vnum, int e_num, char **protein){
    int i;
    G->Vernum = vnum;
    G->Edgenum = e_num;
    G->k=0;
    G->next= (int*)malloc(sizeof(int)*(G->Edgenum*2+5));
    G->head= (int*)malloc(sizeof(int)*vnum);
    for(i=0;i<vnum;i++) G->head[i]=0;
    G->to= (int*)malloc(sizeof(int)*(G->Edgenum*2+5));
    G->weight= (int*)malloc(sizeof(int)*(G->Edgenum*2+5));
    G->protein= (char**)malloc(sizeof(char*)*vnum);
    for(i=0;i<vnum;i++) {
        G->protein[i] = (char *)malloc(sizeof(char)*20);
        strcpy(G->protein[i],protein[i]);
    }
}

void insert(starNet *G,int u,int v,int c) {
    G->next[++G->k] = G->head[u];
    G->head[u] = G->k;
    G->to[G->k] = v;
    G->weight[G->k] = c;
    G->next[++G->k] = G->head[v];
    G->head[v] = G->k;
    G->to[G->k] = u;
    G->weight[G->k] = c;
}

starNet create_starnet(FILE * fp){
    starNet net;
    struct Data data;

    char line[100];
    int count=0,linenum=0;
    char * ifs = " \t\n"; //设定读取文件时的分隔符
    char **protein;

    protein = (char ** )malloc(sizeof(char*)*(count+1));
    protein[0] = (char *)malloc(sizeof(char)*20);
    strcpy(protein[0], "");
//protein为蛋白质（名字）的字符串指针

    fgets(line,sizeof(line),fp);   //忽略第一行
    int num_protein1, num_protein2;
// while内部为主体
    while(fgets(line,sizeof(line),fp)!=NULL){
        linenum++;
        data = get_data(line, ifs);

        num_protein1=is_exist(data.name1, protein, count);
        if(num_protein1==-1){
            protein = (char **)realloc(protein, sizeof(char *)*(count+1));
            protein[count] = (char *) malloc(sizeof(char) * 20);
            num_protein1 = count;
            count++;
        }

        strcpy(protein[num_protein1],data.name1);

        num_protein2=is_exist(data.name2, protein, count);
        if(num_protein2==-1){
            protein = (char **)realloc(protein, sizeof(char *)*(count+1));
            protein[count] = (char *) malloc(sizeof(char) * 20);
            num_protein2 = count;
            count++;
        }
        strcpy(protein[num_protein2],data.name2);
    }

    initstarNet(&net,count,linenum,protein);
    qsort(net.protein, count, sizeof(net.protein[0]), cmp);

    rewind(fp);
    fgets(line,sizeof(line),fp);   //忽略第一行
// while内部为主体
    int s=0;
    while(fgets(line,sizeof(line),fp)!=NULL){
        s++;
        data = get_data(line, ifs);
        insert(&net, is_exist_binary(data.name1,net.protein,count),
               is_exist_binary(data.name2,net.protein,count),data.score);
    }

    return net;
}

// **************************** 链式前向星 **********************************

// ********************************* Dij_heap ******************************************

void dij_heap(starNet G,int vs) {
    int i;
    int* dist = (int*) malloc(sizeof(int)*G.Vernum);
    int* prev = (int*) malloc(sizeof(int)*G.Vernum);
    for (i = 0; i < G.Vernum; i++) prev[i] = vs;              // 顶点i的前驱顶点为-1。
    for (i = 0; i < G.Vernum; i++) dist[i] = INF;
    prev[vs] = -1;
    dist[vs] = 0;

    // 建立堆
    HEAP* dijheap= (HEAP*)malloc(sizeof(HEAP));
    initHeap(dijheap,&G);
    // 建立节点
    HEAPNODE node;
    initHeapNode(&node,dist[vs],vs);

    // 节点入堆
    enQueueHeap(dijheap,node);
    while (!isEmptyHeap(dijheap)) {
        node = deQueueHeap(dijheap);
        if (dist[node.i] < node.key) continue;
        for (i = G.head[node.i]; i; i = G.next[i]) {
            if (dist[G.to[i]] > dist[node.i] + G.weight[i]) {
                dist[G.to[i]] = dist[node.i] + G.weight[i];
                prev[G.to[i]] = node.i;
                HEAPNODE tmpnode;
                initHeapNode(&tmpnode,dist[G.to[i]],G.to[i]);
                enQueueHeap(dijheap,tmpnode);
            }
        }
    }

    /*做检验
    for (j = 0; j < G.Vernum; j++) {
        printf("dist[%d]:%d ",j,dist[j]);
        if(j%6==0) printf("\n");
    }
    printf("\n\n");

    for (j = 0; j < G.Vernum; j++) {
        printf("prev[%d]:%d ",j,prev[j]);
        if(j%6==0) printf("\n");
    }
    printf("\n\n");
    */

    printf("algorithms(%s): \n", G.protein[vs]);
    for (i = 0; i < G.Vernum; i++) {
        printf("  shortest(%s, %s)=%d\n", G.protein[vs], G.protein[i], dist[i]);
        printf("  path(%s,%s):\n", G.protein[vs], G.protein[i]);
        show_path_star(G, vs, i, prev);
        printf("\n");
    }
    // 释放空间
    free(dist);
    free(prev);
    delHeap(dijheap);
}

// ********************************* Dij_heap ******************************************

// ********************************* star_SPFA ******************************************


void star_SPFA(starNet G, int vs) {
    int i,tmp;
    int* dist = (int*) malloc(sizeof(int)*G.Vernum);
    int* prev = (int*) malloc(sizeof(int)*G.Vernum);
    int* flag = (int*) malloc(sizeof(int)*G.Vernum);  //标记是否在队列中
    //初始化
    for (i = 0; i < G.Vernum; i++) {
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
        for (i = G.head[u]; i; i = G.next[i]){
            tmp = dist[u] + G.weight[i];
            if(tmp < dist[G.to[i]]){
                dist[G.to[i]] = tmp;
                prev[G.to[i]] = u;
                if(!flag[G.to[i]]){
                    enQueue(&queue,G.to[i]);
                    flag[G.to[i]] = 1;
                }
            }
        }
    }

    // 输出结果
    printf("SPFA(%s): \n", G.protein[vs]);
    for (i = 0; i < G.Vernum; i++) {
        printf("  shortest(%s, %s)=%d\n", G.protein[vs], G.protein[i], dist[i]);
        printf("  path(%s,%s):\n", G.protein[vs], G.protein[i]);
        show_path_star(G, vs, i, prev);
        printf("\n");
    }

    //释放空间
    free(dist);
    free(prev);
    free(flag);
}

// ********************************* star_SPFA ******************************************