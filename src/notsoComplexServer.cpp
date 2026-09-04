#include <iostream>
#include "../headers/someip.h"
#include <sstream>

class CustomServer : public someip::net::server_interface<int8_t>
{
private:
std::map<int , int> services;
public:
	CustomServer(uint16_t nPort) : someip::net::server_interface<int8_t>(nPort)
	{
	}

protected:
	virtual bool OnClientConnect(std::shared_ptr<someip::net::connection<int8_t>> client)
	{
		someip::net::message msg;
		msg.header.message_id = ServerAccept;
		client->Send(msg);
		return true;
	}

	// Called when a client appears to have disconnected
	virtual void OnClientDisconnect(std::shared_ptr<someip::net::connection<int8_t>> client)
	{
		std::cout << "Removing client [" << client->GetID() << "]\n";
	}

	// Called when a message arrives
	virtual void OnMessage(std::shared_ptr<someip::net::connection<int8_t>> client, someip::net::message& msg)
	{
        switch (msg.header.message_type)
        {
            case OFFER_SERVICE:
            {   std::cout << "[" << client->GetID() << "] offered a service \n";
                uint16_t service_id = (msg.header.message_id >> 16) & (0xFFFF);
                uint16_t instance_id = (msg.header.message_id & 0x7FFF);
                services[service_id] = client->GetID() - 10000;
            }
            break;
            case REQUEST_SERVICE:
            {
				m_deqConnections[0]->Send(msg);
            }
            break;
            case RESPONSE_SERVICE:
            std::cout << "Yassir is fucking gay" << std::endl;
            break;
            case AVAILABILITY:
            break;
            case SHOW_AVAILABLE:
            {
                std::cout << "[" << client->GetID() << "] requests to show available\n";
                std::map<int, int>::iterator it = services.begin();
                while (it != services.end())
                {
                    std::cout <<"service ID : " << it->first << "Client ID :" << it->second + 10000 << std::endl;
                    ++it; 
                    }
            }
            break;
            default:
            break;
        }
    }
};


int main()
{
	CustomServer server(60000); 
	server.Start();
    auto backgroundThread = [&]() {
	while (1)
	{
		server.Update(-1, true);
	}
};	

std::thread bgThread(backgroundThread);
bgThread.join();
	
	return 0;
}