#include <iostream>
#include <net/server.h>

using asio::ip::tcp;
using namespace net;
int main()
{
    tcp::endpoint endpoint(tcp::v4(),10086);

    server sv(endpoint);
    
    while(true)
    {
        sv.deal_msgs();
    }
    return 0;
}