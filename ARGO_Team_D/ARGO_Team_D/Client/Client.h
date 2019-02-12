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
	void setID(int newId) { m_networkId = newId; }
	int getNetworkId() { return m_networkId; }

	void close();

private:
	SOCKET sock;
	int m_networkId = 0;
	char buf[4096];
};

#endif // !CLIENT