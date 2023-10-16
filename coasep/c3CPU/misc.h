#ifndef MISC_H_INCLUDED
#define MISC_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include<string.h>

void line_split(char *src,const char *separator,char **dest,int *num);
void itoaPlus (char str[],long long num,int radix);
void read (char file_bin[]);
#endif // MISC_H_INCLUDED


