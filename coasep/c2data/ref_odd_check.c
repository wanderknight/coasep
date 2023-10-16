#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	@author sjn
	@date 2022-2-27
*/

//ȡ�ö�Ӧ�Ķ���������1���ֵĴ���
int getOccurrenceTimes(int num) {
	int count = 0;
	while(num){
		num = num & (num - 1);
		count++;
	}
	return count;
}

//��У��: �� 1 ���ֵĴ���Ϊ����ʱ������������ 0������� 1
//strΪ������ַ�����times��1���ֵĴ���
void oddCheck(char *str, int times) {
	times & 1 ? strcat(str, "0") : strcat(str, "1");
}

//żУ�飺����У���෴
//����ͬ��У��
void evenCheck(char *str, int times) {
	times & 1 ? strcat(str, "1") : strcat(str, "0");
}

int main() {
	int num;
	printf("��������������:");
	scanf("%d",&num);
	//ȡ��num��Ӧ�Ķ�������1���ֵĴ���
	int times = getOccurrenceTimes(num);
	char str[99];//�洢�ַ���
	//itoa����
	//num->Ҫת�������֣�str->Ҫд��ת�������Ŀ���ַ�����2->ת������ʱ���õĻ���
	//itoa(num,str,2)���ǰ�numת���ɶ�������ʽ���ַ������洢��str�ַ�������
	itoa(num,str,2);
	printf("1 occurrences Times : %d\n",times);
	printf("The original str : %s\n",str);
	//��У��
	oddCheck(str, times);
	printf("After odd check str : %s",str);

	return 0;
}
