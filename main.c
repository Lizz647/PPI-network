#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define inf 1000000000

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

struct Protein
{
    char name[20];
    int position;
    struct Protein *next;
} protein;

int main()
{
    char path[100]="D:\\test\\miniversion.txt";
    //scanf("%s",path);
    FILE *file_PPI;
    file_PPI=fopen(path,"r");
    if(file_PPI==NULL){printf("file not found, the path may be wrong~~~\n");}

    //initiating
    char line[50];//大一点，数组越界会导致读文件循环未知原因的停止！！！！！！！！！！！！！！！！
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
        //测试结果中出现乱码，解决方法为在其字符串尾部加一个'\0'
        for(i=cut[1]+1;i<=strlen(line)-1;++i){
            if(line[i]>='0'&&line[i]<='9'){Score[i-cut[1]-1]=line[i];}
        }
        data[k-1].score=atoi(Score);
    }

    //make a list node to store the name
    struct Protein *head,*ending,*node;
    head = (struct Protein*)malloc(sizeof(struct Protein));
    ending=head;ending->next=NULL;
    int **PPI;
    int sum_of_name=0;
    int flag1,flag2;
    for(i=0;i<=k-1;++i){
        flag1=1;
        flag2=1;
        struct Protein *p=head;
        while(p->next!=NULL){
            p=p->next;
            if(strcmp(data[i].name1,p->name)==0){
                flag1=0;
                break;
            }
        }
        p=head;
        while(p->next!=NULL){
            p=p->next;
            if(strcmp(data[i].name2,p->name)==0){
                flag2=0;
                break;
            }
        }
        if(flag1==1){
            node=(struct Protein*)malloc(sizeof(struct Protein));
            strcpy(node->name,data[i].name1);
            ++sum_of_name;
            node->position=sum_of_name;
            ending->next = node;
            ending=node;
        }
        if(flag2==1){
            node=(struct Protein*)malloc(sizeof(struct Protein));
            strcpy(node->name,data[i].name2);
            ++sum_of_name;
            node->position=sum_of_name;
            ending->next = node;
            ending=node;
        }
        ending->next=NULL;
    }
    struct Protein *p=head;
    while(p->next!=NULL){
        p=p->next;
    }

    //initiating the PPI matrix and the result (min distance) matrix
    PPI=(int **)malloc(sizeof(int *) * sum_of_name);
    for (i = 0; i < sum_of_name; ++i)
	{
		PPI[i] = (int *)malloc(sizeof(int) * sum_of_name);
	}
	for(i=0;i<=sum_of_name-1;++i){
        for(j=0;j<=sum_of_name-1;++j){
            if(i==j){PPI[i][j]=0;}
            else{PPI[i][j]=inf;}
        }
	}
	int **result;
    result=(int **)malloc(sizeof(int *) * sum_of_name);
    for (i = 0; i < sum_of_name; ++i)
	{
		result[i] = (int *)malloc(sizeof(int) * sum_of_name);
	}
	for(i=0;i<=sum_of_name-1;++i){
        for(j=0;j<=sum_of_name-1;++j){
            if(i==j){result[i][j]=0;}
            else{result[i][j]=inf;}
        }
	}
	//get PPI
	int position1=0,tmp=0,position2=0;
	for(i=0;i<=k-1;++i){
        tmp=-1;
        p=head;
        while(p->next!=NULL){
            p=p->next;
            ++tmp;
            if(strcmp(data[i].name1,p->name)==0){
                position1=tmp;
                p->position=tmp;
            }
        }
        tmp=-1;
        p=head;
        while(p->next!=NULL){
            p=p->next;
            ++tmp;
            if(strcmp(data[i].name2,p->name)==0){
                position2=tmp;
                p->position=tmp;
            }
        }
        PPI[position1][position2]=data[i].score;
        PPI[position2][position1]=data[i].score;
        result[position1][position2]=data[i].score;
        result[position2][position1]=data[i].score;
	}

	//floyd algorithm
	int l=0;
	for(l=0;l<sum_of_name;l++){
         for(i=0;i<sum_of_name;i++){
             for(j=0;j<sum_of_name;j++){
                 if(result[i][j]>result[i][l]+result[l][j]){result[i][j]=result[i][l]+result[l][j];}
             }
         }
	}
    printf("%d",result[3][88]);
    return 0;
}
