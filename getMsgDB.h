// Author: Elin.Liu
// Date: 2022-10-04 16:04:07
// Last Modified by:   Elin.Liu
// Last Modified time: 2022-10-04 16:04:07
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <direct.h>
#include <io.h>
#include <ftw.h>
#include <windows.h>
/*
    该函数需要userID返回来的包含用户ID的路径字符串
    并返回存放所有消息记录的sqlite文件路径
    例如：getCacheMsgDB("C:\Users\{Sys User}\Documents\WeChat Files\wxid_{cache_user_id}")
*/
char *getCacheMsgDB(char *path)
{
    DIR *wechat_cache_dir = opendir(path);
    struct dirent *cache_dir;
    char endPath[100] = "\\Msg";
    int i = 0;
    while ((cache_dir = readdir(wechat_cache_dir)) != NULL)
    {
        if (strcmp(cache_dir->d_name, ".") == 0 || strcmp(cache_dir->d_name, "..") == 0)
            ;
        i++;
        // 这里微信约定了用户缓存规则，因此当i=5时，指针指向的就是用户的缓存文件夹
        if (i == 5)
        {
            strcat(path, cache_dir->d_name);
            strcat(path, endPath);
            break;
        }
    }
}