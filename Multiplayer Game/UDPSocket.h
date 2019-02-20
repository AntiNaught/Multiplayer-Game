#pragma once

class UDPSocket
{
public:
	~UDPSocket();

	int Bind(const SocketAddress& inBindAddress);
	int SendTo(const void* inData, int inLen, const SocketAddress& inToAddress);
	int ReceiveFrom(void* inBuffer, int inLen, SocketAddress& outFrom);

	// ����������ģʽ
	int SetNonBlockingMode(bool inShouldBeNonBlocking);
private:
	friend class SocketUtil;
	UDPSocket(SOCKET inSocket) : mSocket(inSocket) {}
	SOCKET mSocket;
};

typedef shared_ptr<UDPSocket> UDPSocketPtr;