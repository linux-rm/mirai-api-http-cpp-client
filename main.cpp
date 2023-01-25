/*************************************************************************
 > Author: linux-rm
 > Mail: linux-rm@outlook.com
 > QQ:1158290244
 > QQ IT group:951234938
 ************************************************************************/

#include <iostream>
#include "msgbox.hpp"
#include "httpC.hpp"

using namespace std;

void breakc(int sig)
{
	if (sig == SIGINT)
	{
		std::cout
			<< REAST << std::endl
			<< "\e]0;shell!\a" << flush; // 恢复终端和标题
		exit(0);
	}
}

int main(int argc, char *argv[])
{
	signal(SIGINT, breakc); // SIGINT信号处理
	FLUSH_SIZE;
	if (argc == 3)
	{
		httpC(argv[1], argv[2]);
		return 0;
	}
	else if (argc == 4)
	{
		httpC(argv[1], argv[2], argv[3]);
		return 0;
	}
	else
	{
		msgbox("帮助", "用法: ./mcc <路径> <请求方式> [请求正文(POST)='\\0']\n示例:\n./mcc /about get\n./mcc /verify post '{\"verifyKey\": \"123456\"}'", "知道了");
		return 1;
	}
	return -1;
}
