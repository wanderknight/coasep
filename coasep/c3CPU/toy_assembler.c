#include "misc.h"
#include "toy_assembler.h"


//变量地址分配表
char var_assign_table[100][8];
int ivar_used=0;
long long vars_counter=0;
long long operation_counter=0;

//int register_assign_table[100];//寄存器分配状态表，0表示未使用，1表示使用
char asm_line[20];
int line_total=0;


short find_var_address(char var_name[])
{
    short i;
    for(i=0; i<ivar_used; i++)
        //printf("find_var_address %s %s %d \n",var_name,var_assign_table[i],strcmp(var_assign_table[i],var_name));
        if(strcmp(var_assign_table[i],var_name)==0)   return i;
}

void seg_count(FILE *asm_fp,FILE *bin_fp)
{
    printf("代码统计……\n");
    int seg_flag=0;
    line_total=0;
    vars_counter=0;
    operation_counter=0;
    while(!feof(asm_fp))  //计算各段位置
    {
        line_total++;  //解决最后一行输出错误问题，统计行数
        fgets(asm_line,20,asm_fp);
        if(strcmp(asm_line, "#data\n")==0)
        {
            seg_flag = 1;
            continue;
        }
        if(strcmp(asm_line, "#code\n")==0)
        {
            seg_flag = 2;
            continue;
        }
        if(strcmp(asm_line, "#output\n")==0)
        {
            seg_flag =3;
            continue;
        }

        if(seg_flag==1) vars_counter++;
        if(seg_flag==2) operation_counter++;

    }
    printf("变量共计: %d 个; 操作共计： %d 个，共%d 行。\n",vars_counter,operation_counter,line_total);
    fwrite(&vars_counter,sizeof(vars_counter),1,bin_fp);  //输出bin文件头,变量数
    fwrite(&operation_counter,sizeof(operation_counter),1,bin_fp);  //输出bin文件头，指令操作数量

    rewind(asm_fp);
}


void seg_assembler(FILE *asm_fp,FILE *bin_fp)
{
    printf("开始逐段汇编……\n");
    int seg_flag=0,ibin=0;

    char *revbuf[5] = {0}; // for line_split
    int num;               // for line_split
    int iload=0;
    int iline=0;
    ivar_used=0;

    while(iline <line_total-1)
    {
        iline++;
        fgets(asm_line,20,asm_fp);
        printf("%s",asm_line);
        if(strcmp(asm_line, "#data\n")==0)
        {
            seg_flag = 1;
            continue;
        }
        if(strcmp(asm_line, "#code\n")==0)
        {
            seg_flag = 2;
            continue;
        }
        if(strcmp(asm_line, "#output\n")==0)
        {
            seg_flag =3;
            continue;
        }


        if(seg_flag==1)  //汇编数据段
        {
            line_split(asm_line," ",revbuf,&num);
            //printf("line_split %s %s %d\n",revbuf[0],revbuf[1],num);

            //分配地址，并写值
            long long var_tmep;
            var_tmep=atoi(revbuf[1]);
            fwrite(&var_tmep,sizeof(var_tmep),1,bin_fp);
            ibin++;

            strcpy(var_assign_table[ivar_used],strcat(revbuf[0],"\0")); //记录使用的变量名，同时，索引对应数据保存地址
            //printf("---%s\n",var_assign_table[ivar_used]);
            ivar_used++;
        }

        long long temp_instruct=0;
        int temp_reg1=0,temp_reg2=0,temp_reg3=0,temp_mem=0;
        char temp_var[8]= {0};
        short opcode;
        char str_inst[65];


        if(seg_flag==2)  //汇编代码段
        {
            if(strstr(asm_line,"LOAD") != NULL)
            {
                //LOAD R1, aa 待处理模式
                opcode = 8; //0b00001000
                //temp_reg1= find_avail_register();

                line_split(asm_line," ,",revbuf,&num);
                //printf("%s %s %s  %d\n",revbuf[0],revbuf[1],revbuf[2],num);
                temp_mem = find_var_address(revbuf[2]);
                //printf("mem = %d\n",temp_mem);
                if(iload == 0)
                {
                    temp_instruct=((((long long)opcode<<16) | (long long)0)<<16  | (long long)temp_mem)<<24;
                    iload=1;
                }
                else
                {
                    temp_instruct=((((long long)opcode<<16) | (long long)1)<<16  | (long long)temp_mem)<<24;
                    iload =0;
                }
            }
            if(strstr(asm_line,"STORE") != NULL)
            {
                //STORE c, R3 待处理模式
                opcode = 9; //0b000 01001

                line_split(asm_line," ,",revbuf,&num);
                //printf("%s %s %s  %d\n",revbuf[0],revbuf[1],revbuf[2],num);
                temp_mem = find_var_address(revbuf[1]);

                //printf("temp_mem %d",temp_mem);

                temp_instruct=((((long long)opcode<<16) | (long long)temp_mem)<<16  | (long long)2)<<24;
            }
            if(strstr(asm_line,"ADD") != NULL)
            {
                opcode = 1; //0b0000 0001
                temp_instruct=(((((long long)opcode<<16) | (long long)2)<<16  | (long long)0)<<16 | (long long)1)<<8;
            }
            if(strstr(asm_line,"SUB") != NULL)
            {
                opcode = 2; //0b0000 0002
                temp_instruct=(((((long long)opcode<<16) | (long long)2)<<16  | (long long)0)<<16 | (long long)1)<<8;
            }
            if(strstr(asm_line,"MUL") != NULL)
            {
                opcode = 3; //0b0000 0003
                temp_instruct=(((((long long)opcode<<16) | (long long)2)<<16  | (long long)0)<<16 | (long long)1)<<8;
            }
            if(strstr(asm_line,"DIV") != NULL)
            {
                opcode = 4; //0b0000 0004
                temp_instruct=(((((long long)opcode<<16) | (long long)2)<<16  | (long long)0)<<16 | (long long)1)<<8;
            }
            fwrite(&temp_instruct,sizeof(temp_instruct),1,bin_fp);
            //下面注释部分 可以检查指令格式
#include "misc.h"
            itoaPlus(str_inst,temp_instruct,2);
            printf("___%s\n",str_inst);

        }
        if(seg_flag==3)  //处理输出段
        {
            long long temp_out;

            line_split(asm_line,"CPU_printf(",revbuf,&num);
            line_split(revbuf[0],")",revbuf,&num);
            temp_out = (long long)find_var_address(revbuf[0]);
            printf("输出地址：%d \n",temp_out);
            fwrite(&temp_out,sizeof(temp_out),1,bin_fp);
        }
    } // end of while
}


void assembler(char file_asm[],char file_bin[])
{
    printf("********开始汇编********\n");
    FILE *asm_handle,*bin_handler;

    if((asm_handle=fopen(file_asm,"r"))==NULL) //汇编文件
    {
        printf("无法打开%s文件\n",file_asm);
        exit(0);//终止程序
    }
    if((bin_handler=fopen(file_bin,"wb"))==NULL) //bin文件
    {
        printf("无法打开%s文件\n",file_bin);
        exit(0);//终止程序
    }

    seg_count(asm_handle,bin_handler);
    seg_assembler(asm_handle,bin_handler);
    //展示使用的变量
    int i;
    printf("变量分配表情况var_assign_table：\n",var_assign_table[i]);
    for(i=0; i<ivar_used; i++)
        printf("地址：%d  变量名：%s\n",i,var_assign_table[i]);

    fclose(asm_handle);
    fclose(bin_handler);

    printf("\n");
    printf("\n");
}
