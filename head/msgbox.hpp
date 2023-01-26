/*************************************************************************
 > Author: linux-rm
 > Mail: linux-rm@outlook.com
 > QQ:1158290244
 > QQ IT group:951234938
 ************************************************************************/

/*
本程序核心:Esc 序列
详情 http://t.csdn.cn/uudnf

使用方法:
光标控件

Esc 序列               描述
ESC[H                  将光标移动到起始位置 (0, 0)
ESC[{x};{y}H
ESC[{x};{y}f        将光标移动到第 # 行,第 # 列
ESC[#A                将光标向上移动 # 行
ESC[#B                将光标向下移动 # 行
ESC[#C                向右移动光标#列
ESC[#D                向左移动光标#列
ESC[#E                将光标移动到下一行的开头,向下 # 行
ESC[#F                将光标移动到上一行的开头,向上#行
ESC[#G                将光标移动到列#
ESC[6n                 请求光标位置(报告为 ESC[#;#R )
ESC[M                 将光标向上移动一行,如果需要滚动
ESC[7                   保存光标位置 (DEC)
ESC[8                   将光标恢复到上次保存的位置 (DEC)
ESC[s                   保存光标位置 (SCO)
ESC[u                   将光标恢复到上次保存的位置 (SCO)

擦除功能

Esc 序列              描述
ESC[J                   在显示中擦除(与 ESC[0J 相同)
ESC[0J                 从光标擦除直到屏幕结束
ESC[1J                 从光标擦除到屏幕开头
ESC[2J                 擦除整个屏幕
ESC[3J                 删除保存的行
ESC[K                  行内擦除(同 ESC[0K)
ESC[0K                从光标擦除到行尾
ESC[1K                擦除光标所在行的开头
ESC[2K                擦除整行

颜色/图形模式

Esc 序列              重置序列               描述
ESC[1;34;{...}m                                  设置单元格的图形模式,以分号 ( ; ) 分隔
ESC[0m                                               重置所有模式(样式和颜色)
ESC[1m                ESC[22m                设置粗体模式
ESC[2m                ESC[22m                设置昏暗/昏暗模式
ESC[3m                ESC[23m                设置斜体模式
ESC[4m                ESC[24m                设置下划线模式
ESC[5m                ESC[25m                设置闪烁模式
ESC[7m                ESC[27m                设置反向/反向模式
ESC[8m                ESC[28m                设置隐藏/不可见模式
ESC[9m                ESC[29m                设置删除线模式

颜色代码
名称          前景             背景
黑                30                40
红                31                41
绿                32                42
黄                33                43
蓝                34                44
品红            35                45
青                36                46
白                37                47
默认            39                49
重置             0                  0
大多数终端,除了基本的 8 种颜色外,还支持"明亮"或"粗体"颜色

支持 aixterm 规范 的终端提供了 ISO 颜色的明亮版本，无需使用粗体修饰符：

的终端提供了 ISO 颜色的明亮版本,无需使用粗体修饰符:



名称              前景             背景
亮黑                90                100
亮红                91                101
亮绿                92                102
亮黄                93                103
亮蓝                94                104
洋红                95                105
亮青                96                106
亮白                97                107

256 种颜色:

Esc 序列                            描述
ESC[38;5;{ID}m                设置前景色
ESC[48;5;{ID}m                设置背景颜色
其中{ID}应替换为以下颜色表的 0 到 255 的颜色索引:

RGB 颜色

Esc 序列                                       描述
ESC[38;2;{r};{g};{b}m                将前景色设置为 RGB
ESC[48;2;{r};{g};{b}m                将背景颜色设置为 RGB
屏幕模式
设置模式

Esc 序列                描述
ESC[={value}h      将屏幕宽度或类型更改为 value 指定的模式
ESC[=0h                40 x 25 单色(文本)
ESC[=1h                40 x 25 彩色(文字)
ESC[=2h                80 x 25 单色(文本)
ESC[=3h                80 x 25 彩色(文字)
ESC[=4h                320 x 200 4 色(图形)
ESC[=5h                320 x 200 单色(图形)
ESC[=6h                640 x 200 单色(图形)
ESC[=7h                启用换行
ESC[=13h              320 x 200 彩色(图形)
ESC[=14h              640 x 200 色(16 色图形)
ESC[=15h              640 x 350 单色(2 色图形)
ESC[=16h              640 x 350 色(16 色图形)
ESC[=17h              640 x 480 单色(2 色图形)
ESC[=18h              640 x 480 色(16 色图形)
ESC[=19h              320 x 200 色(256 色图形)
ESC[={value}l       使用与设置模式相同的值重置模式,但 7 除外,它禁用换行 此转义序列中的最后一个字符是小写 L

常见的私有模式

这些是私有模式的一些示例,规范中没有定义,但在大多数终端中都实现了

Esc 序列                    描述
ESC[?25l                    使光标不可见
ESC[?25h                   使光标可见
ESC[?47l                    恢复屏幕
ESC[?47h                   保存画面
ESC[?1049h               启用备用缓冲区
ESC[?1049l                禁用备用缓冲区

有关 XTerm定义的私有模式的更深入列表, 请参阅 XTerm 控制序列
*/

#include <iostream>

#include <sys/types.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>
#include <assert.h>
#include <string.h>
#include <signal.h>
#include "message.hpp" // 提示信息
// 以上四个获取终端尺寸

using namespace std;

