#include <iostream>
#include "../headers/someip.h"


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
        msg.header.message_id = msg.header.message_id | (0xFEFE << 16);
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
    void request_service(uint16_t service_id, uint16_t instance_id)
    {
        someip::net::message msg;
        msg.header.message_type = REQUEST_SERVICE;
        msg.header.message_id = msg.header.message_id | (0x01 << 17);
        msg.header.message_id = msg.header.message_id | (0xFEFE << 16);
        msg.header.message_id = msg.header.message_id | (8100);
        std::string word = "Yassir";
        msg << word;
        Send(msg);
    }

    std::string Hello(std::string word)
    {
        return "Hello " + word;
    } 

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
                    default:
                    break;  
                }
            }
        }
    }
    };
    std::thread bgThread(backgroundThread);
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
            {
                c.request_service(0xFEFE, 8100);
                std::cout << "Requested\n";
            }
            break;
        }
    }
    bgThread.join();
    return 0;
}