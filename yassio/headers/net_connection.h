#pragma once 

#include "net_common.h"
#include "net_tsqueue.h"
#include "net_message.h"
#include "IDPINGER/idpinger.cpp"

namespace someip
{
    namespace net
    {
        template<typename T>
        class server_interface;

        template <typename T>
        class connection: public std::enable_shared_from_this<connection<T>>
        {
            public :
                enum class owner
                {
                    server,
                    client
                };

            public :

			connection(owner parent, asio::io_context& asioContext, asio::ip::tcp::socket socket, tsqueue<owned_message<T>>& qIn)
				: m_asioContext(asioContext), m_socket(std::move(socket)), m_qMessagesIn(qIn)
			{
                word = selected_word();
                
                m_nHandshakeInClient = new char[word.length()+1];
                m_nHandshakeOutServer = new char[word.length()+1];
				m_nOwnerType = parent;

				// Construct validation check data
				if (m_nOwnerType == owner::server)
				{
                   /* m_nHandshakeOut = "Hello";
                    m_nHandshakeCheck = "Hello";*/
                   m_key = rand_key();
                    std::cout << "random key : " << m_key << std::endl;
                    std::string scrambled = encrypt_word(word,m_key); //m_key);
                    scrambled.copy(m_nHandshakeOutServer, word.length()+1);
                   // word.copy(m_nHandshakeOut,word.length() + 1);
                    m_nHandshakeCheck = m_key;

				}
				else
				{

				}
			}

            virtual ~connection()
            {}

            uint32_t GetID() const
            {
                return id;
            }

            public: 
                void ConnectToClient(someip::net::server_interface<T>* server,uint32_t uid = 0)
                {
                    if(m_nOwnerType == owner::server)
                    {
                        if(m_socket.is_open())
                        {
                            id = uid;
                            WriteValidation();
                            ReadValidation(server);
                        }
                    }
                }

                void ConnectToServer(const asio::ip::tcp::resolver::results_type& endpoints)
                {
                    if(m_nOwnerType == owner::client)
                    {
                        asio::async_connect(m_socket, endpoints,
                        [this](std::error_code ec, asio::ip::tcp::endpoint endpoints)
                        {
                            if(!ec)
                            {
                                ReadValidation();
                            }
                        }
                        );
                    }
                }

                void Disconnect()
                {
                    if(IsConnected())
                        asio::post(m_asioContext, [this](){m_socket.close();});
                }

                bool IsConnected() const
                {
                    return m_socket.is_open();
                }

                void StartListening()
                {

                }

                public: 
                
                void Send(const message& msg)
                {
                    asio::post(m_asioContext, 
                    [this, msg]()
                    {
                        bool bWritingMessage =!m_qMessagesOut.empty();
                        m_qMessagesOut.push_back(msg);
                        if (!bWritingMessage)
                        {
                            WriteHeader();
                        }
                    });
                }

            private:

                void WriteHeader()
                {
                    asio::async_write(m_socket, asio::buffer(&m_qMessagesOut.front().header, sizeof(message_header)),
                    [this](std::error_code ec, std::size_t length)
                    {
                        if (!ec)
                        {
                            if (m_qMessagesOut.front().body.size() > 0)
                            {
                                WriteBody();
                            }
                            else
                            {
                                m_qMessagesOut.pop_front();

                                if (!m_qMessagesOut.empty())
                                {
                                    WriteHeader();
                                }
                            }
                        }
                        else
                        {
                            std::cout << "[" << id << "] Write Header Fail.\n";
                            m_socket.close();
                        }
                    });
                }

                void WriteBody()
                {
                    asio::async_write(m_socket, asio::buffer(m_qMessagesOut.front().body.data(), m_qMessagesOut.front().body.size()),
					[this](std::error_code ec, std::size_t length) 
                    {
                        if (!ec) 
                        {
                            m_qMessagesOut.pop_front();

                            if (!m_qMessagesOut.empty())
                            {
                                WriteHeader();
                            }
                        }
                        else
                        {
                            std::cout << "[" << id << "] Write Body Fail.\n";
                            m_socket.close();
                        }
                    });
                }

                void ReadHeader()
                {
                    asio::async_read(m_socket,asio::buffer(&m_msgTemporaryIn.header, sizeof(message_header)),
                    [this](std::error_code ec, std::size_t length)
                    {
                        if (!ec)
                        {
                            if (m_msgTemporaryIn.header.length > 0)
                            {
                                m_msgTemporaryIn.body.resize(m_msgTemporaryIn.header.length);
                                ReadBody();
                            }
                            else
                            {
                                AddToIncomingMessageQueue();
                            }
                        }
                        else
                        {
                            std::cout << "[" << id << "] Read Header Failed.\n";
                            m_socket.close();
                        }
                    });
                }
                void ReadBody()
                {
                    asio::async_read(m_socket,asio::buffer(m_msgTemporaryIn.body.data(), m_msgTemporaryIn.body.size()),
                    [this](std::error_code ec, std::size_t length)
                    {
                        if(!ec)
                        {
                            AddToIncomingMessageQueue();
                        }
                        else
                        {
                            std::cout << "[" << id << "] Read Body Fail.\n" ;
                            m_socket.close();
                        }
                    });
                }

