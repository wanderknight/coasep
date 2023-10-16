/*计算精确时间，*/

#define M 10000
#define N 10000

typedef int (*test_funct)(int[][N]);
double qpc_time(test_funct f, int param1[][N]);
