#include <stdio.h>
#include "PPI.h"

// 示例程序

int main() {
    // 打开string文件
    char path[] = "/home/lizz02/miniversion.txt";
    FILE * fp;
    fp = fopen(path,"r");
    struct Net net;
    starNet net2;
    //获得网络
    net = create_net(fp);
    rewind(fp);
    net2 = create_starnet(fp);

    // 找最短路径并输出结果 因为后三种算法为单源最短路径 需要传入第二个参数说明源点 此处取0
    //Floyd(net);    //这里为了不输出太多 只输出了点0到其他点的距离
    Dijkstra(net,1);     //成了!!
    //Bellman_ford(net,0);      //成了!!
    //SPFA(net,0);      //成了!!

    // 这里有个注意点!!利用链置前向星的算法 protein的下表不一样 即上面的1和这里的1指的不是一个蛋白!!
    dij_heap(net2,1);   //终于成了!!
    //star_SPFA(net2,0);   //成了!!

    /*测试二叉堆 成功!!
    HEAP* heap= (HEAP*)malloc(sizeof(HEAP));   //结构体指针使用前要初始化!
    HEAP* heap2= (HEAP*)malloc(sizeof(HEAP));
    initHeap(heap2,&net2);
    HEAPNODE tmp;
    buildHeap(heap,net2,0);
    while(!isEmptyHeap(heap)){
        tmp=deQueueHeap(heap);
        enQueueHeap(heap2,tmp);
        printf("dist[%d]:%d\n",tmp.i,tmp.key);
    }
    while(!isEmptyHeap(heap2)){
        tmp=deQueueHeap(heap2);
        printf("dist2[%d]:%d\n",tmp.i,tmp.key);
    }
    delHeap(heap);
    delHeap(heap2);
    // */

    return 0;
}




