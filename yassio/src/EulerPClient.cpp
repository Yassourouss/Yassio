#include <iostream>
#include "../headers/someip.h"
#include "../headers/EulerTool/EulerRotationMatric.cpp"

#define service_id 0xEEFF

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
        msg.header.message_id = msg.header.message_id | (service_id << 16);
        msg.header.message_id = msg.header.message_id | (0x10);
        msg.header.message_id = msg.header.message_id | (0x01 << 17);
        std::string name = "Euler Pitch";
        msg << name;
        Send(msg);
    }
    void show_services()
    {
        someip::net::message msg;
        msg.header.message_type = SHOW_AVAILABLE;
        msg.header.message_id = msg.header.message_id | (0x01 << 17);
        Send(msg);
    }
    void request_service()
    {
        someip::net::message msg;
        msg.header.message_type = REQUEST_SERVICE;
        msg.header.message_id = msg.header.message_id | (0x01 << 17);
        msg.header.message_id = msg.header.message_id | (service_id << 16);
        msg.header.message_id = msg.header.message_id | (0x10);
        double rotation[4][4]= {
        {42, 17, 56, 81},
        {34, 90, 12, 68},
        {75, 29, 83, 21},
        {57, 48, 95, 13}
    };
        double angle = 13;
        msg << rotation << angle;
        Send(msg);
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
                        double rotation[4][4];
                        double angle;
                        msg >> angle >> rotation;
                        Pitch(angle,rotation);
                        msg << rotation;
                        msg.header.message_type = RESPONSE_SERVICE;
                        c.Send_message(msg);
                    }
                    break;

                    case RESPONSE_SERVICE:
                    {
                        double response[4][4];
                        msg >> response;
                        std::cout <<"La reponse recu : \n";
                        printMatrix(response);
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
                c.request_service();
                std::cout << "Requested\n";
            }
            break;
        }
    }
    bgThread.join();
    return 0;
}