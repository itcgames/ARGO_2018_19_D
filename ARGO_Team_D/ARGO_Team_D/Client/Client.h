#ifndef CLIENT
#define CLIENT

#include <WS2tcpip.h>
#include <vector>
#include <map>
#include "../Utils/Packet.h"

using namespace std;

class Client {
public:
	Client();
	~Client();

	bool init();

	void Send(Packet * p);
	Packet *  Receive();
	map<std::string, int> processMessage(std::vector<std::string> items);
	map<std::string, std::string> processMessageStr(std::vector<std::string> items);
	void setID(int newId) { m_networkId = newId; }
	void setHost(int host) {
		if (host == 1) { 
			m_host = true;
		}
		else {
			m_host = false; 
		}
	}

	int getNetworkId() { return m_networkId; }
	bool getHost() { return m_host; }

	void close();

private:
	SOCKET sock;
	int m_networkId = 0;
	bool m_host = false;
	char buf[4096];
	Packet * m_packet;
};

#endif // !CLIENT
