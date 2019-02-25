#include "TCPServer.h"
#include <iostream>

int main() {
	// Loop forever

	TCPServer * server = new TCPServer();
	if (server->winSockInit()) {
		if (server->createSock()) {
			if (server->bindSock()) {
				while (true) {
					server->update();
				}
			}
		}
	}
	server->closeSock();
	return 0;
}