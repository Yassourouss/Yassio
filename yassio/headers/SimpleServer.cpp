#include <iostream>
#include "someip.h"
#include <sstream>

class CustomServer : public someip::net::server_interface<int8_t>
{
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
		switch (msg.header.message_id)
		{
		case ServerPing:
		{
			std::cout << "[" << client->GetID() << "]: Server Ping\n";

			// Simply bounce message back to client
			client->Send(msg);
		}
		break;

		case AllMessage:
		{
			std::cout << "[" << client->GetID() << "]: Message All\n";

			// Construct a new message and send it to all clients
			someip::net::message msg;
			msg.header.message_id = ServerMessage;
			msg << client->GetID();
			MessageAllClients(msg, client);

		}
		break;

		case ServerMessage:
		{	
			int message_id; 
			msg >> message_id; 
			int disp_id = 10000 + message_id;
			std::cout << message_id << std::endl;
			std::cout << "[" << client->GetID() << "] Messaged : [" << disp_id <<  "]\n";
			MessageClient(m_deqConnections[message_id], msg);
		}
	
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