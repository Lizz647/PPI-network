#include <stdio.h>
#include "PPI.h"
// char * ifs=" \t\n";

int main(int argc, char ** argv) {
    //输入错误时usage：
    if(argc<=2){ printf("usage: ./PPI [options] [filename]\n");return -1;}

    char *path = argv[argc-1];
    FILE * fp;
    fp = fopen(path,"r");
    struct Net net;
    net = create_net(fp);

    int opt;
    int option_index=0;
    //-F -D=[protein] -S=[protein]
    char * string="FD::S::";

    static struct option long_options[] = {
            {"Floyd",no_argument, NULL, 'F'},
            {"Dijkstra",optional_argument, NULL, 'D' },
            {"SPFA",optional_argument, NULL, 'S'},
    };

    while((opt=getopt_long(argc, argv, string, long_options, &option_index))!=-1){
        //-F或--Floyd 不带参数，输出ALL-PAIR
        if(opt == 'F') {
            printf("Floyd\nThis is the shortest path for all-pair:\n\n");
            Floyd(net);
        }
        //-D或--Dijkstra 可选参数，默认输出第一个蛋白的（首先查找输入的蛋白）
        else if(opt == 'D'){
            if(optarg == NULL || optind == argc-1){
                printf("Dijkstra\nThis is the shortest path for %s\n\n",net.protein[0]);
                Dijkstra(net,0);
            }
            else{
                int vs;
                vs = binary_search(optarg,net.protein,net.number);
                if(vs==-1) {printf("Protein Not Found!\n"); continue;}
                else {
                    printf("Dijkstra\n This is the shortest path for %s\n\n",optarg);
                    Dijkstra(net,vs);
                }
            }
        }
        //-S或--SPFA 可选参数，默认输出第一个蛋白的（首先查找输入的蛋白）
        else if(opt == 'S'){
            if(optarg == NULL || optind == argc-1){
                printf("SPFA\nThis is the shortest path for %s\n\n",net.protein[0]);
                SPFA(net,0);
            }
            else{
                int vs;
                vs = binary_search(optarg,net.protein,net.number);
                if(vs==-1) {printf("Protein Not Found!\n"); continue;}
                else {
                    printf("SPFA\n This is the shortest path for %s\n\n",optarg);
                    SPFA(net,vs);
                }
            }
        }
        if(optind==argc){break;}
    }
    return 0;
}




