#include "TCPServer.h"
#include "UDPServer.h"
#include <iostream>

int main() {
	// Loop forever

	/*TCPServer * server = new TCPServer();
	if (server->winSockInit()) {
		if (server->createSock()) {
			if (server->bindSock()) {
				while (true) {
					server->update();
				}
			}
		}
	}
	server->closeSock();*/
	UDPServer * server = new UDPServer();
	if (server->winSockInit()) {
		if (server->createSock()) {
			if (server->bindSock()) {
				server->messageHandler();
			}
		}
	}
	return 0;
}