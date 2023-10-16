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
    printf("        ��ӭʹ�� toy_machine\n");
    printf("1) ����compiler\n");
    printf("2) ���assembler\n");
    printf("3) ִ��CPU\n");
    printf("4) ��ʾ�������ļ�\n");
    printf("0) �˳�ϵͳ\n");
    printf("==============================================\n");
    printf("������ѡ��ǰ�����֣�\n");
}


int main()
{
    char fileName_c[]="work_dir\\HighC.txt";//�߼������ļ���Code��
    char fileName_asm[]="work_dir\\HighC.asm";//����ļ�
    char fileName_bin[]="work_dir\\HighC.bin";//��ִ��bin�ļ�
    int iselect=0;
    while(1)
    {
        menu();

        scanf("%d",&iselect);
        getchar();//���ջس�

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
