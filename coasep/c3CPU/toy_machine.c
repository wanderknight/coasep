#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#include "toy_compiler.h"
#include "toy_assembler.h"
#include "toy_CPU.h"
#include "misc.h"


void menu()
{
    printf("==============================================\n");
    printf("        欢迎使用 toy_machine\n");
    printf("1) 编译compiler\n");
    printf("2) 汇编assembler\n");
    printf("3) 执行CPU\n");
    printf("4) 显示二进制文件\n");
    printf("0) 退出系统\n");
    printf("==============================================\n");
    printf("请输入选项前的数字：\n");
}


int main()
{
    char fileName_c[]="work_dir\\HighC.txt";//高级语言文件（Code）
    char fileName_asm[]="work_dir\\HighC.asm";//汇编文件
    char fileName_bin[]="work_dir\\HighC.bin";//可执行bin文件
    int iselect=0;
    while(1)
    {
        menu();

        scanf("%d",&iselect);
        getchar();//吸收回车

        switch(iselect)
        {
        case 1:
            compiler(fileName_c,fileName_asm);
            break;
        case 2:
            assembler(fileName_asm,fileName_bin);
            break;
        case 3:
            CPU(fileName_bin);
            break;
        case 4:
            read(fileName_bin);
            break;
        case 0:
            exit(0);

        }
    }
    return 0;
}
