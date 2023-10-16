#include "toy_CPU.h"
#include "misc.h"

/* 下面是CPU及存储器的组成部件。*/
long long Memory[100];
long long output[100];

int Registers[4];   //通用寄存器组
int PC_reg;         //程序计数器 PC
int imem_adrress_reg=0;  //地址寄存器

/*ALU 实现的功能*/
int Add(int a,int b);
int Sub(int a,int b);
int Mul(int a,int b);
int Div(int a,int b);

/* */
long long mem_counter;
long long instruction_counter=0;
int output_counter=0;


//读取bin文件头，
//获取 变量数目 vars_counter 和
//操作指令数目 operation_counter
void bin_head(FILE * bin_fp)
{
    printf("处理bin文件头\n");
    fread(&mem_counter,sizeof(mem_counter),1,bin_fp);
    fread(&instruction_counter,sizeof(instruction_counter),1,bin_fp);

    printf("变量数为：%d；指令数为： %d \n",(int)mem_counter,(int)instruction_counter);
}

void men_init(FILE * bin_fp)
{
    printf("内存初始化\n");
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
    printf("开始执行……\n");
    PC_reg = mem_counter; //初始化执行的第一条指令位置
    long long instruction;
    char str_inst[65];
    while(PC_reg<(mem_counter+instruction_counter))
    {
        //取指令
        instruction = Memory[PC_reg];
        //显示指令内容
        itoaPlus(str_inst,instruction,2);
        printf("指令___ %s\n",str_inst);
        /*
        指令译码
        */
        int Opcode = (instruction>>56)&0xff;
        int Result_num = (instruction>>40)&0xffff;
        int Source_num1 = (instruction>>24)&0xffff;
        int Source_num2 = (instruction>>8)&0xffff;
        //根据OPcode进行不同的操作
        switch (Opcode)
        {
        case 8:
            Registers[Result_num]= Memory[Source_num1];
            break; // load
        case 9:
            Memory[Result_num] = Registers[Source_num1];
            //清空寄存器组
            Registers[0]=0;
            Registers[1]=0;
            Registers[2]=0;
            Registers[3]=0;
            break; /* STORE 变量存入存储器Memory      */
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
            printf("出现程序不可执行操作");
            exit(0);
        }
        PC_reg++;

//        printf("寄存器组状态：\n");
//        int j=0;
//        for(j;j<4;j++) printf("reg %d  %d\n",j,Registers[j]);
    }
}

void CPU(char file_bin[])
{
    printf("********开始执行bin文件********\n");
    //Sleep(1);
    FILE * bin_fp;
    if((bin_fp=fopen(file_bin,"rb"))==NULL) //二进制读文件形式打开文件
    {
        printf("无法打开%s文件\n",file_bin);//如果打开出错，就输出“无法打开文件”的信息
        exit(0);//终止程序
    }

    bin_head(bin_fp);
    men_init(bin_fp);
    CPU_run(bin_fp);

    fclose(bin_fp);

    printf("存储器状态：\n");
    int i;
    for(i=0; i<mem_counter; i++)
    {
        printf("%d  %d\n",i,(int)Memory[i]);
    }

    printf("\n 输出执行结果 :\n\n");
    for(i = 0; i<output_counter; i++)
    {
        printf("%d \t变量地址：%d  变量值：%d\n",i,(int)output[i],(int)Memory[output[i]]);
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
