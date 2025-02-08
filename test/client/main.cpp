#include <iostream>
#include <sstream>
#include <net/client.h>

using namespace net;
int main()
{
    
    client c;
    c.connect("127.0.0.1",10086);

    int i = 0;
    while(1)
    {
        c.deal_msgs();

        std::stringstream os;
        os<<"sdfsdf"<<i;
        c.send(0,os.str());
    }
    return 0;
}