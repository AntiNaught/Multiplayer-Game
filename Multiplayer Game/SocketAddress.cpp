#include "pch.h"

sockaddr_in * SocketAddress::GetAsSockAddrIn()
{
	return reinterpret_cast<sockaddr_in*>(&mSockAddr);
}

SocketAddress::SocketAddress(uint32_t inAddress, uint16_t inPort)
{
	GetAsSockAddrIn()->sin_family = AF_INET;
	GetAsSockAddrIn()->sin_port = htons(inPort);
	GetAsSockAddrIn()->sin_addr.S_un.S_addr = htonl(inAddress);
}

SocketAddress::SocketAddress(const sockaddr & inSockAddr)
{
	memcpy(&mSockAddr, &inSockAddr, sizeof(inSockAddr));
}

SocketAddress::SocketAddress(std::string addrStr, uint16_t inPort)
{
	sockaddr_in myAddr;
	myAddr.sin_family = AF_INET;
	myAddr.sin_port = inPort;
	//InetPton(AF_INET, "65.254.248.180", &myAddr.sin_addr);
}
