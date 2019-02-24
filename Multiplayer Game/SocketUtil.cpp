#include "pch.h"

int SocketUtil::Select(const vector<TCPSocketPtr>* inReadSet, vector<TCPSocketPtr>* outReadSet, const vector<TCPSocketPtr>* inWriteSet, vector<TCPSocketPtr>* outWriteSet, const vector<TCPSocketPtr>* inExceptSet, vector<TCPSocketPtr>* outExceptSet)
{
	// build some set from out vectors
	fd_set read, write, except;

	fd_set *readPtr = FillSetFromVector(read, inReadSet);
	fd_set *writePtr = FillSetFromVector(write, inWriteSet);
	FD_SET* exceptPtr = FillSetFromVector(except, inExceptSet);

	int toRet = select(0, readPtr, writePtr, exceptPtr, nullptr);

	if (toRet > 0)	// toRet == 0 表示超时
	{
		FillVectorFromSet(outReadSet, inReadSet, read);
		FillVectorFromSet(outWriteSet, inWriteSet, read);
		FillVectorFromSet(outExceptSet, inExceptSet, read);
	}
	return toRet;
}

UDPSocketPtr SocketUtil::CreateUDPSocket(SocketAddressFamily inFamily)
{
	SOCKET s = socket(inFamily, SOCK_DGRAM, IPPROTO_UDP);

	if (s != INVALID_SOCKET)
	{
		return UDPSocketPtr(new UDPSocket(s));
	}
	else
	{
		ReportError("SocketUtil::CreateUDPSocket");
		return nullptr;
	}
}

TCPSocketPtr SocketUtil::CreateTCPSocket(SocketAddressFamily inFamily)
{
	SOCKET s = socket(inFamily, SOCK_STREAM, IPPROTO_TCP);

	if (s != INVALID_SOCKET)
	{
		return TCPSocketPtr(new TCPSocket(s));
	}
	else
	{
		ReportError("SocketUtil::CreateTCPSocket");
		return nullptr;
	}
}

inline fd_set * SocketUtil::FillSetFromVector(fd_set & outSet, const vector<TCPSocketPtr>* inSockets)
{
	if (inSockets)
	{
		FD_ZERO(&outSet);
		for (const TCPSocketPtr& socket : *inSockets)
		{
			FD_SET(socket->mSocket, &outSet);
		}
		return &outSet;
	}
	else
	{
		return nullptr;
	}
}

// 如果 inSockets 中的某个 socket 在 inSet 中，那么将会被加入到 outSockets 中被返回
void SocketUtil::FillVectorFromSet(vector< TCPSocketPtr >* outSockets, const vector< TCPSocketPtr >* inSockets, const fd_set& inSet)
{
	if (inSockets && outSockets)
	{
		outSockets->clear();
		for (const TCPSocketPtr& socket : *inSockets)
		{
			if (FD_ISSET(socket->mSocket, &inSet))
			{
				outSockets->push_back(socket);
			}
		}
	}
}

