/*
	导入Windows.h个tlhelp32.h文件用于访问WindowsAPI和进程信息
*/
#include <windows.h>
#include <TlHelp32.h>
#include <stdio.h>
int isWeChatAlive()
{
	// 初始化进程入口结构体
	PROCESSENTRY32 processEntry;
	// 初始化进程快照大小
	processEntry.dwSize = sizeof(processEntry);
	// 使用CreateToolhelp32Snapshot函数创建进程快照，该参数接受一个快照掩码，需要拍摄快照的进程ID
	HANDLE hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	// 判断进程快照是否创建成功，如果hProcess值是宏中定义的空值
	if (hProcess == INVALID_HANDLE_VALUE)
	{
		return -1;
	}
	/*
		使用Process32First()函数获取进程列表中第一个条目是否复制到Buffer(缓冲区)
		该函数接收两个参数，第一个参数是进程快照句柄，第二个参数是进程入口结构体的指针
		最终返回一个布尔值信号量，用于表示Process32First()函数是否从系统句柄中读取成功读取到进程信息
		当其确定初始化了第一个进程后，我们才可以使用Process32Next()函数获取下一个进程信息
	*/
	BOOL bMore = Process32First(hProcess, &processEntry);
	while (bMore)
	{
		// 判断进程WeChat.exe是否存在于句柄中
		if (strcmp(processEntry.szExeFile, "WeChat.exe") == 0)
		{
			// 存在则关闭句柄检查
			CloseHandle(hProcess);
			return 1;
			break;
		}
		bMore = Process32Next(hProcess, &processEntry);
	}
	return 0;
}
