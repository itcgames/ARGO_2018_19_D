#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include "Client.h"
#include "../Utils/Packet.h"

class UDPClient : public Client {
public:
	UDPClient();
	~UDPClient();
	bool init() override;
	bool Send(Packet * p) override;
	Packet * Receive() override;
};

#endif //!UDPCLIENT_H