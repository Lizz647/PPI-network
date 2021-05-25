//
// Created by admin on 2021/5/25.
//

#ifndef MYPPI_PPI_H
#define MYPPI_PPI_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
// get_data函数用于将文件每行内容存储到一个Data结构体中：
struct Data get_data(char *line, char *ifs);
//is_exist函数用于判断新读到的蛋白是否与之前重复
int is_exist(char * name, char ** protein, int count);
struct Net create_net(FILE * fp);
#endif //MYPPI_PPI_H
