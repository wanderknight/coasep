#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ShowValueBin(int bits, int value)
{
    int i;
    printf("%d�Ķ�����Ϊ:",value);
    for(i = bits-1; i >=0; i--)
    {
        if(value & (1 << i))
        {
            printf("1");
        }
        else
        {
            printf("0");
        }
    }
}

int GetSign(int iNum)//��ȡ����λ
{
    int iSign = iNum >> 31;
    if(iSign)//��λΪ1Ϊ����
        return 1;
    else
        return 0;
}


/*���Ҫ��
-4����ֵ������Ϊ:-100
��ʽ
*/
int True_Code(int iNum)
{
    /*todo*/
}


/*���Ҫ��
-4�ķ��������Ϊ:11111111111111111111111111111011
��ʽ
*/
int Ones_complement_Code(int iNum)//����
{
    /*todo*/
}

/*���Ҫ��
-4�Ĳ��������Ϊ:11111111111111111111111111111100
��ʽ
*/
int  Complemental_Code(int iNum)//����
{
    /*todo*/
}


/*���Ҫ��
-4�����������Ϊ:01111111111111111111111111111100
��ʽ
*/
int Frame_Shift(int iNum)//����
{
    /*todo*/
}


int main(int argc, char* argv[])
{
    /*****************************************************
    1. ������
    ������ԭ�롢���롢���붼��ͬ��
    2. ������
    ԭ�룺�����ľ���ֵ���������λΪ1��
    ���룺ԭ��ķ���λ���䣬����λ��λȡ����
    ���룺�ڷ���Ļ�����+1��
    3. ���룺
    ��������/�����������ڲ���Ļ����ϣ�����λȡ����
    ******************************************************/


    printf("int �͵ĳ���Ϊ��%dλ\n",sizeof(int)*8);
    printf("���������int��10�������������ֵ��ԭ�롢���롢���롢���롣\n");
    /*todo
    ���������10�������������ֵ��ԭ�롢���롢���롢���롣
    */

    return 0;

}
