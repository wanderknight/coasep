#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ShowValueBin(int bits, int value)
{
    int i;
    printf("%d的二进制为:",value);
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

int GetSign(int iNum)//获取符号位
{
    int iSign = iNum >> 31;
    if(iSign)//高位为1为负数
        return 1;
    else
        return 0;
}


/*输出要求
-4的真值二进制为:-100
形式
*/
int True_Code(int iNum)
{
    /*todo*/
}


/*输出要求
-4的反码二进制为:11111111111111111111111111111011
形式
*/
int Ones_complement_Code(int iNum)//反码
{
    /*todo*/
}

/*输出要求
-4的补码二进制为:11111111111111111111111111111100
形式
*/
int  Complemental_Code(int iNum)//补码
{
    /*todo*/
}


/*输出要求
-4的移码二进制为:01111111111111111111111111111100
形式
*/
int Frame_Shift(int iNum)//移码
{
    /*todo*/
}


int main(int argc, char* argv[])
{
    /*****************************************************
    1. 正数：
    正数的原码、反码、补码都相同。
    2. 负数：
    原码：负数的绝对值，并且最高位为1。
    反码：原码的符号位不变，其他位按位取反。
    补码：在反码的基础上+1。
    3. 移码：
    无论是正/负数，都是在补码的基础上，符号位取反。
    ******************************************************/


    printf("int 型的长度为：%d位\n",sizeof(int)*8);
    printf("接收输入的int型10进制数，输出真值、原码、反码、补码、移码。\n");
    /*todo
    接受输入的10进制数，输出真值、原码、反码、补码、移码。
    */

    return 0;

}
