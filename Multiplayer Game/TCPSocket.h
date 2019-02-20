#pragma once

class TCPSocket
{
public:
	~TCPSocket();
	int								Connect(const SocketAddress& inAddress);
	int								Bind(const SocketAddress& inToAddress);
	int								Listen(int inBackLog = 32);
	shared_ptr<TCPSocket>			Accepet(SocketAddress& inFromAddress);
	int								Send(void* inData, int inLen);
	int								Receive(void* inBuffer, int inLen);
private:
	friend class SocketUtil;
	TCPSocket(SOCKET inSocket) : mSocket(inSocket) {}

	SOCKET mSocket;
};

typedef shared_ptr<TCPSocket> TCPSocketPtr;