                void AddToIncomingMessageQueue()
                {
                    if(m_nOwnerType == owner::server)
                        m_qMessagesIn.push_back({this->shared_from_this(), m_msgTemporaryIn});

                    else
                        m_qMessagesIn.push_back({nullptr, m_msgTemporaryIn});

                    ReadHeader();
                }

                void WriteValidation()
                {
                    
                    if (m_nOwnerType == owner::client){
                        std::cout << "Message out : " << m_nHandshakeOutClient << std::endl;
                    asio::async_write(m_socket, asio::buffer(&m_nHandshakeOutClient, sizeof(int)),
                        [this](std::error_code ec, std::size_t length)
                        {
                            if (!ec)
                            {
                                // Validation data sent, clients should sit and wait
                                // for a response (or a closure)
                                
                                    ReadHeader();
                            }
                            else
                            {
                                m_socket.close();
                            }
                        });
                    }
                    else
                    {
                        std::cout << "Message out : " << m_nHandshakeOutServer << std::endl;
                        asio::async_write(m_socket, asio::buffer(m_nHandshakeOutServer, (word.length()+1)),
                        [this](std::error_code ec, std::size_t length)
                        {
                            if (!ec)
                            {
                            }
                            else
                            {
                                m_socket.close();
                            }
                        });
                    }
                }

            void ReadValidation(someip::net::server_interface<T>* server = nullptr)
                {
                    if (m_nOwnerType == owner::server)
                    {
                    asio::async_read(m_socket, asio::buffer(&m_nHandshakeInServer, sizeof(int)),
                        [this, server](std::error_code ec, std::size_t length)
                        {
                            if (!ec)
                            {
                                std::cout << "[] Message received : " << m_nHandshakeInServer << std::endl; 

                                    // Connection is a server, so check response from client

                                    // Compare sent data to actual solution
                                    std::cout << "m_nHandshakeCheck : " << m_nHandshakeCheck << std::endl;
                                    if (m_nHandshakeInServer == m_nHandshakeCheck)
                                    {
                                        // Client has provided valid solution, so allow it to connect properly
                                        std::cout << "Client Validated" << std::endl;
                                        server->OnClientValidated(this->shared_from_this());

                                        // Sit waiting to receive data now
                                        ReadHeader();
                                    }
                                    else
                                    {
                                        // Client gave incorrect data, so disconnect
                                        std::cout << "Client Disconnected (Fail Validation)" << std::endl;
                                        m_socket.close();
                                    }
                                }
                        });
                    }
                                else
                                {
                    asio::async_read(m_socket, asio::buffer(m_nHandshakeInClient, word.length()+ 1),
                        [this, server](std::error_code ec, std::size_t length)
                        {
                            if (!ec)
                            {
                                    // Connection is a client, so solve puzzle
                                    std::string wew = m_nHandshakeInClient;
                                    m_key = determine_shift(wew);
                                    std::cout << "Determined shift : " << m_key << std::endl;
                                    //wew = decrypt_word(wew, m_key);
                                    //wew.copy(m_nHandshakeOut, wew.length());
                                    m_nHandshakeOutClient = m_key;
                                    std::cout << "hand shake out received value : " << m_nHandshakeOutClient << std::endl;

                                    // Write the result
                                    WriteValidation();
                                }
                            else
                            {
                                // Some biggerfailure occured
                                std::cout << "Client Disconnected (ReadValidation)" << std::endl;
                                m_socket.close();
                            }
                        });
                }
                }

                        

            protected: 
            
            asio::ip::tcp::socket m_socket;
            asio::io_context& m_asioContext;
            tsqueue<message> m_qMessagesOut;
            tsqueue<owned_message<T>>& m_qMessagesIn;
            message m_msgTemporaryIn;
            owner m_nOwnerType = owner::server;

            //For the server : sends out a word, expects a number, matches it with a number

			char*  m_nHandshakeOutServer;
			int m_nHandshakeInServer;
			int m_nHandshakeCheck;

            //For the client : receives a word, sends back a number: 
            char* m_nHandshakeInClient;
            int m_nHandshakeOutClient;

            int m_key = 0;
            std::string word;

			bool m_bValidHandshake = false;
			bool m_bConnectionEstablished = false;

			uint32_t id = 0;
        };
    }
}
