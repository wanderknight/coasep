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


//��ȡbin�ļ�ͷ��
//��ȡ ������Ŀ vars_counter ��
//����ָ����Ŀ operation_counter
void binary_head(FILE * bin_fp)
{
    printf("����bin�ļ�ͷ\n");
    fread(&mem_counter1,sizeof(mem_counter1),1,bin_fp);
    fread(&instruction_counter1,sizeof(instruction_counter1),1,bin_fp);

    printf("������Ϊ��%d��ָ����Ϊ�� %d \n",(int)mem_counter1,(int)instruction_counter1);
}


void read (char file_bin[])
{

    printf("�����Ƶ���������\n");
    FILE * bin_example;
    if((bin_example=fopen(file_bin,"rb"))==NULL) //�����ƶ��ļ���ʽ���ļ�
    {
        printf("�޷���%s�ļ�\n",file_bin);//����򿪳�����������޷����ļ�������Ϣ
        exit(0);//��ֹ����
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
    while(!feof(bin_example))  //��β����Ծ���С���⣬��һ��
    {
        fread(&num,sizeof(num),1,bin_example);
        itoaPlus(str,num,2);
        printf("%s\n",str);//
    }
    fclose(bin_example);
}
