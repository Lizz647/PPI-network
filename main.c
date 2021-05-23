#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int judge(char a){
    if((a<='z'&&a>='a')||(a<='Z'&&a>='A')||(a<='9'&&a>='0')||a=='.'||a=='-'){return 0;}
}

struct Data
{
    int score;
    char name1[20];
    char name2[20];
    int position1;
    int position2;
};

int main()
{
    char path[100]="D:\\4932.protein.links.v11.0.txt";
    //scanf("%s",path);
    FILE *file_PPI;
    file_PPI=fopen(path,"r");
    if(file_PPI==NULL){printf("file not found, the path may be wrong~~~\n");}

    //initiating
    char line[50];//��һ�㣬����Խ��ᵼ�¶��ļ�ѭ��δ֪ԭ���ֹͣ��������������������������������
    char Score[10];
    int i=0,j=0,k=0;
    int cut[2]={0};
    struct Data *data;
    data=(struct Data*)malloc(sizeof(struct Data*)*0);


    //ignore first line's text
    fgets(line, sizeof(line), file_PPI);

    //get other line's data
    while(fgets(line, sizeof(line), file_PPI)!=NULL){
        data=(struct Data*)realloc(data, sizeof(struct Data)*(++k));
        cut[0]=0;cut[1]=0;
        strcpy(data[k-1].name1,"");
        strcpy(data[k-1].name2,"");
        strcpy(Score,"");
        i=0;j=0;//remember to initiate!!!!!!!!!!!!!!!!!!!!!!!!!
        while(line[i]!='\n'){
            if(judge(line[i])!=0&&j<=1){cut[j]=i;++j;}
            ++i;
        }
        for(i=0;i<=cut[0]-1;++i){
            data[k-1].name1[i]=line[i];
        }
        data[k-1].name1[i]='\0';
        for(i=cut[0]+1;i<=cut[1]-1;++i){
            data[k-1].name2[i-cut[0]-1]=line[i];
        }
        data[k-1].name2[i-cut[0]-1]='\0';
        //���Խ���г������룬�������Ϊ�����ַ���β����һ��'\0'
        for(i=cut[1]+1;i<=strlen(line)-1;++i){
            Score[i-cut[1]-1]=line[i];
        }
        data[k-1].score=atoi(Score);
    }

    //make an **data to store the data
    char **protein;
    int **PPI;
    PPI = (int **)malloc(sizeof(int *) * 0);
    protein = (char **)malloc(sizeof(char *) * 0);
    int sum_of_name=0;
    int l=0;
    int flag1,flag2;
    for(i=0;i<=k-1;++i){
        flag1=1;
        flag2=1;
        for(j=0;j<=i-1;++j){
            if(strcmp(data[i].name1,data[j].name1)==0&&strcmp(data[i].name1,data[j].name2)==0){
                flag1=0;break;
            }
        }
        for(j=0;j<=i-1;++j){
            if(strcmp(data[i].name2,data[j].name1)!=0&&strcmp(data[i].name2,data[j].name2)!=0){
                flag2=0;break;
            }
        }
        if(flag1==1){
            protein= (char **)realloc(protein,sizeof(char*) * (++sum_of_name));
            strcpy(protein[sum_of_name-1],data[i].name1);
            data[i].position1=sum_of_name;
            PPI=(int **)realloc(PPI,sizeof(int*) * (sum_of_name));
            for(l=0;l<=sum_of_name-1;++l){
               PPI[l]=(int *)realloc(PPI[l],sizeof(int) * (sum_of_name));
               memset(PPI[l],0,sizeof(int) *sum_of_name);
            }
        }
        if(flag2==1){
            protein= (char **)realloc(protein,sizeof(char*) * (++sum_of_name));
            strcpy(protein[sum_of_name-1],data[i].name2);
            data[i].position2=sum_of_name;
            PPI=(int **)realloc(PPI,sizeof(int*) * (sum_of_name));
            for(l=0;l<=sum_of_name-1;++l){
               PPI[l]=(int *)realloc(PPI[l],sizeof(int) * (sum_of_name));
               memset(PPI[l],0,sizeof(int) *sum_of_name);
            }
        }
        PPI[data[i].position1][data[i].position2]=data[i].score;
        PPI[data[i].position2][data[i].position1]=data[i].score;
    }
    printf("%d\n",PPI[0][1]);
    return 0;
}
//���Ӷ�O(6*n^2),�������Ѿ�û�и��õķ�����(�����ڽӾ���Ĵ�С����O(N^2),��С�ĸ��ӶȾ���O(N^2)�ˣ������θ��������̫���ܲ��������Լ���С���ݿ��ԣ�)
//1����һ���ļ�O(n)����ȡ�ض�����O(n)
//2��ȡ���ظ������ݣ����֣�O��n^2����ÿȡ��һ����̬����ռ�
