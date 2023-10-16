#include <string.h>

#include "toy_compiler.h"
#include "misc.h"


//������ַ�����
char var_table[100][8];//�������ڼ�����������ָ��ʹ��δ������������

//����߼�C����
char highc_lines[100][20];
char asm_lines[100][20];

int lines_num;
int iasm_lines_length;
int compile_result = 1; //1��ʾ��ȷ��0��ʾ����


/*�����ʽ��飺
1.��ȡ���룬��ɾ�����У�
2.��� data code output���Ƿ����
3.����μ����
*/
void read_check(FILE *fp)
{
    int iline=0;
    printf("��ʼ�����ʽ��顭��");

    //��ȡ�ļ�����ɾ������
    while (!feof(fp))
    {
        fgets(highc_lines[iline],20,fp);
        //�����ж���highc_lines����ֻ�����ǿ���
        //blank_flag 0 ��ʾ�գ�1��ʾ�ǿ�
        int blank_flag=0,ichar;
        for (ichar=0; ichar<strlen(highc_lines[iline]); ichar++)
        {
            if (0xff & (highc_lines[iline][ichar] > 0x20))
            {
                blank_flag=1;
                break;
            };
        }
        if(blank_flag==1)
            iline++;
    }
    lines_num=iline;
    printf("��Ч���빲 %d�С�\n",lines_num);

    //��� #data #code #output �Ƿ�����
    int i=0,data_seg_flag=0,code_seg_flag=0,output_seg_flag=0;
    for(i=0; i<lines_num; i++)
    {
        //printf("%s\n",highc_lines[i]);
        if(strcmp(highc_lines[i], "#data\n")==0) data_seg_flag=1;
        if(strcmp(highc_lines[i], "#code\n")==0) code_seg_flag=1;
        if(strcmp(highc_lines[i], "#output\n")==0) output_seg_flag=1;
    }
    if(data_seg_flag==0) printf("**** #data ��Ǵ���\n");
    if(code_seg_flag==0) printf("**** #code ��Ǵ���\n");
    if(output_seg_flag==0) printf("**** #output ��Ǵ���\n");
}

/*��Ǹ��Σ�����α���*/
void seg_compile()
{
    printf("��ʼ��α��롭��\n");
    //�����־flag��1����data,2����code��3����output
    int i,ivar=0,iasm_line=0,seg_flag=0;
    for(i=0; i<lines_num; i++)
    {
        if(strcmp(highc_lines[i], "#data\n")==0)
        {
            seg_flag = 1;
            strcpy(asm_lines[iasm_line],"#data");
            iasm_line++;
            continue;
        }
        if(strcmp(highc_lines[i], "#code\n")==0)
        {
            seg_flag = 2;
            strcpy(asm_lines[iasm_line],"#code");
            iasm_line++;
            continue;
        }
        if(strcmp(highc_lines[i], "#output\n")==0)
        {
            seg_flag =3;
            strcpy(asm_lines[iasm_line],"#output");
            iasm_line++;
            continue;
        }

        char *revbuf[5] = {0}; // for line_split
        int num;               // for line_split
        if(seg_flag==1)  //�������ݶ�
        {
            num = 0;
            line_split(highc_lines[i]," =;",revbuf,&num);
            //printf("%s,%s %s  %d\n",revbuf[0],revbuf[1],revbuf[2],num);
            strcpy(var_table[ivar],revbuf[1]);
            ivar++;
            sprintf(asm_lines[iasm_line],"%s%s%s",revbuf[1]," ",revbuf[2]);
            iasm_line++;
        }
        if(seg_flag==2)  //��������
        {
            if(strstr(highc_lines[i],"+") != NULL)
            {
                num = 0;
                line_split(highc_lines[i]," +=;",revbuf,&num);
                // printf("%s %s %s  %d\n",revbuf[0],revbuf[1],revbuf[2],num);
                sprintf(asm_lines[iasm_line],  "LOAD R1, %s",revbuf[1]);
                sprintf(asm_lines[iasm_line+1],"LOAD R2, %s",revbuf[2]);
                sprintf(asm_lines[iasm_line+2],"ADD R3, R1, R2");
                sprintf(asm_lines[iasm_line+3],"STORE %s, R3",revbuf[0]);
                iasm_line=iasm_line+4;
            }
            if(strstr(highc_lines[i],"-") != NULL)
            {
                num = 0;
                line_split(highc_lines[i]," -=;",revbuf,&num);
                //printf("%s %s %s  %d\n",revbuf[0],revbuf[1],revbuf[2],num);
                sprintf(asm_lines[iasm_line],"LOAD R1, %s",revbuf[1]);
                sprintf(asm_lines[iasm_line+1],"LOAD R2, %s",revbuf[2]);
                sprintf(asm_lines[iasm_line+2],"SUB R3, R1, R2");
                sprintf(asm_lines[iasm_line+3],"STORE %s, R3",revbuf[0]);
                iasm_line=iasm_line+4;
            }
            if(strstr(highc_lines[i],"*") != NULL)
            {
                num = 0;
                line_split(highc_lines[i]," *=;",revbuf,&num);
                //printf("%s %s %s  %d\n",revbuf[0],revbuf[1],revbuf[2],num);
                sprintf(asm_lines[iasm_line],"LOAD R1, %s",revbuf[1]);
                sprintf(asm_lines[iasm_line+1],"LOAD R2, %s",revbuf[2]);
                sprintf(asm_lines[iasm_line+2],"MUL R3, R1, R2");
                sprintf(asm_lines[iasm_line+3],"STORE %s, R3",revbuf[0]);
                iasm_line=iasm_line+4;
            }

            if(strstr(highc_lines[i],"/") != NULL)
            {
                num = 0;
                line_split(highc_lines[i]," /=;",revbuf,&num);
                //printf("%s %s %s  %d\n",revbuf[0],revbuf[1],revbuf[2],num);
                sprintf(asm_lines[iasm_line],"LOAD R1, %s",revbuf[1]);
                sprintf(asm_lines[iasm_line+1],"LOAD R2, %s",revbuf[2]);
                sprintf(asm_lines[iasm_line+2],"DIV R3, R1, R2");
                sprintf(asm_lines[iasm_line+3],"STORE %s, R3",revbuf[0]);
                iasm_line=iasm_line+4;
            }

        }

        if(seg_flag==3) //���������
        {
            num = 0;
            line_split(highc_lines[i],";",revbuf,&num);
            // printf("%s %s %s  %d\n",revbuf[0],revbuf[1],revbuf[2],num);
            sprintf(asm_lines[iasm_line],revbuf[0]);
            iasm_line++;
            //printf("%s\n",revbuf[0]);
        }
    }

    iasm_lines_length = iasm_line;

    if(compile_result)
        printf("������ɣ���ȷ\n");
    else
        printf("������ɣ�����\n");

}


void compiler(char file_c[],char file_asm[])
{
    printf("********��ʼ����********\n");
    FILE *highC_handler,*asm_handle;
    if((highC_handler=fopen(file_c,"r"))==NULL) //�߼������ļ�
    {
        printf("�޷���%s�ļ�\n",file_c);
        exit(0);//��ֹ����
    }
    if((asm_handle=fopen(file_asm,"w"))==NULL) //��������ļ�
    {
        printf("�޷���%s�ļ�\n",file_asm);
        exit(0);//��ֹ����
    }

    read_check(highC_handler);

    seg_compile();

    int i;
    for(i=0; i<iasm_lines_length; i++)
    {
        fputs(asm_lines[i],asm_handle);
        fputs("\n",asm_handle);
    }

    fclose(highC_handler);
    fclose(asm_handle);
    printf("\n");
    printf("\n");
}
