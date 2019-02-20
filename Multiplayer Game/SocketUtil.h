#pragma once

enum SocketAddressFamily
{
	INET = AF_INET,
	INET6 = AF_INET6,
};

class TCPSocket;
class UDPSocket;

class SocketUtil
{
public:
	SocketUtil();
	~SocketUtil();

	static bool			StaticInit();
	static void			CleanUp();

	static void			ReportError(const char* inOperationDesc);
	static int			GetLastError();
	static int			Select(const vector<TCPSocket>* inReadSet,
								vector<TCPSocketPtr>* outReadSet,
								const vector<TCPSocketPtr>* inWriteSet,
								vector<TCPSocketPtr>* outWriteSet,
								const vector<TCPSocketPtr>* inExceptSet,
								vector<TCPSocketPtr>* outExceptSet);

	static UDPSocketPtr CreateUDPSocket(SocketAddressFamily inFamily)
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
	static TCPSocketPtr CreateTCPSocket(SocketAddressFamily inFamily);

private:
	inline static fd_set* FillSetFromVector(fd_set& outSet, const vector<TCPSocket>* inSockets, int& ioNaxNfds);
	inline static void FillVectorFromSet(vector<TCPSocketPtr>* outSockets, const vector<TCPSocketPtr>* inSockets, const fd_set& inSet);
};