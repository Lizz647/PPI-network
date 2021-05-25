//
// Created by admin on 2021/5/25.
//
#include "PPI.h"
#include <stdio.h>

// get_data函数用于将文件每行内容存储到一个Data结构体中：
struct Data get_data(char *line, char *ifs){
    struct Data curdata;
    curdata.name1 = strtok(line, ifs);
    curdata.name2 = strtok(NULL, ifs);
    char * score = strtok(NULL, ifs);
    curdata.score = 0; int i;
    for(i=0; score[i]!='\0';i++){
        curdata.score *=10;
        curdata.score += score[i]-'0';
    }
    return curdata;
}

//is_exist函数用于判断新读到的蛋白是否与之前重复,若重复则返回此蛋白在protein中的下标，若不重复则返回-1
int is_exist(char * name, char ** protein, int count){
    int i;
    for(i=0;i<count;i++){
        if(strcmp(name, protein[i])==0) break;
    }
    if(i==count) return -1;
    else return i;
}

struct Net create_net(FILE * fp){
    struct Net net;
    struct Data data;

    char line[100];
    int count=0;
    extern char * ifs;

    net.PPI = (int **)malloc(sizeof(int *)*(count+1));
    net.PPI[0] = (int *)malloc(sizeof(int)*(count+1));
    net.PPI[0][0]=0;
//PPI即为所构建的邻接矩阵

    net.protein = (char ** )malloc(sizeof(char*)*(count+1));
    net.protein[0] = (char *)malloc(sizeof(char)*20);
    strcpy(net.protein[0], "");
//protein为蛋白质（名字）的字符串指针


    fgets(line,sizeof(line),fp);   //忽略第一行
    int num_protein1, num_protein2;
// while内部为主体
    while(fgets(line,sizeof(line),fp)!=NULL){
        data = get_data(line, ifs);

        num_protein1=is_exist(data.name1, net.protein, count);
        if(num_protein1==-1){
            //重新分配PPI、protein的空间：
            net.PPI = (int **)realloc(net.PPI,sizeof(int*)*(count+1));
            net.PPI[count]=(int *)malloc(sizeof(int *)*count);
            int i,j;
            for(i=0;i<=count;i++){
                net.PPI[i] = (int *)realloc(net.PPI[i], sizeof(int)*(count+1));
                net.PPI[i][count]=-1;
            }
            for(j=0;j<count;j++){
                net.PPI[count][j]=-1;
            }
            net.PPI[count][count]=0;

            net.protein = (char **)realloc(net.protein, sizeof(char *)*(count+1));
            net.protein[count] = (char *) malloc(sizeof(char) * 20);
            num_protein1 = count;
            count++;
        }

        strcpy(net.protein[num_protein1],data.name1);

        num_protein2=is_exist(data.name2, net.protein, count);
        if(num_protein2==-1){
            //重新分配PPI、protein的空间：
            net.PPI = (int **)realloc(net.PPI,sizeof(int*)*(count+1));
            net.PPI[count]=(int *)malloc(sizeof(int *)*count);
            int i,j;
            for(i=0;i<=count;i++){
                net.PPI[i] = (int *)realloc(net.PPI[i], sizeof(int)*(count+1));
                net.PPI[i][count]=-1;
            }
            for(j=0;j<count;j++){
                net.PPI[count][j]=-1;
            }
            net.PPI[count][count]=0;

            net.protein = (char **)realloc(net.protein, sizeof(char *)*(count+1));
            net.protein[count] = (char *) malloc(sizeof(char) * 20);
            num_protein2 = count;
            count++;
        }
        //将新读到的内容存储到PPI、protein中：
        net.PPI[num_protein1][num_protein2]=data.score;
        net.PPI[num_protein2][num_protein1]=data.score;
        strcpy(net.protein[num_protein2],data.name2);

    }

    net.number=count;
    return net;
}

