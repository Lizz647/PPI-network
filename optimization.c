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
    if (heap->currentSize == heap -> maxSize - 1) {
        heap->array = (HEAPNODE *) realloc(heap->array,sizeof(HEAPNODE) * heap->maxSize*2);
        heap -> maxSize = heap -> maxSize * 2;
    }
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

int buildHeap(HEAP* heap, starNet G, int vs)
{
    int i,k=0;
    for(i=G.head[vs]; i; i=G.next[i]) k++;
    heap -> currentSize = G.Vernum;
    heap -> maxSize = G.Vernum+10;
    heap -> array = (HEAPNODE*) malloc(sizeof(HEAPNODE)*heap->maxSize);
    k=0;
    for(i=0; i < heap->currentSize ;i++) {
        HEAPNODE tmp;
        initHeapNode(&tmp,G.weight[i],G.to[i]);
        heap->array[i+1] = tmp;
        k++;
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
    FILE * fp;
    fp = fopen("dij_heap.txt","w+");
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

    fprintf(fp, "algorithms(%s): \n", G.protein[vs]);
    for (i = 0; i < G.Vernum; i++) {
        fprintf(fp,"  shortest(%s, %s)=%d\n", G.protein[vs], G.protein[i], dist[i]);
        fprintf(fp,"  path(%s,%s):\n", G.protein[vs], G.protein[i]);
        show_path_star(G, vs, i, prev, fp);
        fprintf(fp,"\n");
    }
    // 释放空间
    free(dist);
    free(prev);
    delHeap(dijheap);
    fclose(fp);
}

// ********************************* Dij_heap ******************************************

// ********************************* star_SPFA ******************************************


void star_SPFA(starNet G, int vs) {
    FILE *fp;
    fp = fopen("star_SPFA.txt","w+");
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
    fprintf(fp,"starSPFA(%s): \n", G.protein[vs]);
    for (i = 0; i < G.Vernum; i++) {
        fprintf(fp,"  shortest(%s, %s)=%d\n", G.protein[vs], G.protein[i], dist[i]);
        fprintf(fp,"  path(%s,%s):\n", G.protein[vs], G.protein[i]);
        show_path_star(G, vs, i, prev,fp);
        fprintf(fp,"\n");
    }

    //释放空间
    free(dist);
    free(prev);
    free(flag);
    fclose(fp);
}
// ********************************* star_SPFA ******************************************

unsigned int BKDRHash(char*str)//函数的引用
{
    unsigned int seed=131 ;//本BKDRhash的seed为131
    unsigned int hash=0 ;

    while(*str)
    {
        hash=hash*seed+(*str++);
    }
    hash=(unsigned int)hash;

    return(hash & 0x7FFFFFFF);
}

unsigned int is_exist_hash(char** hash_protein,const int* hash_state, int p,char *str){
    unsigned int hashnum = BKDRHash(str);
    unsigned int pos = hashnum % p;
    //printf("判断中的pos:%d\n",pos);
    if(strcmp(hash_protein[pos],str)==0) return pos;
    if(hash_state[pos]==0) return -1;
    else {
        while(hash_state[pos] == 1){
            pos=(pos+1)%p;
            if(strcmp(hash_protein[pos],str)==0) return pos;
            if(hash_state[pos] == 0) return -1;
        }
    }
}

starNet create_starnet_hash(FILE * fp){
    starNet net;
    struct Data data;

    char line[100];
    int count=0,linenum=0;
    char * ifs = " \t\n"; //设定读取文件时的分隔符
    char **protein;


    protein = (char ** )malloc(sizeof(char*)*(count+1));
    protein[0] = (char *)malloc(sizeof(char)*25);
    strcpy(protein[0], "");
//protein为蛋白质（名字）的字符串指针

    fgets(line,sizeof(line),fp);   //忽略第一行
    while(fgets(line,sizeof(line),fp)!=NULL){
        linenum++;
    }
    int vernum=linenum;
    if(vernum>=1000000){vernum = vernum/50;}
    else if(vernum>=100000){vernum = vernum/10;}
    else;


    rewind(fp);
    int o;
    linenum = 0;
    fgets(line,sizeof(line),fp);   //忽略第一行


    char **hash_protein= (char **)malloc(sizeof (char*)*vernum);
    for(o=0;o<vernum;o++){hash_protein[o]=(char*) malloc(sizeof(char)*25);}
    int* hash_state=(int *) malloc(sizeof (int)*vernum);
    for(o=0;o<vernum;o++){hash_state[o]=0;}
    char *a=(char *) malloc(sizeof (char)*10);

    /*
    for (o=0;o<vernum;o++) {
        if(hash_protein[o]==NULL){
            hash_protein[o]="NULL";
        } else hash_protein[o]="arbi";
        printf("protein[%d]:%s state[%d]:%d\n",o,hash_protein[o],o,hash_state[o]);
    }
     */

    int num_protein1, num_protein2;
    unsigned int flag;

// while内部为主体
    //printf("line:%d\n",linenum+1);
    while(fgets(line,sizeof(line),fp)!=NULL){
        linenum++;
        //printf("line:%d\n",linenum+1);
        data = get_data(line, ifs);
        //printf("name1:%s name2:%s score:%d\n",data.name1,data.name2,data.score);
        flag = is_exist_hash(hash_protein,hash_state,vernum,data.name1);
        //printf("Flag:%d\n",flag);
        if(flag==-1){
            //insert_hash(hash_protein,hash_state,vernum,data.name1);
            unsigned int pos;

            unsigned int hashnum = BKDRHash(data.name1);

            pos = hashnum % vernum;
            if(hash_state[pos] == 0){
                //printf("pos:%d %p %p\n",pos,&hash_protein[pos],&hash_protein[pos+1]);
                strcpy(hash_protein[pos],data.name1);
                hash_state[pos] = 1;
            }
            else{
                while(hash_state[pos]==1) pos=(pos+1)%vernum;
                strcpy(hash_protein[pos],data.name1);
                //printf("pos:%d %p %p\n",pos,&hash_protein[pos],&hash_protein[pos+1]);
                hash_state[pos] = 1;
            }

            protein = (char **)realloc(protein, sizeof(char *)*(count+1));
            protein[count] = (char *) malloc(sizeof(char) * 25);
            strcpy(protein[count],data.name1);
            count++;
        }

        flag = is_exist_hash(hash_protein,hash_state,vernum,data.name2);
        //printf("Flag:%d\n",flag);
        if(flag==-1){
            //insert_hash(&h_table,vernum,data.name1);
            unsigned int pos;
            unsigned int hashnum = BKDRHash(data.name2);
            pos = hashnum % vernum;
            if(hash_state[pos] == 0){
                //printf("pos:%d %p %p\n",pos,&hash_protein[pos],&hash_protein[pos+1]);
                strcpy(hash_protein[pos],data.name2);
                hash_state[pos] = 1;
            }
            else{
                while(hash_state[pos]==1) pos=(pos+1)%vernum;
                //printf("pos:%d %p %p\n",pos,&hash_protein[pos],&hash_protein[pos+1]);
                strcpy(hash_protein[pos],data.name2);
                hash_state[pos] = 1;
            }

            protein = (char **)realloc(protein, sizeof(char *)*(count+1));
            protein[count] = (char *) malloc(sizeof(char) * 25);
            strcpy(protein[count],data.name2);
            count++;
        }
        //printf("count:%d\n",count);
    }

    /*
    for(o=0;o<count;o++) {printf("protein[%d]:%s  ",o,protein[o]);
        if(o%5==4&&o!=0) printf("\n");
    }
     */

    for(o=0;o<vernum;o++) free(hash_protein[o]);
    free(hash_protein);
    free(hash_state);


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