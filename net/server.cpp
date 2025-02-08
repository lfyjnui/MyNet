#include "server.h"
#include "connection.h"
#include "IOServicePool.h"

namespace net
{

server::server(const asio::ip::tcp::endpoint& endpoint)
{
    acc_pool_ = std::make_unique<IOServicePool>();
    acc_pool_->start(1);
    acceptor_ = std::make_unique<asio::ip::tcp::acceptor>(acc_pool_->getIOService(),endpoint);

    con_pool_ = std::make_unique<IOServicePool>();
    con_pool_->start(3);

    do_accept();
}

server::~server()
{

}

void server::do_accept()
{
    auto& io_context = con_pool_->getIOService();
	auto  con    = new connection(io_context);
	auto &socket = con->socket();
	acceptor_->async_accept(socket,
	                       [this, con](std::error_code ec) {
		                       con->start();
		                       connections_.emplace_back(con);
		                       do_accept();
	                       });
}

void server::deal_msgs()
{
    for (auto& con:connections_)
    {
        con->deal_msg([&con](uint32_t id,std::string data){
            std::cout<<"recv msg:id:"<<id<<","<<data<<std::endl;
            con->send(id,data);
        });
    }
    
}

}        // namespace net