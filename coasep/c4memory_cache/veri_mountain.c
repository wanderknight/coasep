
/* mountain.c - Generate the memory mountain. */
/* $begin mountainmain */
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

#define MINBYTES (1 << 14) /* First working set size */
#define MAXBYTES (1 << 29) /* Last working set size,128M */
#define MAXSTRIDE 15       /* Stride x8 bytes */
#define MAXELEMS MAXBYTES / sizeof(long)

/* $begin mountainfuns */
long data[MAXELEMS]; /* The global array we'll be traversing */

/* $end mountainfuns */
/* $end mountainmain */
void init_data(long *data, int n);
int test(int elems, int stride);
double run(int size, int stride);

void create_csv(const char *filename, const char *title, int max_stride, int max_size)
{
    FILE *file = fopen(filename, "w");

    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    printf("Memory mountain (GB/sec)\n");
    printf(" ,");

    fprintf(file, "%s\n", title);
    fprintf(file, ",");
    for (int stride = 1; stride <= max_stride; stride++)
    {
        fprintf(file, "s%d,", stride);
        printf("s%d,", stride);
    }
    fprintf(file, "\n");
    printf("\n");

    for (int size = max_size; size >= MINBYTES; size >>= 1)
    {
        if (size > (1 << 20))
        {
            fprintf(file, "%dm,", size / (1 << 20));
            printf("%dm,", size / (1 << 20));
        }
        else
        {
            fprintf(file, "%dk,", size / 1024);
            printf("%dk,", size / 1024);
        }

        for (int stride = 1; stride <= max_stride; stride++)
        {
            float result = run(size, stride);
            fprintf(file, "%.2f,", result);
            printf("%.2f,", result); // Print to console for verification
        }
        fprintf(file, "\n");
        printf("\n"); // Print newline to console for verification
    }

    fclose(file);
}

/* $begin mountainmain */
int main()
{
    int size;   /* Working set size (in bytes) */
    int stride; /* Stride (in array elements) */

    init_data(data, MAXELEMS); /* Initialize each element in data */
    /* $end mountainmain */
    /* Not shown in the text */
    create_csv("veri_mountain.csv", "Memory mountain (GB/sec)", MAXSTRIDE, MAXBYTES);
    exit(0);
}
/* $end mountainmain */

/* init_data - initializes the array */
void init_data(long *data, int n)
{
    int i;

    for (i = 0; i < n; i++)
        data[i] = i;
}

typedef int (*test_funct)(int, int);
double QPC_time(test_funct f, int param1, int param2)
{
    LARGE_INTEGER freq;
    LARGE_INTEGER start, stop;
    double exe_time;

    // 查询cpu主频
    QueryPerformanceFrequency(&freq);

    // 计算时间延迟
    QueryPerformanceCounter(&start);

    f(param1, param2);
    QueryPerformanceCounter(&stop);
    exe_time = 1e3 * (stop.QuadPart - start.QuadPart) / freq.QuadPart;
    return exe_time;
}

/* $begin mountainfuns */
/* test - 对前“elems"个数据以步长stride进行循环,
 *        使用 4x4 循环展开.
 */
int test(int elems, int stride)
{
    long i, s, sx2 = stride * 2, sx3 = stride * 3, sx4 = stride * 4;
    long acc0, acc1, acc2, acc3;
    long length;
    long limit;
    /*增加循环次数，防止出现执行时间太短出现的除零错误*/
    for (s = 0; s < stride; s++)
    {
        acc0 = 0, acc1 = 0, acc2 = 0, acc3 = 0;
        length = elems;
        limit = length - sx4;
        /* Combine 4 elements at a time */
        for (i = 0; i < limit; i += sx4)
        {
            acc0 = acc0 + data[i];
            acc1 = acc1 + data[i + stride];
            acc2 = acc2 + data[i + sx2];
            acc3 = acc3 + data[i + sx3];
        }

        /* Finish any remaining elements */
        for (; i < length; i += stride)
        {
            acc0 = acc0 + data[i];
        }
    }

    return ((acc0 + acc1) + (acc2 + acc3));
}
/* run - 执行 test(elems, stride) 并返回读带宽 (GB/s).
 *       "size"单位为字节, "stride" 表示步长。
 *       QPC_time返回的是毫秒.
 */
double run(int size, int stride)
{
    double exe_time;
    int elems = size / sizeof(double); // todo: why double

    test(elems, stride); /* Warm up the cache */                                           // line:mem:warmup
    exe_time = QPC_time(test, elems, stride); /* Call test(elems,stride) */                // line:mem:fcyc
    return (size) / (exe_time / 1000.0) / 1024 / 1024 / 1024; /* Convert cycles to MB/s */ // line:mem:bwcompute
}
/* $end mountainfuns */
