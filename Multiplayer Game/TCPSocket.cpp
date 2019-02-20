#include "pch.h"

TCPSocket::~TCPSocket()
{
}

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

int TCPSocket::Listen(int inBackLog)
{
	int err = listen(mSocket, inBackLog);
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
	SOCKET newSocket = accept(mSocket, &inFromAddress.mSockAddr, &length);

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

int TCPSocket::Send(void * inData, int inLen)
{
	int bytesReceiveCount = recv(mSocket, static_cast<char*>(inData), inLen, 0);

	if (bytesReceiveCount < 0)
	{
		SocketUtil::ReportError("TCPSocket::Send");
		return -SocketUtil::GetLastError();
	}
	return bytesReceiveCount;
}
