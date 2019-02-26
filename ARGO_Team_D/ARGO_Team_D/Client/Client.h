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

	virtual bool init();
	virtual bool Send(Packet * p);
	virtual Packet * Receive();
	virtual void close();

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
protected:
	SOCKET m_sock;
	int m_networkId = 0;
	bool m_host = false;
	Packet * m_packet;
	sockaddr_in m_hint;
};

#endif // !CLIENT
