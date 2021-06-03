//
// Created by admin on 2021/5/28.
//
#include <stdio.h>
#include "PPI.h"
int binary_search(char * name, char ** protein, int count){
    int left = 0, right = count-1, middle;
    while (left<=right){
        middle = (left+right)/2;
        if(strcmp(protein[middle],name)==0) return middle;
        else if(strcmp(protein[middle],name)<0) left=middle+1;
        else right=middle-1;
    }
    return -1;
}

