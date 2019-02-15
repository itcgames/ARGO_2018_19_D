#ifndef CLIENT
#define CLIENT

#include <WS2tcpip.h>
#include <vector>
#include <map>

using namespace std;

class Client {
public:
	Client();
	~Client();

	bool init();

	void Send(std::string userInput);
	vector<std::string> Receive();
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
};

#endif // !CLIENT
