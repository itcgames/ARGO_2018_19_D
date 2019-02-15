#include "NetworkingSystem.h"

NetworkingSystem::NetworkingSystem()
{
}

void NetworkingSystem::initClientLocalClient()
{
	if (m_client.init()) {
		std::cout << "Client Created" << std::endl;
	}
	else {
		std::cout << "Couldnt Connect Client                                                |" << std::endl;
		std::cout << "-----------------------------------------------------------------------" << std::endl;
	}

	parseNetworkData(m_client.processMessage(m_client.Receive()));
}

void NetworkingSystem::updateFromHost()
{
	// Update everything from here
	parseNetworkDataStr(m_client.processMessageStr(m_client.Receive()));
}

void NetworkingSystem::updateClients()
{
	// Update client entities from here
	parseNetworkDataStr(m_client.processMessageStr(m_client.Receive()));
}

void NetworkingSystem::sendToHost()
{
	std::string msg;
	cin >> msg;
	msg = "Client Says: " + msg;

	//  send own entity back
	m_client.Send(msg);
}

void NetworkingSystem::sendToClients()
{
	std::string msg;
	cin >> msg;
	msg = "Host Says: " + msg;

	// Send EVERYTHING BACK
	m_client.Send(msg);
}

void NetworkingSystem::parseNetworkData(std::map<std::string, int> parsedMessage)
{
	for (auto const& pair : parsedMessage) {

		auto key = pair.first;
		auto value = pair.second;

		if (key == "ID") {
			m_client.setID(value);
		}

		if (key == "Host") {
			m_client.setHost(value);
		}
	}
}

void NetworkingSystem::parseNetworkDataStr(std::map<std::string, std::string> parsedMessage)
{
	for (auto const& pair : parsedMessage) {

		auto key = pair.first;
		auto value = pair.second;

		if (key == "Host Says") {
			cout << value << endl;
		}


		if (key == "Client Says") {
			cout << value << endl;
		}
	}
}
