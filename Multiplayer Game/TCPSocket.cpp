/*
建立连接的步骤
1 创建一个 socket
2 绑定到指定端口
3 监听传入的连接请求
*/
#include "pch.h"

TCPSocket::~TCPSocket()
{
}

//--------------------------------- 主动发起连接
int TCPSocket::Connect(const SocketAddress & inAddress)
{
	int err = connect(mSocket, &inAddress.mSockAddr, inAddress.GetSize());
	if (err < 0)
	{
		SocketUtil::ReportError("TCPSocket::Connect");
		return -SocketUtil::GetLastError();
	}
	return NO_ERROR;
}

int TCPSocket::Bind(const SocketAddress & inToAddress)
{
	return 0;
}

//--------------------------------- 被动建立连接

// inBckLog : 允许传入的最大连接数，达到最大值后，后续连接都会被丢弃
int TCPSocket::Listen(int inBackLog)
{
	int err = listen(mSocket, inBackLog);									// 3.1启动监听
	if (err < 0)
	{
		SocketUtil::ReportError("TCPSocket::Listen");
		return -SocketUtil::GetLastError();
	}
	return NO_ERROR;
}

TCPSocketPtr TCPSocket::Accepet(SocketAddress& inFromAddress)
{
	int length = inFromAddress.GetSize();
	SOCKET newSocket = accept(mSocket, &inFromAddress.mSockAddr, &length);	// 3.0接收传入的连接并继续 tcp 握手过程

	if (newSocket != INVALID_SOCKET)
	{
		return TCPSocketPtr(new TCPSocket(newSocket));
	}
	else
	{
		SocketUtil::ReportError("TCPSocket::Accepet");
		return nullptr;
	}
}

// 数据发送(只是将数据写入 socket 的输出缓冲区， socket 库来决定将来的某一时刻发送出去)
int TCPSocket::Send(void * inData, int inLen)
{
	int bytesSentCount = send(mSocket, static_cast<char*>(inData), inLen, 0);
	if (bytesSentCount < 0)
	{
		SocketUtil::ReportError("TCPSocket::Send");
		return -SocketUtil::GetLastError();
	}
	return bytesSentCount;
}

// 数据接收
int TCPSocket::Receive(void * inBuffer, int inLen)
{
	int bytesReceiveCount = recv(mSocket, static_cast<char*>(inBuffer), inLen, 0);		// 当 len 非0，而函数返回0，表示收到一个 FIN 数据包，应该断开连接了
	if (bytesReceiveCount < 0)
	{
		SocketUtil::ReportError("TCPSocket::Receive");
		return -SocketUtil::GetLastError();
	}
	return bytesReceiveCount;
}
