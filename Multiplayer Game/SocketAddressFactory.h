#pragma once

class SocketAddressFactory
{
public:
	static SockedAddressPtr CreateIPv4FromString(const std::string& inString);
};
