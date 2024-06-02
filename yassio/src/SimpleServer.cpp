#include <iostream>
#include "../headers/someip.h"
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
		if(msg.header.message_id )
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
			int disp_id = 10000 + msg.header.request_id;
			//std::cout << message_id << std::endl;
			if(m_deqConnections[msg.header.request_id] && m_deqConnections[msg.header.request_id]->IsConnected())
			{
				
				std::cout << "[" << client->GetID() << "] Messaged : [" << disp_id <<  "]\n";
				int receiver = msg.header.request_id;
				msg.header.request_id = client->GetID() - 10000;
				MessageClient(m_deqConnections[receiver], msg);
			}
			else
			{
				std::cout << "[Server] Client " << disp_id << " Is Unavailable\n";
			}
		}
	
		break;

		case StringMessage:
		{
			int disp_id = 10000 + msg.header.request_id;
			//std::cout << message_id << std::endl;
			if(m_deqConnections[msg.header.request_id] && m_deqConnections[msg.header.request_id]->IsConnected())
			{
				
				std::cout << "[" << client->GetID() << "] Messaged : [" << disp_id <<  "]\n";
				int receiver = msg.header.request_id;
				msg.header.request_id = client->GetID() - 10000;
				MessageClient(m_deqConnections[receiver], msg);
			}
			else
			{
				std::cout << "[Server] Client " << disp_id << " Is Unavailable\n";
			}
		}
		break;
		
		case Subscibe:
		{
			int message_id; 
			msg >> message_id; 
			int disp_id = 10000 + message_id;
			//std::cout << message_id << std::endl;
			std::cout << "[" << client->GetID() << "] Subscribed to [" << disp_id <<  "]\n";
			msg << (client->GetID() - 10000);
			MessageClient(m_deqConnections[message_id], msg);
		}
		break;

		case Pubish:
		{
			int disp_id = 10000 + msg.header.request_id;
			//std::cout << message_id << std::endl;
			if(m_deqConnections[msg.header.request_id] && m_deqConnections[msg.header.request_id]->IsConnected())
			{
				
				std::cout << "[" << client->GetID() << "] Published.\n";
				int receiver = msg.header.request_id;
				msg.header.request_id = client->GetID() - 10000;
				MessageClient(m_deqConnections[receiver], msg);
			}
			else
			{
				std::cout << "[Server] Client " << disp_id << " Is Unavailable\n";
			}

		}
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