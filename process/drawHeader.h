// Author: Elin.Liu
// Date: 2022-10-13 14:33:07
// Last Modified by:   Elin.Liu
// Last Modified time: 2022-10-13 14:33:07

#include <stdio.h>
#include <stdlib.h>
void drawHeader()
{
    for (int i = 0; i <= 3; i++)
    {
        printf("***");
    }
    printf(" 微信清理工具 ");
    for (int i = 0; i <= 3; i++)
    {
        printf("***");
    }
    printf("\n");
    for (int i = 0; i <= 3; i++)
    {
        printf("***");
    }
    printf("By : 柳轶霖");
    for (int i = 0; i <= 3; i++)
    {
        printf("***");
    }
    printf("\n");
    // 使用cmd指令：color c将终端文字颜色调整为红色
    system("color c");
    printf("!!!  ");
    printf("请注意：该程序会完全清除你所有的微信缓存！\n");
    printf("包含缓存的聊天记录、视频、以及文件等等！\n");
    printf("另外我们无法确保该程序会将全部的");
    system("color 6");
    printf("<消息缓存>");
    system("color c");
    printf("清除！\n");
    printf("请确保必要文件备份后再执行程序！\n");
    for (int i = 0; i <= 10; i++)
    {
        printf("-");
        if (i == 10)
        {
            printf("\n");
        }
    }
    printf("我已知晓未备份文件后的后果，并妥善保存必要数据：(输入y/n)");
}