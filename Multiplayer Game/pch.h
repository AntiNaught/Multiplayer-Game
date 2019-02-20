#ifndef PCH_H
#define PCH_H

#define WIN32_LEAN_AND_MEAN		//将 Windos.h 中的 Winsock 忽略

#ifdef  _WIN32
#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>			// 地址转换功能
#else
#endif //  _WIN32

#endif //PCH_H
 
#include <memory>
#include <vector>
#include <string>


using std::vector;
using std::shared_ptr;

#include "SocketUtil.h"
#include "SocketAddress.h"
#include "SocketAddressFactory.h"
#include "TCPSocket.h"
#include "UDPSocket.h"
