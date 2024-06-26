#include <iostream>
#include "someip.h"
#include <map>

struct n_mservice {
    uint32_t service_id;
    uint32_t instance_id;
    uint32_t port;
    uint32_t  index;
    n_mservice(uint32_t srv, uint32_t inst, uint32_t po, uint32_t ind) : service_id(srv), instance_id(inst), port(po), index(ind)
    {} 
    friend std::ostream& operator<<(std::ostream& os, n_mservice& serv)
    {
        os << "Service id : " <<  serv.service_id << "\n Instance id : " << serv.instance_id << "\n Port : " << serv.port << std::endl;
        return os;
    }
};

int main(){
std::map<int, n_mservice>mp;
n_mservice sr1(0x1234,0x4321, 60000, 1);
mp[1] = n_mservice(0x1234,0x4321, 60000, 1);
std::map<int, n_mservice>::iterator it = mp.begin();
while (it != mp.end())
{
    std::cout << it->second << std::endl;
    }
}