char getch() // linux 获取字符的 getch() ,windows 系统要直接删除这个函数
{
	// 以下不是核心,我就少注释了
	char c = 0;
	struct termios org_opts, new_opts;
	int res = 0;
	//-----  store old settings -----------
	res = tcgetattr(STDIN_FILENO, &org_opts);
	assert(res == 0);
	//---- set new terminal parms --------
	memcpy(&new_opts, &org_opts, sizeof(new_opts));
	new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);
	c = getchar();
	//------  restore old settings ---------
	res = tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);
	assert(res == 0);
	// cout << (int)c << " , " << flush; // 测试编码
	return c;
}

struct winsize SIZE; // 定义winsize 结构体变量

#define FLUSH_SIZE ioctl(STDIN_FILENO, TIOCGWINSZ, &SIZE)
// TIOCSWINSZ命令可以将此结构的新值存放到内

void full(string color = "\e[0m")
{
	// 填充屏幕
	std::cout << color;
	for (int i = 0; i < SIZE.ws_row; i++)
	{
		FLUSH_SIZE;
		std::cout << "\e[K" << endl; // 行内擦除
	}
}

int msgbox(string title /*标题*/ = "标题", string message /*信息*/ = "信息", string button /*按钮*/ = OK, std::string color = "\e[44m\e[97m", int X /*对话框左上角起始位置X坐标*/ = -1, int Y /*对话框左上角起始位置Y坐标*/ = -1, int W /*对话框长度*/ = (SIZE.ws_col * 2 / 3), int H = /*对话框宽度*/ (SIZE.ws_row * 2 / 3)) // 对话框函数
{
	std::cout << "\e]0;" << title << "\a" << SETUP << flush; // 标题和初始化
	full(color);						 // 使用蓝色背景亮白色填充屏幕
	std::cout << '\a' << flush;

	FLUSH_SIZE;
	if (X < 0)
		X = (SIZE.ws_col - W) / 2; // 默认对话框左上角起始位置X坐标

	if (Y < 0)
		Y = (SIZE.ws_row - H) / 2; // 默认对话框左上角起始位置Y坐标

	// std::cout << "\e[H\e[97m\e[44m" << "列:" << SIZE.ws_col << "行" << SIZE.ws_row << endl; // 打印行列(调试使用)

	// 对话框边角绘制
	std::cout << "\e[" << Y << ';' << X << "H\e[97m\e[47m┌"				   // 左上角
		  << "\e[" << Y << ';' << W + X + 1 << "H\e[30m\e[47m┐"			   // 右上角
		  << "\e[" << H + Y + 1 << ';' << X << "H\e[97m\e[47m└"			   // 左下角
		  << "\e[" << H + Y + 1 << ';' << W + X + 1 << "H\e[30m\e[47m┘"		   // 右下角
		  << "\e[97m\e[40m  "							   // 右下角阴影1
		  << "\e[" << H + Y + 2 << ';' << W + X + 2 << "H\e[97m\e[40m  " << flush; // 右下角阴影1

	// 对话框边框和阴影绘制(左右)
	for (int i = X; i < W + X; i++)
	{
		std::cout << "\e[" << Y << ';' << i + 1 << "H\e[97m\e[47m─"		      // 上
			  << "\e[" << Y + H + 1 << ';' << i + 1 << "H\e[30m\e[47m─"	      // 下
			  << "\e[" << Y + H + 2 << ';' << i + 2 << "H\e[97m\e[40m " << flush; // 下阴影
	}

	std::cout << "\e[" << Y << ';' << (W - title.length()) / 2 + X << "H\e[47m\e[97m┤" << flush << " \e[34m" << title << flush << "\e[97m ├" << flush; // 标题

	// 对话框边框和阴影绘制(上下)
	for (int i = Y; i < H + Y; i++)
	{
		std::cout << "\e[" << i + 1 << ';' << X << "H\e[97m\e[47m│"		     // 左
			  << "\e[" << i + 1 << ';' << W + X + 1 << "H\e[30m\e[47m│" << flush // 右
			  << "\e[97m\e[40m  " << flush;					     // 右阴影
	}

	// 绘制背景
	for (int x = X; x < W + X; x++)
		for (int y = Y; y < H + Y; y++)
			std::cout << "\e[" << y + 1 << ';' << x + 1 << "H\e[47m\e[30m " << flush;

	std::string msg;
	for (string::size_type index = 0; index < message.size(); index++)
	{
		char c = message[index];
		msg += c;
		if (c == '\n' || c == '\r')
			msg += ((std::string) "\e[" + std::to_string(X + 1) + 'C');
	}

	int pos = msg.find("\e[0m"); // 查找指定的串
	while (pos != -1)
	{
		msg.replace(pos, 4, "\e[47m\e[30m"); // 用新的串替换掉指定的串
		pos = msg.find("\e[0m");	     // 继续查找指定的串，直到所有的都找到为止
	}

	std::cout << "\e[" << Y + 2 << ';' << X + 2 << "H\e[47m\e[30m" << msg << flush; // 打印信息

	std::cout << "\e[" << Y + H - 1 << ';' << (W - button.length()) / 2 + X << "H\e[44m\e[37m<" << button << ">\b" << flush; // 绘制按钮

	while (getch() != '\n')
		std::cout << '\a';

	std::cout
	    << REAST << message << std::endl
	    << "\e]0;shell!\a" << flush; // 恢复终端和标题

	return 0;
}
