#pragma once
class Server
{
public:
	Server();
	~Server();

	void DoTCPLoop();
private:
	bool gIsGameRunning = true;
	const int GOOD_SOCKET_SIZE = 30;
	void ProcessNewClient(TCPSocketPtr socket, SocketAddress address);
	void ProcessDataFromClient(TCPSocketPtr socket, char* data, int dataLen);
};