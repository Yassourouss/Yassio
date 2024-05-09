#include <iostream>
#include "net_message.h"

int main()
{
    someip::net::message msg;
    someip::net::message_header header{0x01,0x02,0x03,0x04,0x05,0x06,0x07};
    msg.header = header;
    int a[3][2] = {{10,20},{30,40},{50,60}};
    float b = 10.5;
    msg << a << b;
    int x[3][2]; 
    float y;
    msg >> y >> x;

    return 0;
}