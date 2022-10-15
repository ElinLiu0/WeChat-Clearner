// Author: Elin.Liu
// Date: 2022-10-03 12:16:28
// Last Modified by:   Elin.Liu
// Last Modified time: 2022-10-03 12:16:28

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getCacheRoute.h"
#include "removingCache.h"
#include "getUserID.h"
#include "getVideoRoute.h"
#include "getFileRoute.h"
#include "getMsgRoute.h"
#include "getMsgDB.h"
#include "drawHeader.h"
#include "getWeChatProcess.h"
void main(int argc, char *argv[])
{
    char userChoice;
    drawHeader();
    scanf("%c", &userChoice);
    switch (userChoice)
    {
    case 'y':
        int WeChatAlive = 0;
        WeChatAlive = isWeChatAlive();
        switch (WeChatAlive)
        {
            case -1:
                printf("无法初始化进程探测器，请重新启动程序尝试！\n");
            case 0:
                system("color f");
                // 获取本地缓存的用户ID
                char* userID = getUserID();
                printf("缓存ID路径: %s \n", userID);
                // 生成缓存ID副本
                char* userIDForCache = (char*)malloc(sizeof(char) * 100);
                strcpy(userIDForCache, userID);
                char* userIDForVideo = (char*)malloc(sizeof(char) * 100);
                strcpy(userIDForVideo, userID);
                char* userIDForFile = (char*)malloc(sizeof(char) * 100);
                strcpy(userIDForFile, userID);
                char* userIDForMsg = (char*)malloc(sizeof(char) * 100);
                strcpy(userIDForMsg, userID);
                char* userIDForMsgDB = (char*)malloc(sizeof(char) * 100);
                strcpy(userIDForMsgDB, userID);
                // 获取本地缓存的完整路径
                char* cachePath = getCacheDir(userIDForCache);
                char* cacheVideoPath = getCacheVideoDir(userIDForVideo);
                char* cacheFilePath = getCacheFileDir(userIDForFile);
                char* cacheMsgPath = getCacheMsgDir(userIDForMsg);
                char* cacheMsgDBPath = getCacheMsgDB(userIDForMsgDB);
                printf("尝试删除...\n");
                // 释放缓存
                int _cache_object_count = removing_cache(cachePath);
                int _cache_video_object_count = removing_cache(cacheVideoPath);
                int _cache_File_object_count = removing_cache(cacheFilePath);
                int _cache_msg_object_count = removing_cache(cacheMsgPath);
                int _cache_msg_db_count = removing_cache(cacheMsgDBPath);
                for (int i = 0; i <= 15; i++)
                {
                    printf("-");
                    if (i == 15)
                    {
                        printf("\n");
                    }
                }
                printf("删除完毕！\n");
                printf("共删除缓存对象 %d 个。\n", (_cache_object_count + _cache_video_object_count + _cache_File_object_count + _cache_msg_object_count + _cache_msg_db_count));
                system("PAUSE");
            case 1:
				printf("检测到微信正在运行，请关闭微信后再试！\n");
				system("PAUSE");
        }
    case 'n':
        exit(EXIT_SUCCESS);
    }
}