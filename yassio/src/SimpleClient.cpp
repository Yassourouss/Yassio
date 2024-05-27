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
	
	void SendString(int receiver, std::string message)
	{
		someip::net::message msg;
        msg.header.message_id = StringMessage;
		msg.header.request_id = receiver;
        msg << message;
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

	void MessageAll()
	{
		someip::net::message msg;
		msg.header.message_id = AllMessage;
		msg << 0xFF;		
		Send(msg);
	}

	void Subscribe(int id)
	{
		someip::net::message msg;
		msg.header.message_id = Subscibe;
		msg << id;
		Send(msg);
	}
	void Add_Sub(int id)
	{
		subscribers.push_back(id);
	}

	void Publish()
	{
		someip::net::message msg;
		/*msg.header.message_id = Pubish;
		msg << 0xEE;*/
		for (int rec : subscribers)
		{
			SendMessage(rec, 0XEE);
		}

	}

	private:
	std::vector<int> subscribers;
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
					std::cout << "Client [" << msg.header.request_id << "] sent :" << clientID << "\n";
				}
				break;
				
				case Subscibe:
				{
					int sub_id;
					msg >> sub_id;
					c.Add_Sub(sub_id);
					std::cout << "[Client] New subscription from [" << sub_id << "]\n";
				}
				break;

				case StringMessage:
				{
					std::string str;
					msg >> str; 
					std::cout << str << std::endl;
				}
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
		switch((int)input)
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
				int rec;
				int message;
				std::cout << "Enter the receiver and then the message : \n"; 
				std::cin >> rec >> message;
				c.SendMessage(rec,message);
			}
			break;
			case 4:
			{
				int id;
				std::cin >> id;
				c.Subscribe(id);
			}
			break;
			case 5:
			{
				c.Publish();
			}

			case 6:
			{
				int id;
				std::cin >> id;
				std::string ss = "Hello";
				c.SendString(id, ss);
			}
			default:
			//std::cin.clear();
			
			//std::cin.ignore(INT_MAX);
			break;
    	}
	}
	bgThread.join();

	return 0;
}