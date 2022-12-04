// Author: Elin.Liu
// Date: 2022-10-13 14:33:30
// Last Modified by:   Elin.Liu
// Last Modified time: 2022-10-13 14:33:30

#include "dirent.h"
#include <direct.h>
#include <io.h>
/*
    该函数需要userID返回来的包含用户ID的路径字符串
    并返回存放所有消息记录的sqlite文件路径
    例如：getCacheMsgDB("C:\Users\{Sys User}\Documents\WeChat Files\wxid_{cache_user_id}")
*/
char *getCacheMsgDB(char *path)
{
    // 初始化路径结构体对象，并使用opendir函数打开路径
    DIR *wechat_cache_dir = opendir(path);
    // 初始化目录结构体对象
    struct dirent *cache_dir;
    // 初始化路径尾部
    char endPath[100] = "\\Msg";
    int i = 0;
    // 使用readdir函数读取目录的结果不为空时
    while ((cache_dir = readdir(wechat_cache_dir)) != NULL)
    {
        // 判断路径是否为上级目录名称，如果是则略过
        if (strcmp(cache_dir->d_name, ".") == 0 || strcmp(cache_dir->d_name, "..") == 0)
            ;
        i++;
        // 这里微信约定了用户缓存规则，因此当i=5时，指针指向的就是用户的缓存文件夹
        if (i == 5)
        {
            // 聚合路径字符串
            strcat(path, cache_dir->d_name);
            strcat(path, endPath);
            break;
        }
    }
}