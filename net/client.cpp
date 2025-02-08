#include "client.h"
#include <asio/include/asio.hpp>
#include "IOServicePool.h"
#include "connection.h"

using asio::ip::tcp;
namespace net
{

client::client()
{

}

client::~client()
{

}

void client::connect(std::string_view ip, int port)
{
    pool_ = std::make_unique<IOServicePool>();
    pool_->start(1);
    
    asio::ip::tcp::resolver resolver(pool_->getIOService());
    auto endpoints = resolver.resolve(std::string(ip).c_str(), std::to_string(port).c_str());
	connection_ = std::make_unique<connection>(pool_->getIOService());
	asio::async_connect(connection_->socket(),
	                    endpoints,
	                    [this](std::error_code ec, asio::ip::tcp::endpoint) {
                            if(ec)
                            {
                                std::cout<<ec.message();
                            }
                            else
                            {
                                connection_->start();
                            }
	                    });
	// connection_->start();
}

void client::send(uint32_t id,std::string_view msg)
{
    if (connection_)
    {
        connection_->send(id,msg);
    }
    
}

void client::deal_msgs()
{
    if (connection_)
    {
        connection_->deal_msg([](uint32_t id,std::string data){
            std::cout<<"recv msg:id:"<<id<<","<<data<<std::endl;
        });
    }
    
}

}        // namespace net