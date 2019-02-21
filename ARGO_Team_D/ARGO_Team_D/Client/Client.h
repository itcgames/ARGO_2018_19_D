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

	bool init(const std::string ip, const int port);
	bool Send(Packet * p);
	Packet * Receive();
	void close();

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
private:
	SOCKET sock;
	int m_networkId = 0;
	bool m_host = false;
	char buf[4096];
	Packet * m_packet;
};

#endif // !CLIENT
