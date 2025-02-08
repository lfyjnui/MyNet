#pragma once
#include <asio/include/asio.hpp>
#include <string>
#include <functional>
#include <deque>
#include <memory>


namespace net
{
class connection;
class IOServicePool;

class server
{
public:
    server(const asio::ip::tcp::endpoint& endpoint);
    ~server();
    
    void deal_msgs();
private:
    void do_accept();
    std::unique_ptr<asio::ip::tcp::acceptor> acceptor_;
    //接受连接用的.
    std::unique_ptr<IOServicePool> acc_pool_;
    //处理消息用的
    std::unique_ptr<IOServicePool> con_pool_;
    std::deque<std::unique_ptr<connection>> connections_;

};

    
}