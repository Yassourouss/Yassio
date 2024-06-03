#include <iostream>
#include "../headers/someip.h"

#define service_id 0xfefe

class CustomClient : public someip::net::client_interface<int8_t>
{
public:
    void Send_message(someip::net::message msg)
    {
        Send(msg);
    }
    void offer_service()
    {
        someip::net::message msg;
        msg.header.message_type = OFFER_SERVICE;
        msg.header.message_id = msg.header.message_id | (service_id<< 16);
        msg.header.message_id = msg.header.message_id | (8100);
        msg.header.message_id = msg.header.message_id | (0x01 << 17);
        std::string name = "Hello";
        msg << name;
        Send(msg);
    }
    void show_services()
    {
        someip::net::message msg;
        msg.header.message_type = SHOW_AVAILABLE;
        msg.header.message_id = msg.header.message_id | (0x01 << 17);
        msg << 19;
        Send(msg);
    }
    void request_service(uint16_t instance_id)
    {
        someip::net::message msg;
        msg.header.message_type = REQUEST_SERVICE;
        msg.header.message_id = msg.header.message_id | (0x01 << 17);
        msg.header.message_id = msg.header.message_id | (service_id<< 16);
        msg.header.message_id = msg.header.message_id | (8100);
        std::string word = "Yassir";
        msg << word;
        Send(msg);
    }

    void SendMessage(int receiver, int message)
    {
        someip::net::message msg;
        msg.header.message_id = ServerMessage;
		msg.header.request_id = receiver;
        msg << message;
        Send(msg);
    }

    void MessageAll(int mess)
	{
		someip::net::message msg;
		msg.header.message_id = AllMessage;
		msg << mess;		
		Send(msg);
	}

    void Subscribe(int id)
	{
		someip::net::message msg;
        msg.header.message_id = msg.header.message_id | (0x01 << 17);
        msg.header.message_type = SUBSCRIBE;
        msg.header.request_id = id;
		Send(msg);
	}
	void Add_Sub(int id)
	{
		subscribers.push_back(id);
	}

	void Publish(int message)
	{
		someip::net::message msg;
        //msg.header.message_id = msg.header.message_id | (0x01 << 17);
		/*msg.header.message_id = Pubish;
		msg << 0xEE;*/
		for (int rec : subscribers)
		{
			SendMessage(rec, message);
		}
	}

    std::string Hello(std::string word)
    {
        return "Hello " + word;
    } 


	private:
	std::vector<int> subscribers;

};

int main()
{
	CustomClient c;
	c.Connect("127.0.0.1", 60000);
    auto backgroundThread = [&]() {
		while (true)
	{   
    		if (c.IsConnected())
		{
			if (!c.Incoming().empty())
			{
				auto msg = c.Incoming().pop_front().msg;
                uint16_t instance_id = (msg.header.message_id & 0x7FFF);
                if((msg.header.message_id >> 17 & 0x1))
                {
                switch(msg.header.message_type)
                    {
                    case REQUEST_SERVICE:
                    {
                        std::string p; 
                        msg >> p;
                        p = c.Hello(p);
                        msg << p;
                        msg.header.message_type = RESPONSE_SERVICE;
                        c.Send_message(msg);
                    }
                    break;

                    case RESPONSE_SERVICE:
                    {
                        std::string response;
                        msg >> response;
                        std::cout <<"La reponse recu : "  << response << std::endl;
                    }
                    break;

                    case AVAILABILITY:
                    {
                        bool response; 
                        msg >> response;
                        if(response)
                            std::cout <<"Service dispo :D\n"; 
                        else
                            std::cout << "Service non dispo :(\n";
                    }
                    case SUBSCRIBE:
                    {
                        int sub_id = msg.header.request_id;
                        c.Add_Sub(sub_id);
                        std::cout << "[Client] New subscription from [" << sub_id << "]\n";
                    }
                    default:
                    break;  
                    }
                }
                else
                {
                    switch (msg.header.message_id)
                    {
                    case ServerAccept:
                    {
                        // Server has responded to a ping request				
                        std::cout << "Server Accepted Connection\n";
                    }
                    break;


                    case ServerPing:
                    {
                        // Server has responded to a ping request
                        std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
                        std::chrono::system_clock::time_point timeThen;
                        msg >> timeThen;
                        std::cout << "Ping: " << std::chrono::duration<double>(timeNow - timeThen).count() << "\n";
                    }
                    break;

                    case ServerMessage:
                    {
                        // Server has responded to a ping request	
                        int message;
                        msg >> message;
                        std::cout << "Client [" << msg.header.request_id << "] sent :" << message << "\n";
                    }
                    break;
                    
                    default:
                    break;

                    }
                }
            }
        }
    
    }};
    std::thread bgThread(backgroundThread);
    std::cout << "Welcome to Euler Yaw : \n";
    std::cout << "[1] OFFER SERVICE\n" << "[2] SHOW SERVICES\n" << "[3] REQUEST SERVICE\n" << "input your choice : \n";
    while(true)
    {
        
        int input;
        std::cin >> input;
        switch(input){
            case 1: 
            {
                c.offer_service();
            }
            break;
            case 2:
            {
                c.show_services();
            }
            break;
            case 3:
            {   std::cout << "Enter the instance id : ";
                int instance_id;
                std::cin >> instance_id;
                c.request_service(instance_id);
                std::cout << "\nRequested\n";
            }
            break;

            case 4:			
            {
				int rec;
				int message;
				std::cout << "Enter the receiver and then the message : \n"; 
				std::cin >> rec >> message;
				c.SendMessage(rec,message);
			}
            break;
            case 5:
            {
                int message;
                std::cout << "Enter the message to broadcast : ";
                std::cin >> message;
                c.MessageAll(message);
            }
            break;

            case 6: 
            {
                int id;
                std::cin >> id; 
                c.Subscribe(id);
            }
            break;

            case 7:
            {
                int message;
                std::cout << "Enter the message to publish : ";
                std::cin >> message;
                c.Publish(message);
            }

        }
    }
    bgThread.join();
    return 0;
}