#pragma once
#include "net_common.h"

#include <vector>

namespace someip
{
    namespace net
    {
        struct message_header
        {
            int32_t message_id;
            uint32_t length; /*= sizeof(request_id) + sizeof(protocol_version) +
                    sizeof(interface_version) + sizeof(message_type) +
                    sizeof(return_code);*/
            uint32_t request_id;
            uint8_t protocol_version;
            uint8_t interface_version;
            uint8_t message_type;
            uint8_t return_code;

        };

        struct message
        {
            message_header header{};
            std::vector<uint8_t> body;

        size_t length() const 
        {
            return sizeof(header.request_id) + sizeof(header.protocol_version) +
                    sizeof(header.interface_version) + sizeof(header.message_type) +
                    sizeof(header.return_code) + body.size();
        }

        size_t size() const 
        {
            return body.size();
        }

        //overloading the << operator to facilitate the display
        //of informations in the messages header
        friend std::ostream& operator << (std::ostream& os, const message& msg)
        {
            os << "Message ID: " << int(msg.header.message_id) << "Size: " << msg.header.length;
            return os; 
        }

        //overloading the << and >> operators to facilitate serialisation & deserialisation
        //of data in and out of the messages body
        template<typename DataType>
        friend message& operator << (message& msg, const DataType& data)
        {
            // Check that the type of the data being pushed is trivially copyable
            static_assert(std::is_standard_layout<DataType>::value, "Data is too complex to be pushed into vector");

            // Cache current size of vector, as this will be the point we insert the data
            size_t i = msg.body.size();

            // Resize the vector by the size of the data being pushed
            msg.body.resize(msg.body.size() + sizeof(DataType));

            // Physically copy the data into the newly allocated vector space
            std::memcpy(msg.body.data() + i, &data, sizeof(DataType));

            // Recalculate the message size
            msg.header.length = msg.size();

            // Return the target message so it can be "chained"
            return msg;
        }

        template<typename DataType>
        friend message& operator >> (message& msg, DataType& data)
        {
            // Check that the type of the data being pushed is trivially copyable
            static_assert(std::is_standard_layout<DataType>::value, "Data is too complex to be pulled from vector");

            // Cache the location towards the end of the vector where the pulled data starts
            size_t i = msg.body.size() - sizeof(DataType);

            // Physically copy the data from the vector into the user variable
            std::memcpy(&data, msg.body.data() + i, sizeof(DataType));

            // Shrink the vector to remove read bytes, and reset end position
            msg.body.resize(i);

            // Recalculate the message size
            msg.header.length = msg.size();

            // Return the target message so it can be "chained"
            return msg;
        }	
        };
        
        template <typename T>
		class connection;

		template <typename T>
		struct owned_message
		{
			std::shared_ptr<connection<T>> remote = nullptr;
			message msg;

			// Again, a friendly string maker
			friend std::ostream& operator<<(std::ostream& os, const owned_message<T>& msg)
			{
				os << msg.msg;
				return os;
			}
		};		


    
    }
}