# 使用GNU Make工具进行统一编译
all:icon generate
# 生成图标文件
icon:
	# 使用mingw中的win32工具 windres.exe 将图像icon.rc编译成二进制文件icon.o
	windres ./icons/icons.rc ./icons/icons.o
# 生成主文件(WeChatCleaner.c)的二进制可执行文件
generate:
	# 使用mingw中的win32工具 gcc.exe 将C语言源文件main.c编译成二进制文件main.o
	# 其中第一个参数是C源文件，一个参数为图标的目标文件
	# -o 参数代表输出的目标文件，格式为.exe
	gcc ./WeChatCleaner.c ./icons/icons.o -o ./bin/WeChatCleaner.exe
