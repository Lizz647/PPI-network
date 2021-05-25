#include <stdio.h>
#include "PPI.h"
char * ifs=" \t\n";

int main() {
struct Data data1;
char path[] = "D:\\C\\C_program\\shortpath\\miniversion.txt";
FILE * fp;
fp = fopen(path,"r");
char line[100];
while(fgets(line,sizeof(line),fp)!=NULL){
    data1 = get_data(line, ifs);
    printf("%s %s %d\n", data1.name1, data1.name2, data1.score);
}
return 0;
}
