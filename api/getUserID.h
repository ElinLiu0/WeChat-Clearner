// Author: Elin.Liu
// Date: 2022-10-13 14:33:45
// Last Modified by:   Elin.Liu
// Last Modified time: 2022-10-13 14:33:45

#include <dirent.h>
#include <string.h>
#include <direct.h>
#include <io.h>
/*
    该函数返回一个字符串，该字符串是用户的缓存ID
    需要区别，该标识区别于实际的用户微信号
*/
char *getUserID()
{
    // 初始化DIR结构体指针，并使用io.h中的函数打开C:/Users/文件夹
    DIR *_sys_users = opendir("C:\\Users");
    // 初始化dirent结构体指针，用于存储文件夹中的文件信息
    struct dirent *user;
    // 初始化路径头和尾
    char pathHeader[100] = "C:\\Users\\";
    char pathEnd[100] = "\\Documents\\WeChat Files\\";
    int i = 0;
    // 使用while循环遍历文件夹中的文件
    while ((user = readdir(_sys_users)) != NULL && i == 0)
    {
        // 这里我们判断路径是否为根和上级，如果是则跳过
        // strcmp = string compare
        if (strcmp(user->d_name, ".") == 0 || strcmp(user->d_name, "..") == 0)
            continue;
        // 使用pathHeader和pathEnd拼接路径
        // strcat = string concat
        strcat(pathHeader, user->d_name);
        strcat(pathHeader, pathEnd);
        i++;
    }
    // 初始化完整的路径指针
    char *_full_wechat_cache_path;
    _full_wechat_cache_path = (char *)malloc(sizeof(char) * 100);
    /*
        使用strcpy函数将pathHeader的值复制到_full_wechat_cache_path中
        因为之前使用了strcat函数，pathHeader的值已经被改变了
        因此只能使用strcpy函数来复制
    */
    strcpy(_full_wechat_cache_path, pathHeader);
    return _full_wechat_cache_path;
}