#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	@author sjn
	@date 2022-2-27
*/

//取得对应的二进制数中1出现的次数
int getOccurrenceTimes(int num) {
	int count = 0;
	while(num){
		num = num & (num - 1);
		count++;
	}
	return count;
}

//奇校验: 当 1 出现的次数为奇数时候在最后面加上 0，否则加 1
//str为传入的字符串，times是1出现的次数
void oddCheck(char *str, int times) {
	times & 1 ? strcat(str, "0") : strcat(str, "1");
}

//偶校验：与奇校验相反
//参数同奇校验
void evenCheck(char *str, int times) {
	times & 1 ? strcat(str, "1") : strcat(str, "0");
}

int main() {
	int num;
	printf("请输入待计算的数:");
	scanf("%d",&num);
	//取得num对应的二进制中1出现的次数
	int times = getOccurrenceTimes(num);
	char str[99];//存储字符串
	//itoa函数
	//num->要转换的数字，str->要写入转换结果的目标字符串，2->转移数字时所用的基数
	//itoa(num,str,2)就是把num转换成二进制形式的字符串并存储在str字符数组中
	itoa(num,str,2);
	printf("1 occurrences Times : %d\n",times);
	printf("The original str : %s\n",str);
	//奇校验
	oddCheck(str, times);
	printf("After odd check str : %s",str);

	return 0;
}
