#include <stdio.h>
#include "PPI.h"

// 示例程序

int main() {
    // 打开string文件
    char path[] = "/home/lizz02/miniversion.txt";
    FILE * fp;
    fp = fopen(path,"r");
    struct Net net;
    //获得网络
    net = create_net(fp);

    /*  输出获得的蛋白质网络
    for(i=0;i<net.number;i++)
        for(j=0;j<net.number;j++)
            if(net.PPI[i][j]!=-1)
                printf("%s %s %d\n",net.protein[i],net.protein[j],net.PPI[i][j]);
    */

    // 找最短路径并输出结果 因为后三种算法为单源最短路径 需要传入第二个参数说明源点 此处取0
    Floyd(net);    //这里为了不输出太多 只输出了点0到其他点的距离
    //Dijkstra(net,1);     //成了!!
    //Bellman_ford(net,35);      //成了!!
    //SPFA(net,5);      //成了!

    return 0;
}




