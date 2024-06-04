#include <iostream>
#include "../headers/someip.h"
#include <sstream>
    struct n_mService {
    std::string name;
    uint32_t service_id;
    uint32_t instance_id;
    uint32_t port;
    uint32_t  index;
    n_mService(std::string naem, uint32_t srv, uint32_t inst, uint32_t po, uint32_t ind) :name(naem), service_id(srv), instance_id(inst), port(po), index(ind)
    {} 
    friend std::ostream& operator<<(std::ostream& os, n_mService& serv)
    {
        os <<"Service name : " << serv.name <<"\nService id : " << std::hex <<serv.service_id << "\nInstance id : " << std::dec << serv.instance_id << "\nPort : " << serv.port << std::endl;
        return os;
    }
};


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
		msg.header.message_type = ServerAccept;
		client->Send(msg);
		return true;
	}
    	
    virtual void OnClientDisconnect(std::shared_ptr<someip::net::connection<int8_t>> client)
	{
		std::cout << "Removing client [" << client->GetID() << "]\n";
	}

    virtual void OnMessage(std::shared_ptr<someip::net::connection<int8_t>> client, someip::net::message& msg)
	{
		if((msg.header.message_id >> 17 & 0x1)) // if true then the message is of type SOME-IP/SD 
        {
            switch (msg.header.message_type)
            {
            case OFFER_SERVICE:     
            {
                std::cout << "[" << client->GetID() << "] Offered a service\n";
                uint16_t service_id = (msg.header.message_id >> 16) & (0xFFFF);
                uint16_t instance_id = (msg.header.message_id & 0x7FFF);
                int port = client->GetPort();
                int index = (client->GetID() - 10000);
                std::string name;
                msg >> name;
                n_mService service(name, service_id, instance_id, port, index);
                services.insert({instance_id, service});
            }
                break;

            case AVAILABILITY:
            {
                uint16_t service_id = (msg.header.message_id >> 16) & (0xFFFF);
                uint16_t instance_id = (msg.header.message_id & 0x7FFF);
                std::map<int, n_mService>::iterator it = services.begin();
                while (it != services.end())
                {   
                        if(instance_id == it->first){
                        msg << true;
                        client->Send(msg);
                        break;
                    }
                    it++;
                }
                msg << false;
                client->Send(msg);
                }
            break;

            case REQUEST_SERVICE:
            {
                //std::cout << "Receivde this mmmm";
                int id; 
                uint16_t service_id = (msg.header.message_id >> 16) & (0xFFFF);
                uint16_t instance_id = (msg.header.message_id & 0x7FFF);
                std::map<int, n_mService>::iterator it = services.begin();
                while (it != services.end())
                {
                    if(instance_id == it->first){
                        id = it->second.index;
                        break;
                    }
                    ++it;
                }
                std::cout << "[" << client->GetID() << "] requested a service from [" << id + 10000 <<"]\n";
                msg.header.request_id = client->GetID();
                MessageClient(m_deqConnections[id], msg);
                
            }
                break;

            case RESPONSE_SERVICE:
            {
                int id = msg.header.request_id;
                id = id - 10000;
                m_deqConnections[id]->Send(msg);
                std::cout << "[" << client->GetID() << "] responded to [" << id + 10000 <<"]\n";
            }
                break;

            case SHOW_AVAILABLE:
            {
                std::cout << "[" << client->GetID() << "] requests to show available services : \n";
                std::map<int, n_mService>::iterator it = services.begin();
                while (it != services.end())
                {
                    std::cout << it->second << std::endl;
                    ++it; 
                    }
            }
            break;

            case SUBSCRIBE:
            {
                std::cout << "[" << client->GetID() << "] subscribed to  : [" << msg.header.request_id << "]\n";
                int id = msg.header.request_id;
                msg.header.request_id = client->GetID();
                //m_deqConnections[id]->Send(msg);
                for(auto c : m_deqConnections)
                {
                    std::cout << c->GetID();
                    if (c->GetID() == id)
                    {
                        MessageClient(c, msg);
                        break;
                    }
                }
            }
            break;

            default:
                break;
            }
        }
        else
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
                msg.header.message_id = ServerMessage;
                msg.header.request_id = client->GetID();
                MessageAllClients(msg, client);

            }
            break;

            case ServerMessage:
            {	
                int disp_id = msg.header.request_id;
                int real_id = disp_id - 10000;
                //std::cout << message_id << std::endl;
                if(m_deqConnections[real_id] && m_deqConnections[real_id]->IsConnected())
                {
                    
                    std::cout << "[" << client->GetID() << "] Messaged : [" << disp_id <<  "]\n";
                    int receiver = real_id;
                    msg.header.request_id = client->GetID();
                    MessageClient(m_deqConnections[receiver], msg);
                }
                else
                {
                    std::cout << "[Server] Client " << disp_id << " Is Unavailable\n";
                }
            }
        
            break;

            default:
            break;
            }
        }
    }


    private: 
    std::map<int, n_mService> services;

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