#pragma once
#include <string>
#include <functional>
#include <thread>

namespace net
{
class connection;
class IOServicePool;
class client
{
public:
    client();
    ~client();
    void connect(std::string_view ip,int port);
    void send(uint32_t id,std::string_view msg);
    
    void deal_msgs();
private:
    std::unique_ptr<connection> connection_;
    std::unique_ptr<IOServicePool> pool_;
};
}