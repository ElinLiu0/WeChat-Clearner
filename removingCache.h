// Author: Elin.Liu
// Date: 2022-10-03 13:26:46
// Last Modified by:   Elin.Liu
// Last Modified time: 2022-10-03 13:26:46
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <direct.h>
#include <io.h>
#include <ftw.h>
#include <windows.h>
/*
    释放被指定了本地userID的路径缓存，该函数仅可适用基于CMD的运行环境
    @param path: 被释放的缓存路径，须明确该路径为最终的完整路径
                而并非仅仅是缓存的userID路径
    例如：\n
        void removing_cache(C:\\Users\\98246\\Documents\\WeChat Files\\wxid_cdcep93sebq222\\FileStorage\\Cache\\)
*/
int removing_cache(char *path)
{
    int dir_count = 0;
    int file_count = 0;
    // 创建DIR类型结构体指针，并使用dirent.h头文件中的opendir函数打开目录
    chdir(path);
    DIR *dir = opendir(".");
    // 初始化dirent类型结构体入口指针
    struct dirent *ent;
    // 当读取到目录结尾时，返回NULL
    while ((ent = readdir(dir)) != NULL)
    {
        // 初始化状态结构体
        struct stat st;
        // 使用stat函数获取文件状态，首个参数为路径名的指针或具体值，第二个参数为状态结构体指针
        stat(ent->d_name, &st);
        // 如果S_ISDIR(st.st_mode)为真，则为目录
        if (S_ISDIR(st.st_mode))
        {
            // 防止程序过度删除，保留上层路径，使用strcmp进行检测
            if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
                continue;
            else
            {
                // 初始化int类型_dir_result，以承接来自direct.h头文件中的_rmdir函数的返回值
                const int _dir_result = _rmdir(ent->d_name);
                if (_dir_result == 0)
                {
                    printf("删除了空文件夹: %s (响应: %d)\n", ent->d_name, _dir_result);
                    dir_count++;
                }
                else
                {
                    // 初始化Powershell
                    // 初始化powershell指令
                    char command_begin[100] = "rmdir /S /Q ";
                    char end_path[100] = ".\\";
                    strcat(command_begin, end_path);
                    strcat(command_begin, ent->d_name);
                    // 获取系统返回值
                    const int _recustive_dir_result = system(command_begin);
                    if (_recustive_dir_result == 0)
                    {
                        printf("删除了非空文件夹 : %s(响应: %d)\n", ent->d_name, _recustive_dir_result);
                        dir_count++;
                    }
                }
            }
        }
        // 否则为文件
        else if (S_ISREG(st.st_mode))
        {
            if (strcmp(ent->d_name, "main.c") == 0 || strcmp(ent->d_name, "main.exe") == 0)
                continue;
            else
            {
                const int _file_result = remove(ent->d_name);
                if (_file_result == 0)
                {
                    printf("删除了文件: %s (响应: %d)\n", ent->d_name, _file_result);
                    file_count++;
                }
                else
                {
                    printf("无法删除文件: %s (响应: %d,%p)\n", ent->d_name, _file_result, _file_result);
                }
            }
        }
    }
    // 关闭路径，防止出现文件异常
    closedir(dir);
    return file_count + dir_count;
}