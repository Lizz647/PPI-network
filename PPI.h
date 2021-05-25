//
// Created by admin on 2021/5/25.
//

#ifndef MYPPI_PPI_H
#define MYPPI_PPI_H
#include <stdlib.h>
#include <string.h>
struct Data{
    int score;
    char *name1;
    char *name2;
    int position1;
    int position2;
};

struct Protein
{
    char name[20];
    int position;
    struct Protein *next;
} protein;

// get_data函数用于将文件每行内容存储到一个Data结构体中：
struct Data get_data(char *line, char *ifs);


#endif //MYPPI_PPI_H
