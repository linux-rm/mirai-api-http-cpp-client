/*************************************************************************
 > Author: linux-rm
 > Mail: linux-rm@outlook.com
 > QQ:1158290244
 > QQ IT group:951234938
 ************************************************************************/

#include <iostream>
#include "httplib.h"

using namespace std;
using namespace httplib;

#define host "0.0.0.0"
#define port 8080
httplib::Client cli(host, port);
httplib::Result res = cli.Get("/");

std::string getLevelStr(int level)
{
	string levelStr = "";
	for (int i = 0; i < level; i++)
	{
		levelStr += "\t";
	}
	return levelStr;
}

std::string formatJson(string text)
{
	std::string json;
	for (int i = 0; text[i] != '\0'; i++)
		if (text[i] != ' ' && text[i] != '\n' && text[i] != '\r' && text[i] != '\t')
			json += text[i];
	json += '\0';
	string result = "\e[0m\e[30m";
	int level = 0;
	for (string::size_type index = 0; index < json.size(); index++)
	{
		char c = json[index];
		if (level > 0 && '\n' == json[json.size() - 1])
		{
			result += getLevelStr(level);
		}
		switch (c)
		{
		case '{':
		case '[':
			result += ((std::string) "\e[43m" + c + '\n');
			level++;
			result += getLevelStr(level);
			break;
		case ',':
		case ';':
			result += ((std::string) "\e[44m" + c + '\n');
			result += getLevelStr(level);
			break;
		case '}':
		case ']':
			result += "\n";
			level--;
			result += getLevelStr(level);
			result += ((std::string) "\e[43m" + c);
			break;
		case ':':
			result += ((std::string) "\e[46m" + c);
			break;
		default:
			result += ((std::string) "\e[42m" + c);
			break;
		}
	}
	return (result + "\e[0m");
}

int httpC(std::string path , std::string way , std::string body = "\0", std::string type = "application/json")
{
	std::cerr << "主机:端口: " << host << ':' << port
			  << "\nHTTP 方式: " << way
			  << "\nHTTP 路径: " << path;
	if (way == "get")
	{
		res = cli.Get(path);
	}
	else if (way == "post")
	{
		res = cli.Post(path, body, type);
	std::cerr << "\nHTTP 请求: \n" << formatJson(body);
	}
	else
	{
		std::cerr << "\n\a\e[41m\e[97m请求方式无效!\n试试 help 参数";
		return 22;
	}
	if (res)
	{
		std::cerr << "\n\e[0mHTTP 代码: " << res->status 
				  << "\nHTTP 信息: " << httplib::to_string(res.error())
				  << "\nHTTP 数据: \n";
		std::cout << formatJson(res->body);
		return 0;
	}

	std::cerr << "\n\a\e[41m\e[97m网络错误!";
	return 13;
}
