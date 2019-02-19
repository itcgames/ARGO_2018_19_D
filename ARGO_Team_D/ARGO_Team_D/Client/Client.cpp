#include "Client.h"
#include "ParseUtils.h"
#include <iostream>
#include "../Utils/Packet.h"

Client::Client()
{
}

Client::~Client()
{
}

bool Client::init()
{

	std::string ipAddress = "149.153.106.150";			// IP Address of the server
	int port = 8080;

	sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock == INVALID_SOCKET)
	{
		std::cerr << "Can't create socket, Err #" << WSAGetLastError() << std::endl;
		WSACleanup();
		return false;
	}

	u_long iMode = 1;
	int result = ioctlsocket(sock, FIONBIO, &iMode);
	if (result != NO_ERROR) {
		std::cout << "ioctlsocket failed with error: " << result << std::endl;
		return false;
	}

	// Fill in a hint structure
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	// Connect to server
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		std::cout << "-----------------------------------------------------------------------" << std::endl;
		std::cerr << "Can't create socket, Err #" << WSAGetLastError() << std::endl;
		std::cout << "Non fatal error apparently just gonna use the the socket anyway :/    |" << std::endl;
		std::cout << "vvvvv Dont mind this vvvvv                                            |" << std::endl;
		return false;
	}
	return true;
}

void Client::Send(std::string userInput)
{
	//if (userInput.size() > 0)		// Make sure the user has typed in something
	//{
	//	// Send the text
	//	int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
	//}
	Packet * p = new Packet();
	p->message = userInput.size() != 0 ? userInput : "";
	p->playerID = 10;
	int sendResult = send(sock, (char*)p, sizeof(struct Packet), 0);
}

vector<std::string> Client::Receive()
{
	ZeroMemory(buf, 4096);
	int bytesReceived = recv(sock, buf, 4096 , 0);
	std::vector<std::string> items;
	if (bytesReceived > 0)
	{
		items = pu::Split(std::string(buf, 0, bytesReceived), ',');
	}
	return items;
}

void Client::close()
{
	closesocket(sock);
	WSACleanup();
}

map<std::string, int> Client::processMessage(std::vector<std::string> items)
{
	int intV;
	std::string stringV;
	map<std::string, int>  values;

	if (items.size() != 0) {
		for (std::string parsed : items) {
			std::stringstream ss(parsed);

			ss >> stringV;
			stringV.pop_back();

			if (ss >> intV && stringV != "") {
				values.insert(std::make_pair(stringV, intV));
			}
			else {
				std::cout << "Error: Unknown value" << std::endl;
			}
		}
	}
	return values;
}

map<std::string, std::string> Client::processMessageStr(std::vector<std::string> items)
{
	std::string intV;
	std::string stringV;
	map<std::string, std::string>  values;

	if (items.size() != 0) {
		for (std::string parsed : items) {
			std::stringstream ss(parsed);

			ss >> stringV;
			stringV.pop_back();

			if (ss >> intV && stringV != "") {
				values.insert(std::make_pair(stringV, intV));
			}
			else {
				std::cout << "Error: Unknown value" << std::endl;
			}
		}
	}
	return values;
}
