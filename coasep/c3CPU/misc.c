#include "misc.h"

void line_split(char *src,const char *separator,char **dest,int *num)
{
    char *pNext;
    int count = 0;
    if (src == NULL || strlen(src) == 0)
        return;
    if (separator == NULL || strlen(separator) == 0)
        return;
    pNext = strtok(src,separator);
    while(pNext != NULL)
    {
        *dest++ = pNext;
        ++count;
        pNext = strtok(NULL,separator);
    }

    dest--;
    char *start=*dest;
    while(*(*dest)!=NULL)
    {
        if( *(*dest)=='\n')
        {
            **dest='\0';
            break;
        }
        (*dest)++;
    }
    *dest=start;

    *num = count;
}



void itoaPlus (char str[],long long num,int radix)
{
    int count = 0;
    int num1 = 8;
    int num2 = 0;
    for(int i=67; i>=0; i--)
    {
        char ch = '0' + num%radix;
        num/=radix;
        str[i]=ch;
        count++;
        if(count%num1==num2)
        {
            num1=16;
            num2=8;
            i--;
            str[i]=' ';
        }
    }
    str[68]='\0';
}


/* */
long long mem_counter1;
long long instruction_counter1=0;
int output_counter1=0;


//读取bin文件头，
//获取 变量数目 vars_counter 和
//操作指令数目 operation_counter
void binary_head(FILE * bin_fp)
{
    printf("处理bin文件头\n");
    fread(&mem_counter1,sizeof(mem_counter1),1,bin_fp);
    fread(&instruction_counter1,sizeof(instruction_counter1),1,bin_fp);

    printf("变量数为：%d；指令数为： %d \n",(int)mem_counter1,(int)instruction_counter1);
}


void read (char file_bin[])
{

    printf("二进制的内容如下\n");
    FILE * bin_example;
    if((bin_example=fopen(file_bin,"rb"))==NULL) //二进制读文件形式打开文件
    {
        printf("无法打开%s文件\n",file_bin);//如果打开出错，就输出“无法打开文件”的信息
        exit(0);//终止程序
    }

    binary_head(bin_example);

    int count = 0;
    long long  num=0;
    char str[70];

    printf("#data\n");
    while(count<mem_counter1)
    {
        fread(&num,sizeof(num),1,bin_example);
        itoaPlus(str,num,2);
        printf("%d: %s\n",count,str);
        count++;
    }
    printf("\n#code\n");
    count = 0;
    while(count<instruction_counter1)
    {
        fread(&num,sizeof(num),1,bin_example);
        itoaPlus(str,num,2);
        printf("%d: %s\n",count,str);
        count++;

    }
    printf("#\noutput\n");
    while(!feof(bin_example))  //结尾输出仍旧有小问题，多一行
    {
        fread(&num,sizeof(num),1,bin_example);
        itoaPlus(str,num,2);
        printf("%s\n",str);//
    }
    fclose(bin_example);
}
