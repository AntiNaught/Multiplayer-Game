#include "pch.h"
#include "Server.h"

Server::Server()
{
}

Server::~Server()
{
}

void Server::DoTCPLoop()
{
	TCPSocketPtr listenSocket = SocketUtil::CreateTCPSocket(INET);
	SocketAddress receivingAddress(INADDR_ANY, 48000);
	if (listenSocket->Bind(receivingAddress) != NO_ERROR)
	{
		return;
	}
	vector<TCPSocketPtr> readBlockSockets;

	readBlockSockets.push_back(listenSocket);

	vector<TCPSocketPtr> readableSockets;

	while (gIsGameRunning)
	{
		if (SocketUtil::Select(&readBlockSockets, &readableSockets, nullptr, nullptr, nullptr, nullptr))
		{
			// we got a packet-loop through the set ones
			for (const TCPSocketPtr& socket : readableSockets)
			{
				if (socket == listenSocket)
				{
					// it's the listen socket, accept a new connection
					SocketAddress newClientAddress;
					TCPSocketPtr newSocket = listenSocket->Accepet(newClientAddress);
					readBlockSockets.push_back(newSocket);
					ProcessNewClient(newSocket, newClientAddress);
				}
				else
				{
					//it's a regular socket-process tha 
					char segment[1500];
					int dataReceived = socket->Receive(segment, 1500);
					if (dataReceived > 0)
					{
						ProcessDataFromClient(socket, segment, dataReceived);
					}
				}
			}
		}
	}
}

void Server::ProcessNewClient(TCPSocketPtr socket, SocketAddress address)
{
	throw std::exception("Non Implement -> Server::ProcessNewClient");
}

void Server::ProcessDataFromClient(TCPSocketPtr socket, char * data, int dataLen)
{
	throw std::exception("Non Implement -> Server::ProcessDataFromClient");
}
