/*************************************************************************
	> File Name: tool.h
	> Author:ZhangKe 
	> Mail:ch.zhangke@gmail.com 
	> Created Time: 2016年09月24日 星期六 21时35分39秒
 ************************************************************************/

#ifndef _APUE_H
#define _APUE_H
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
void err_ret(char* str)
{
    printf("%s; The errno is %s\n",str, strerror(errno));
}
void err_quit(char* str)
{
    printf("%s\n", str);
    exit(-1);
}
#endif
