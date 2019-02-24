/*
�������ӵĲ���
1 ����һ�� socket
2 �󶨵�ָ���˿�
3 �����������������
*/
#include "pch.h"

TCPSocket::~TCPSocket()
{
}

//--------------------------------- ������������
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

//--------------------------------- ������������

// inBckLog : �������������������ﵽ���ֵ�󣬺������Ӷ��ᱻ����
int TCPSocket::Listen(int inBackLog)
{
	int err = listen(mSocket, inBackLog);									// 3.1��������
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
	SOCKET newSocket = accept(mSocket, &inFromAddress.mSockAddr, &length);	// 3.0���մ�������Ӳ����� tcp ���ֹ���

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

// ���ݷ���(ֻ�ǽ�����д�� socket ������������� socket ��������������ĳһʱ�̷��ͳ�ȥ)
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

// ���ݽ���
int TCPSocket::Receive(void * inBuffer, int inLen)
{
	int bytesReceiveCount = recv(mSocket, static_cast<char*>(inBuffer), inLen, 0);		// �� len ��0������������0����ʾ�յ�һ�� FIN ���ݰ���Ӧ�öϿ�������
	if (bytesReceiveCount < 0)
	{
		SocketUtil::ReportError("TCPSocket::Receive");
		return -SocketUtil::GetLastError();
	}
	return bytesReceiveCount;
}
