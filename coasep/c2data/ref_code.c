#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ShowValueBin(short bits, short value)
{
    short i;
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
short GetSign(short iNum)//��ȡ����λ
{
    short iSign = iNum >> 15;
    if(iSign)//��λΪ1Ϊ����
        return 1;
    else
        return 0;
}
short Ones_complement_Code(short iNum)//����
{
    short iSign = GetSign(iNum);
    if(iSign)//Ϊ����
    {
        iNum = ~iNum;
        iNum |= 1 << 15;
        return iNum;
    }
    else
    {
        return iNum;
    }
}
short  Complemental_Code(short iNum)//����
{
    short iSign = GetSign(iNum);
    if(iSign)
    {
        printf("####");
        ShowValueBin(16,iNum);
        iNum = Ones_complement_Code(iNum)+1;
        printf("\n**************%d,%d\n",iSign,iNum);
        printf("####");
        ShowValueBin(16,iNum);
        printf("\n");
        return iNum;
    }
    else
    {
        return iNum;
    }
}

short Frame_Shift(short iNum)//����
{
    short iSign = GetSign(iNum);
    if(iSign)
    {
        iNum &= ~(1 << 15);
        return iNum;
    }
    else
    {
        iNum |= 1 << 15;
        return iNum;
    }
}
short True_Code(short iNum)
{
    short iSign = GetSign(iNum);
    if(iSign)//�������ڴ������Բ������ʽ����
    {
        iNum = Complemental_Code(iNum);
        return iNum;
    }
    else
    {
        return iNum;
    }
}
short main(short argc, char* argv[])
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

    short True_Code1 = True_Code(1);
    short True_Code2 = True_Code(-1);

    short Complemental_Code1 = Complemental_Code(1);
    short Complemental_Code2 = Complemental_Code(-1);

    short Ones_complement1 = Ones_complement_Code(1);
    short Ones_complement2 = Ones_complement_Code(-1);

    short Frame_Shift1 = Frame_Shift(1);
    short Frame_Shift2 = Frame_Shift(-1);

    printf("True_Code1=%d\r\n", True_Code1);
    printf("True_Code2=%d\r\n", True_Code2);

    printf("Complemental_Code1=%d\r\n", Complemental_Code1);
    printf("Complemental_Code2=%d\r\n", Complemental_Code2);

    printf("Ones_complement1=%d\r\n", Ones_complement1);
    printf("Ones_complement2=%d\r\n", Ones_complement2);

    printf("Frame_Shift1=%d\r\n", Frame_Shift1);
    printf("Frame_Shift2=%d\r\n", Frame_Shift2);

    printf("\r\n");
    ShowValueBin(16, 1);
    printf("\r\n");
    ShowValueBin(16, -1);
    printf("\r\n");

    return 0;

}
