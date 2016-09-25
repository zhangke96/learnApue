/*************************************************************************
	> File Name: zkls.c
	> Author:ZhangKe 
	> Mail:ch.zhangke@gmail.com 
	> Created Time: 2016年09月24日 星期六 21时41分02秒
 ************************************************************************/

 /*
  * This program is a simple implement of ls
  * usage: ./zkls pathname
  * output with a example "tool.h": -rw-rw-r-- 1 zhangke zhangke 532 Sep 24 21:40 tool.h
  * just like ls -l pathname
  */

#include <stdio.h>
#include "tool.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

char judgeStyle(mode_t mode);
void getMode(mode_t mode, char* aMode);
int main(int argc, char* argv[])
{
    int i;
    struct stat aStat;
    char error[30];
    char aMode[10];
    char style;

    if (argc == 1)
    {
        sprintf(error, "usage: %s pathname", argv[0]);
        err_quit(error);
    }
    for (i = 1; i < argc; ++i)
    {
        if (stat(argv[i], &aStat) < 0)
        {
            sprintf(error, "error with file:%s", argv[i]);
            err_ret(error);
            continue;
        }
        style = judgeStyle(aStat.st_mode);
        getMode(aStat.st_mode, aMode);
        printf("%c%s %s %ld %d %d %ld\n", style, aMode, argv[i], aStat.st_nlink, aStat.st_uid, aStat.st_gid, aStat.st_size);
        
    }
    return 0;
    
}
char judgeStyle(mode_t mode)
{
    if (S_ISREG(mode))
        return '-';
    else if (S_ISDIR(mode))
        return 'd';
    else if (S_ISCHR(mode))
        return 'c';
    else if (S_ISBLK(mode))
        return 'b';
    else if (S_ISFIFO(mode))
        return 'p';
    else if (S_ISLNK(mode))
        return 'l';
    else if (S_ISSOCK(mode))
        return 's';
    else
        return 'e';
}
void getMode(mode_t mode, char* temp)
{
    if ((mode & S_IRUSR) == S_IRUSR)
        temp[0] = 'r';
    else
        temp[0] = '-';
    if ((mode & S_IWUSR) == S_IWUSR)
        temp[1] = 'w';
    else
        temp[1] = '-';
    if (((mode & S_IXUSR) == S_IXUSR) && ((mode & S_ISUID) != S_ISUID))
        temp[2] = 'x';
    else if (((mode & S_IXUSR) == S_IXUSR) && ((mode & S_ISUID) == S_ISUID))
        temp[2] = 's';
    else if (((mode & S_IXUSR) != S_IXUSR) && ((mode & S_ISUID) == S_ISUID))
        temp[2] = 'S';
    else
        temp[2] = '-';
    if ((mode & S_IRGRP) == S_IRGRP)
        temp[3] = 'r';
    else
        temp[3] = '-';
    if ((mode & S_IWGRP) == S_IWGRP)
        temp[4] = 'w';
    else
        temp[4] = '-';
    if (((mode & S_IXGRP) == S_IXGRP) && ((mode & S_ISGID) != S_ISGID))
        temp[5] = 'x';
    else if (((mode & S_IXGRP) == S_IXGRP) && ((mode & S_ISGID) == S_ISGID))
        temp[5] = 's';
    else if (((mode & S_IXGRP) != S_IXGRP) && ((mode & S_ISGID) == S_ISGID))
        temp[5] = 'S';
    else
        temp[5] = '-';
    if ((mode & S_IROTH) == S_IROTH)
        temp[6] = 'r';
    else
        temp[6] = '-';
    if ((mode & S_IWOTH) == S_IWOTH)
        temp[7] = 'w';
    else
        temp[7] = '-';
    if (((mode & S_IXOTH) == S_IXOTH) && ((mode & S_ISVTX) != S_ISVTX))
        temp[8] = 'x';
    else if (((mode & S_IXOTH) == S_IXOTH) && ((mode & S_ISVTX) == S_ISVTX))
        temp[8] = 't';
    else if (((mode & S_IXOTH) != S_IXOTH) && ((mode & S_ISVTX) == S_ISVTX))
        temp[8] = 'T';
    else
        temp[8] = '-';
    temp[9] = 0;
}
