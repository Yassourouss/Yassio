#include <iostream>
#include "someip.h"


class CustomClient : public someip::net::client_interface<int8_t>
{
public:
	void PingServer()	
	{
		someip::net::message msg;
		msg.header.message_id = ServerPing;

		// Caution with this...
		std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();		

		msg << timeNow;
		Send(msg);
	}

    void SendMessage()
    {
        someip::net::message msg;
        msg.header.message_id = ServerMessage;
        msg << 0x11;
        Send(msg);
    }

	void MessageAll()
	{
		someip::net::message msg;
		msg.header.message_id = AllMessage;		
		Send(msg);
	}
};

int main()
{
	CustomClient c;
	c.Connect("127.0.0.1", 60000);

	bool bQuit = false;

	auto backgroundThread = [&]() {
        std::cout << "Thread is running :)\n";
		while (!bQuit)
	{
    		if (c.IsConnected())
		{
			if (!c.Incoming().empty())
			{


				auto msg = c.Incoming().pop_front().msg;

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
					uint32_t clientID;
					msg >> clientID;
					std::cout << "Hello from [" << clientID << "]\n";
				}
				break;
				
				/*case ClientMessage:
				{
					char ss[] = "AAAAA";
					msg >> ss;
					std::cout << ss << std::endl;
				}*/
				}
			}
		}
		else
		{
			std::cout << "Server Down\n";
			bQuit = true;
		}
	}
	};

	std::thread bgThread(backgroundThread);
	while(true)
	{
		int input;
		std::cin >> input;
		switch(input)
		{
			case 1:
			{
				c.PingServer();
			}
			break;
			case 2:
			{
				c.MessageAll();
			}
			break;
			case 3:
			{
				c.SendMessage();
			}
    	}
	}
	bgThread.join();

	return 0;
}