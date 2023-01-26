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

#define host "localhost"
#define port 8080
httplib::Client cli(host, port);
auto res = cli.Get("/");

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

int httpC(std::string path = "/about", std::string way = "get", std::string body = "\0", std::string type = "application/json")
{
	std::string text = ((std::string) "主机:端口:" + host + ':' + std::to_string(port) +
			    "\nHTTP 方式: " + way +
			    "\nHTTP 路径: " + path);
	if (way == "get")
	{
		res = cli.Get(path);
	}
	else if (way == "post")
	{
		res = cli.Post(path, body, type);
		text += ("\nHTTP 请求: \n" + formatJson(body));
	}
	else
	{
		text += "\n\a\e[41m\e[97m请求方式无效!\n试试 help 参数";
		msgbox("httpC", text, "退出", "\e[41m\e[97m");
		return 22;
	}
	if (res)
	{
		text += "\n\e[0mHTTP 代码: " + std::to_string(res->status) + "\nHTTP 信息: " + httplib::to_string(res.error()) + "\nHTTP 数据: \n" + formatJson(res->body);
		msgbox("httpC", text, "关闭");
		return 0;
	}

	text += "\n\a\e[41m\e[97m网络错误!";
	msgbox("httpC", text, "退出", "\e[41m\e[97m");
	return 13;
}
