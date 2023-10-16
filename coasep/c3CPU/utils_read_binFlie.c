#include"utils_read_binFlie.h"



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

void read (char file_bin[])
{
    printf("�����Ƶ���������\n");
    FILE * bin_example;
    if((bin_example=fopen(file_bin,"rb"))==NULL) //�����ƶ��ļ���ʽ���ļ�
    {
        printf("�޷���%s�ļ�\n",file_bin);//����򿪳�����������޷����ļ�������Ϣ
        exit(0);//��ֹ����
    }
    char str[100];
    int count = 0;
    printf("#data\n");
    while(count++<mem_counter)
    {
        int  num=0;
        fread(&num,sizeof(num),1,bin_example);
        char str[70];
        itoaPlus(str,num,2);
        printf("%s\n",str);

    }
    printf("\n#code\n");
    count = instruction_counter;
    while(count-->0)
    {
        long long num=0;
        fread(&num,sizeof(num),1,bin_example);
        char str[70];
        itoaPlus(str,num,2);
        printf("%s\n",str);

    }
    printf("\n");
    while(!feof(bin_example))
    {
        fscanf(bin_example,"%s",str);
        printf("%s\n",str);//
    }
    fclose(bin_example);
}
