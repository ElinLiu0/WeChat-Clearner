// Author: Elin.Liu
// Date: 2022-10-03 14:27:58
// Last Modified by:   Elin.Liu
// Last Modified time: 2022-10-03 14:27:58

#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <direct.h>
#include <io.h>
#include <ftw.h>
#include <windows.h>
/*
    该函数返回一个字符串，该字符串是用户的缓存ID
    需要区别，该标识区别于实际的用户微信号
*/
char *getUserID()
{
    DIR *_sys_users = opendir("C:\\Users");
    struct dirent *user;
    char pathHeader[100] = "C:\\Users\\";
    char pathEnd[100] = "\\Documents\\WeChat Files\\";
    int i = 0;
    while ((user = readdir(_sys_users)) != NULL && i == 0)
    {
        if (strcmp(user->d_name, ".") == 0 || strcmp(user->d_name, "..") == 0)
            continue;
        strcat(pathHeader, user->d_name);
        strcat(pathHeader, pathEnd);
        i++;
    }
    char *_full_wechat_cache_path;
    _full_wechat_cache_path = (char *)malloc(sizeof(char) * 100);
    strcpy(_full_wechat_cache_path, pathHeader);
    return _full_wechat_cache_path;
}