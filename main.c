#include <stdio.h>
#include "PPI.h"

int main() {

char path[] = "D:\\C\\C_program\\shortpath\\miniversion.txt";
FILE * fp;
fp = fopen(path,"r");
struct Net net;
net = create_net(fp);
int i,j;
for(i=0;i<net.number;i++)
    for(j=0;j<net.number;j++)
        if(net.PPI[i][j]!=-1)
        printf("%s %s %d\n",net.protein[i],net.protein[j],net.PPI[i][j]);
return 0;
}
