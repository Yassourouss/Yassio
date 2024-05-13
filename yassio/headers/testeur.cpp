#include <iostream>
#include "net_message.h"
   #include <cstdint>
#include <limits>

int main()
{


//...

std::cout << std::numeric_limits<uint32_t>::max() << std::endl;
std::cout << std::numeric_limits<uint32_t>::min() << std::endl;
std::cout << std::numeric_limits<int64_t>::max() << std::endl;
std::cout << std::numeric_limits<int64_t>::min() << std::endl;
    return 0;
}