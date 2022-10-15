/*
	导入Windows.h个tlhelp32.h文件用于访问WindowsAPI和进程信息
*/
#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <stdbool.h>
int isWeChatAlive()
{					
	// 初始化进程入口结构体
	PROCESSENTRY32 currentProcess;
	// 初始化进程快照大小
	currentProcess.dwSize = sizeof(currentProcess);
	// 使用CreateToolhelp32Snapshot函数创建进程快照，该参数接受一个快照掩码，需要拍摄快照的进程ID
	HANDLE hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	// 判断进程快照是否创建成功，如果hProcess值是宏中定义的空值
	if (hProcess == INVALID_HANDLE_VALUE)
	{
		// 则抛出异常
		printf("初始化内存快照失败！\n");
		// 使用exit()推出进程
		return -1;
	}
	/*
		使用Process32First()函数获取进程快照中的第一个进程信息
		该函数接收两个参数，第一个参数是进程快照句柄，第二个参数是进程入口结构体的指针
		最终返回一个布尔值信号量，用于表示Process32First()函数是否从系统句柄中读取成功读取到进程信息
		当其确定初始化了第一个进程后，我们才可以使用Process32Next()函数获取下一个进程信息
	*/
	bool bMore = Process32First(hProcess,&currentProcess);
	while (bMore)
	{
		// 判断微信进程是否存活
		if (strcmp(currentProcess.szExeFile, "WeChat.exe")) {
			/*
				当从系统句柄中探测到微信进程存活时，
				那么对应的，将会触发一个信号量为1给缓存释放进程
				以表达当前系统环境并不适合缓存释放进程的执行。
				因为我们也无法能够预测到：当微信进程处于存活状态时，执行释放缓存会造成什么不可预知的后果
				所以这里的我们将false定义为信号量值为1的宏是相对系统状态而言定义来的
			*/
			return 1;
			break;
		}
		else {
			/*
				如果为false，则继续获取下一个进程信息。
				Process32Next()函数的参数列表同Process32First()这里不做赘述
			*/
			bMore = Process32Next(hProcess,&currentProcess);
		}	
	}
	// 释放系统句柄
	CloseHandle(hProcess);
}