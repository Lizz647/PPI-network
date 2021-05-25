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


