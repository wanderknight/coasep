#include "toy_CPU.h"
#include "misc.h"

/* ������CPU���洢������ɲ�����*/
long long Memory[100];
long long output[100];

int Registers[4];   //ͨ�üĴ�����
int PC_reg;         //��������� PC
int imem_adrress_reg=0;  //��ַ�Ĵ���

/*ALU ʵ�ֵĹ���*/
int Add(int a,int b);
int Sub(int a,int b);
int Mul(int a,int b);
int Div(int a,int b);

/* */
long long mem_counter;
long long instruction_counter=0;
int output_counter=0;


//��ȡbin�ļ�ͷ��
//��ȡ ������Ŀ vars_counter ��
//����ָ����Ŀ operation_counter
void bin_head(FILE * bin_fp)
{
    printf("����bin�ļ�ͷ\n");
    fread(&mem_counter,sizeof(mem_counter),1,bin_fp);
    fread(&instruction_counter,sizeof(instruction_counter),1,bin_fp);

    printf("������Ϊ��%d��ָ����Ϊ�� %d \n",(int)mem_counter,(int)instruction_counter);
}

void men_init(FILE * bin_fp)
{
    printf("�ڴ��ʼ��\n");
    imem_adrress_reg=0;
    output_counter=0;
    //char str_inst[65];
    for(; imem_adrress_reg<mem_counter; imem_adrress_reg++)
    {
        fread(&Memory[imem_adrress_reg],sizeof(Memory[imem_adrress_reg]),1,bin_fp);
//        printf("%d  %d\n",i,Memory[i]);
//        itoaPlus(str_inst,Memory[i],2);
//        printf(" ___ %s\n",str_inst);
    }


    for(; imem_adrress_reg<(mem_counter+instruction_counter); imem_adrress_reg++)
    {
        fread(&Memory[imem_adrress_reg],sizeof(Memory[imem_adrress_reg]),1,bin_fp);
//        itoaPlus(str_inst,Memory[i],2);
//        printf(" ___ %s\n",str_inst);
    }
    while(!feof(bin_fp))
    {
        fread(&output[output_counter],sizeof(output[output_counter]),1,bin_fp);
        output_counter++;
    }
    output_counter=output_counter-1;
}

void CPU_run(FILE * bin_fp)
{
    printf("��ʼִ�С���\n");
    PC_reg = mem_counter; //��ʼ��ִ�еĵ�һ��ָ��λ��
    long long instruction;
    char str_inst[65];
    while(PC_reg<(mem_counter+instruction_counter))
    {
        //ȡָ��
        instruction = Memory[PC_reg];
        //��ʾָ������
        itoaPlus(str_inst,instruction,2);
        printf("ָ��___ %s\n",str_inst);
        /*
        ָ������
        */
        int Opcode = (instruction>>56)&0xff;
        int Result_num = (instruction>>40)&0xffff;
        int Source_num1 = (instruction>>24)&0xffff;
        int Source_num2 = (instruction>>8)&0xffff;
        //����OPcode���в�ͬ�Ĳ���
        switch (Opcode)
        {
        case 8:
            Registers[Result_num]= Memory[Source_num1];
            break; // load
        case 9:
            Memory[Result_num] = Registers[Source_num1];
            //��ռĴ�����
            Registers[0]=0;
            Registers[1]=0;
            Registers[2]=0;
            Registers[3]=0;
            break; /* STORE ��������洢��Memory      */
        case 1:
            Registers[Result_num] = Add(Registers[Source_num1],Registers[Source_num2]);
            break; /* ADD      */
        case 2:
            Registers[Result_num] = Sub(Registers[Source_num1],Registers[Source_num2]);
            break; /* SUB      */
        case 3:
            Registers[Result_num] = Mul(Registers[Source_num1],Registers[Source_num2]);
            break; /* MUL      */
        case 4:
            Registers[Result_num] = Div(Registers[Source_num1],Registers[Source_num2]);
            break; /* DIV      */
        default:
            printf("���ֳ��򲻿�ִ�в���");
            exit(0);
        }
        PC_reg++;

//        printf("�Ĵ�����״̬��\n");
//        int j=0;
//        for(j;j<4;j++) printf("reg %d  %d\n",j,Registers[j]);
    }
}

void CPU(char file_bin[])
{
    printf("********��ʼִ��bin�ļ�********\n");
    //Sleep(1);
    FILE * bin_fp;
    if((bin_fp=fopen(file_bin,"rb"))==NULL) //�����ƶ��ļ���ʽ���ļ�
    {
        printf("�޷���%s�ļ�\n",file_bin);//����򿪳�����������޷����ļ�������Ϣ
        exit(0);//��ֹ����
    }

    bin_head(bin_fp);
    men_init(bin_fp);
    CPU_run(bin_fp);

    fclose(bin_fp);

    printf("�洢��״̬��\n");
    int i;
    for(i=0; i<mem_counter; i++)
    {
        printf("%d  %d\n",i,(int)Memory[i]);
    }

    printf("\n ���ִ�н�� :\n\n");
    for(i = 0; i<output_counter; i++)
    {
        printf("%d \t������ַ��%d  ����ֵ��%d\n",i,(int)output[i],(int)Memory[output[i]]);
    }
}



int Add(int a,int b)
{
    return a+b;
}

int Sub(int a,int b)
{
    return a-b;
}

int Mul(int a,int b)
{

    return a * b;
}

int Div(int a, int b)
{
    return a/b;
}
