/*************************************************************************
 > Author: linux-rm
 > Mail: linux-rm@outlook.com
 > QQ:1158290244
 > QQ IT group:951234938
 ************************************************************************/

#include <iostream>
#include "head/httpC.hpp"

using namespace std;

void breakc(int sig)
{
	if (sig == SIGINT)
	{
		std::cerr << "\n\a用户手动退出" << std::endl;
		exit(0);
	}
}

int main(int argc, char *argv[])
{
	signal(SIGINT, breakc); // SIGINT信号处理
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
		std::cerr << "用法: " << argv[0] << " <路径> <请求方式> [请求正文(POST)='\\0']\n示例:\n"
			  << argv[0] << " /about get\n"
			  << argv[0] << " /verify post '{\"verifyKey\": \"123456\"}\n\n路径,请求方式和正文 请参阅官方文档" << std::endl;
		return 1;
	}
	return -1;
}
