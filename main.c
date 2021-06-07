#include <stdio.h>
#include "PPI.h"
// char * ifs=" \t\n";

int main(int argc, char ** argv) {

    if(argc<=2){ printf("usage: ./PPI [options] [filename]\n");return -1;}

    char *path = argv[argc-1];

    FILE * fp;
    fp = fopen(path,"r");
    struct Net net;
    starNet net2;
    //获得网络



    int opt;
    int option_index=0;
    char * string="FD::S::R:d::s::B::";

    static struct option long_options[] = {
            {"Floyd",no_argument, NULL, 'F'},
            {"Dijkstra",optional_argument, NULL, 'D' },
            {"SPFA",optional_argument, NULL, 'S'},
            {"Dijheap", optional_argument, NULL, 'd'},
            {"starSPFA",optional_argument, NULL, 's'},
            {"Bellman",optional_argument, NULL, 'B'},
    };


    while((opt=getopt_long(argc, argv, string, long_options, &option_index))!=-1){
        if(opt == 'F') {
            net = create_net(fp);
            rewind(fp);
            printf("Floyd\nThis is the shortest path for all-pair:\n\n");
            Floyd(net);
        }
        else if(opt == 'D'){
            net = create_net(fp);
            rewind(fp);
            if(optarg == NULL){
                printf("Dijkstra\nThis is the shortest path for %s\n\n",net.protein[0]);
                Dijkstra(net,0);
            }
            else {
                int vs;
                vs = search(optarg, net.protein, net.number);
                if (vs == -1) {
                    printf("Protein Not Found!\n");
                    continue;
                }
                else {
                    printf("Dijkstra\n This is the shortest path for %s\n\n", optarg);
                    Dijkstra(net, vs);
                }
            }
        }

        else if(opt == 'S'){
            net = create_net(fp);
            rewind(fp);
            if(optarg == NULL){
                printf("SPFA\nThis is the shortest path for %s\n\n",net.protein[0]);
                SPFA(net,0);
            }
            else{
                int vs;
                vs = search(optarg,net.protein,net.number);
                if(vs==-1) {printf("Protein Not Found!\n"); continue;}
                else {
                    printf("SPFA\n This is the shortest path for %s\n\n",optarg);
                    SPFA(net,vs);
                }
            }
        }
        else if(opt=='R'){
            net = create_net(fp);
            rewind(fp);
            if(strstr(optarg,"/")!=NULL){
                int is_find=Dijkstra_end(net, optarg);
                printf("%d\n",is_find);
            }
        }
        else if(opt == 'd'){
            net2 = create_starnet_hash(fp);

            if(optarg == NULL){
                printf("Dijheap\nThis is the shortest path for %s\n\n",net2.protein[0]);
                dij_heap(net2,0);
            }
            else {
                int vs;
                vs = search(optarg, net2.protein, net2.Vernum);
                if (vs == -1) {
                    printf("Protein Not Found!\n");
                    continue;
                }
                else {
                    printf("Dijheap\n This is the shortest path for %s\n\n", optarg);
                    dij_heap(net2, vs);
                }
            }
        }
        else if(opt == 's'){
            net2 = create_starnet_hash(fp);

            if(optarg == NULL){
                printf("starSPFA\nThis is the shortest path for %s\n\n",net2.protein[0]);
                star_SPFA(net2, 0);
            }
            else{
                int vs;
                vs = search(optarg,net2.protein,net2.Vernum);
                if(vs==-1) {printf("Protein Not Found!\n"); continue;}
                else {
                    printf("starSPFA\n This is the shortest path for %s\n\n",optarg);
                    star_SPFA(net2, vs);
                }
            }
        }
        else if(opt == 'B'){
            net = create_net(fp);
            rewind(fp);
            if(optarg == NULL){
                printf("Bellman_ford\nThis is the shortest path for %s\n\n",net.protein[0]);
                Bellman_ford(net, 0);
            }
            else{
                int vs;
                vs = search(optarg,net.protein,net.number);
                if(vs==-1) {printf("Protein Not Found!\n"); continue;}
                else {
                    printf("Bellman_ford\n This is the shortest path for %s\n\n",optarg);
                    Bellman_ford(net, vs);
                }
            }
        }
    }

    return 0;
}
