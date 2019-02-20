// Multiplayer Game.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

// 初始化一个地址
void Test()
{
	sockaddr_in myAddr;
	memset(myAddr.sin_zero, 0, sizeof(myAddr.sin_zero));		//memset(void *s, int ch,size_t n);中ch实际范围应该在0~~255，因为该函数只能取ch的后八位赋值给你所输入的范围的每个字节
	myAddr.sin_family = AF_INET;								//协议族
	myAddr.sin_port = htons(80);								//平台字节序转为网络字节序
	myAddr.sin_addr.S_un.S_un_b.s_b1 = 65;
	myAddr.sin_addr.S_un.S_un_b.s_b2 = 254;
	myAddr.sin_addr.S_un.S_un_b.s_b3 = 248;
	myAddr.sin_addr.S_un.S_un_b.s_b4 = 180;
}

class BB
{};

void Test2(BB* b)
{
}

void Test3(BB& b)
{
}

int main()
{
	BB newB;
	BB* newBPtr = &newB;
	Test2(&newB);
	Test3(newB);

    std::cout << "Hello World!\n"; 
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
