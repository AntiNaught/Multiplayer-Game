// Multiplayer Game.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

// 初始化一个地址
//void Test()
//{
//	sockaddr_in myAddr;
//	memset(myAddr.sin_zero, 0, sizeof(myAddr.sin_zero));		//memset(void *s, int ch,size_t n);中ch实际范围应该在0~~255，因为该函数只能取ch的后八位赋值给你所输入的范围的每个字节
//	myAddr.sin_family = AF_INET;								//协议族
//	myAddr.sin_port = htons(80);								//平台字节序转为网络字节序
//	myAddr.sin_addr.S_un.S_un_b.s_b1 = 65;
//	myAddr.sin_addr.S_un.S_un_b.s_b2 = 254;
//	myAddr.sin_addr.S_un.S_un_b.s_b3 = 248;
//	myAddr.sin_addr.S_un.S_un_b.s_b4 = 180;
//}

int main()
{
    std::cout << "Hello World!\n"; 
}

// 处理收到的数据
void ProcessReceiveData()
{
	std::cout << "ProcessReceiveData" << endl;
}
// 进行一帧的游戏
void DoGameFrame()
{
	std::cout << "One Frame Game" << endl;
}

// 使用非阻塞 socket 的游戏循环
void DoGameLoop()
{
	UDPSocketPtr mySock = SocketUtil::CreateUDPSocket(INET);
	mySock->SetNonBlockingMode(true);
	char data[1500];
	SocketAddress socketAddress;

	bool gIsGameRunning = true;
	while (gIsGameRunning)
	{
		int bytesReceived = mySock->ReceiveFrom(data, sizeof(data), socketAddress);
		if (bytesReceived > 0)
		{
			ProcessReceiveData();
		}
		DoGameFrame();
	}
}