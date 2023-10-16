#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
/***多线程 ref:https://www.jianshu.com/p/07a4739334e8

void* myfunc(void *args)
{
    printf("Hello world!\n");
    return NULL;
}


int main()
{
    pthread_t th;
    pthread_create(&th,NULL,myfunc,NULL);
    pthread_join(th,NULL);
    printf("Hello world!\n");
    return 0;
}

***/

void* myfunc(void *args)
{
    int i;
    char *name = (char*)args;
    for(i=1;i<500;i++)
    printf("%s:%d\n",name,i);
    return NULL;
}

int main()
{
    pthread_t th1;
    pthread_t th2;

    pthread_create(&th1,NULL,myfunc,"th1");
    pthread_create(&th2,NULL,myfunc,"th2");
    pthread_join(th1,NULL);
    pthread_join(th2,NULL);
    printf("End!\n");
    return 0;
}





/***多进程 https://blog.csdn.net/jaj2003/article/details/123910646
#include <unistd.h>
#include <stdio.h>

#include <stdio.h>
#include<stdlib.h>

void tellEnd()
{
	puts("The end!");
}

int main(void)
{
	atexit(tellEnd);
	puts("exit");
}



#include <stdio.h>
#include<Windows.h>

int main()
{
	system("notepad");
	return(0);
}
***/
