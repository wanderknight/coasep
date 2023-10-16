#include <windows.h>
#include <stdio.h>

double clockperiods = 0;//读的文件的时钟周期数差之和,初始化为零
char str[1024];//1kb大小的字符串
//读文件的方法 filename :文件名
void read(char filename[])
{
    LARGE_INTEGER start_t, stop_t;
    QueryPerformanceCounter(&start_t);
    FILE * fp;//文件指针
    if((fp=fopen(filename,"r"))==NULL) //只读文件形式打开文件
    {
        printf("无法打开文件\n");//如果打开出错，就输出“无法打开文件”的信息
        exit(0);//终止程序
    }

    char str[1024];
    while(fgets(str,1024,fp)!=NULL) //一次性读取1kb的大小的数据
    {

    }

    fclose(fp);//关闭输入文件
    QueryPerformanceCounter(&stop_t);
    clockperiods+=(stop_t.QuadPart-start_t.QuadPart);//累加每一次读取的文件的时钟周期数差
}

/*总计一个G储存,分多个小文件读出储存*/
int main()
{
    int length = sizeof(str)/sizeof(char);//str数组的长度
    length--;//长度减一，使字符数组最后一个是结束符
    for(int i = 0; i<length; i++)
    {
        str[i]='a';
    }
    int filenums,filesize ; //要生成文件的数量，大小单位为kb
    printf("必须保证你要读的文件已经存在。\n");
    printf("请输入文件大小，\n");
    scanf("%d",&filesize);
    filenums = 1024*1024/filesize;
    char chars[13];//储存文件后面大小的名字 （sizekb.txt）
    itoa(filesize,chars,10);
    //char *itoa( int value, char *string,int radix); [1]原型说明： value：欲转换的数据。
    //string：目标字符串的地址。 radix：转换后的进制数，可以是10进制、16进制等。
    char filesuffixname[20]="sizeis";//文件后面的名字
    strcat(chars,"kb.txt");//字符串拼接函数
    strcat(filesuffixname,chars);
    printf("%d个%dkb文件开始读！\n",filenums,filesize);
    for(int i =0 ; i<filenums; i++) //循环读取filenums次文件
    {
        char chars1[20];//文件后半部分的名字
        itoa(i,chars1,10);
        char filename[100] = "C:\\coasep\\coasepv1\\coasep\\c5disk\\";//修改为本机目录
        strcat(filename,chars1);//字符串拼接函数
        strcat(filename,filesuffixname);
        read(filename);//调用读文件方法
    }
    printf("%d个文件读成功！\n",filenums);
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    double exe_time;//读文件时间
    exe_time = 1e3*(clockperiods)/freq.QuadPart;
    //全部文件计算公式：文件数 * 单个文件大小 / 1024 因为这里单位是MB 文件大小单位为kb 1MB=1024kb
    double filesizes=(double)filenums*filesize/1024;
    //读文件数度 ；计算公式 全部文件大小 / 读文件用时 * 1000 因为数度以MB/S为单位 写文件用时单位为ms 1s=1000ms
    double v = filesizes/exe_time*1000;
    printf( "%d个文件读成功\t共计:%fMB\t读用时:%fms.\n",filenums,filesizes,exe_time);
    printf("读文件读数度:%.2fMB/s",v);
    return 0;
}
