#include <windows.h>
#include <stdio.h>

double clockperiods = 0;//�����ļ���ʱ����������֮��,��ʼ��Ϊ��
char str[1024];//1kb��С���ַ���
//���ļ��ķ��� filename :�ļ���
void read(char filename[])
{
    LARGE_INTEGER start_t, stop_t;
    QueryPerformanceCounter(&start_t);
    FILE * fp;//�ļ�ָ��
    if((fp=fopen(filename,"r"))==NULL) //ֻ���ļ���ʽ���ļ�
    {
        printf("�޷����ļ�\n");//����򿪳�����������޷����ļ�������Ϣ
        exit(0);//��ֹ����
    }

    char str[1024];
    while(fgets(str,1024,fp)!=NULL) //һ���Զ�ȡ1kb�Ĵ�С������
    {

    }

    fclose(fp);//�ر������ļ�
    QueryPerformanceCounter(&stop_t);
    clockperiods+=(stop_t.QuadPart-start_t.QuadPart);//�ۼ�ÿһ�ζ�ȡ���ļ���ʱ����������
}

/*�ܼ�һ��G����,�ֶ��С�ļ���������*/
int main()
{
    int length = sizeof(str)/sizeof(char);//str����ĳ���
    length--;//���ȼ�һ��ʹ�ַ��������һ���ǽ�����
    for(int i = 0; i<length; i++)
    {
        str[i]='a';
    }
    int filenums,filesize ; //Ҫ�����ļ�����������С��λΪkb
    printf("���뱣֤��Ҫ�����ļ��Ѿ����ڡ�\n");
    printf("�������ļ���С��\n");
    scanf("%d",&filesize);
    filenums = 1024*1024/filesize;
    char chars[13];//�����ļ������С������ ��sizekb.txt��
    itoa(filesize,chars,10);
    //char *itoa( int value, char *string,int radix); [1]ԭ��˵���� value����ת�������ݡ�
    //string��Ŀ���ַ����ĵ�ַ�� radix��ת����Ľ�������������10���ơ�16���Ƶȡ�
    char filesuffixname[20]="sizeis";//�ļ����������
    strcat(chars,"kb.txt");//�ַ���ƴ�Ӻ���
    strcat(filesuffixname,chars);
    printf("%d��%dkb�ļ���ʼ����\n",filenums,filesize);
    for(int i =0 ; i<filenums; i++) //ѭ����ȡfilenums���ļ�
    {
        char chars1[20];//�ļ���벿�ֵ�����
        itoa(i,chars1,10);
        char filename[100] = "C:\\coasep\\coasepv1\\coasep\\c5disk\\";//�޸�Ϊ����Ŀ¼
        strcat(filename,chars1);//�ַ���ƴ�Ӻ���
        strcat(filename,filesuffixname);
        read(filename);//���ö��ļ�����
    }
    printf("%d���ļ����ɹ���\n",filenums);
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    double exe_time;//���ļ�ʱ��
    exe_time = 1e3*(clockperiods)/freq.QuadPart;
    //ȫ���ļ����㹫ʽ���ļ��� * �����ļ���С / 1024 ��Ϊ���ﵥλ��MB �ļ���С��λΪkb 1MB=1024kb
    double filesizes=(double)filenums*filesize/1024;
    //���ļ����� �����㹫ʽ ȫ���ļ���С / ���ļ���ʱ * 1000 ��Ϊ������MB/SΪ��λ д�ļ���ʱ��λΪms 1s=1000ms
    double v = filesizes/exe_time*1000;
    printf( "%d���ļ����ɹ�\t����:%fMB\t����ʱ:%fms.\n",filenums,filesizes,exe_time);
    printf("���ļ�������:%.2fMB/s",v);
    return 0;
}
