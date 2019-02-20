#pragma once
class SocketAddress
{
private:
	friend class UDPSocket;
	friend class TCPSocket;

	sockaddr mSockAddr;

	sockaddr_in* GetAsSockAddrIn();

	size_t GetSize() const { return sizeof(sockaddr); }
protected:

public:
	// ipv4
	SocketAddress(uint32_t inAddress, uint16_t inPort);
	SocketAddress(const sockaddr& inSockAddr);
	SocketAddress(std::string addrStr, uint16_t inPort);
};

// π≤œÌ÷∏’Î
typedef std::shared_ptr<SocketAddress> SockedAddressPtr;
