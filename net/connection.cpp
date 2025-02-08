#include "connection.h"
#include <string>
#include <thread>
namespace net
{
connection::connection(asio::io_service& io):
	    socket_(io),
        write_strand_(io),
        read_strand_(io)
{
}


void connection::send(uint32_t id,std::string_view data)
{
    std::string buf;
    buf.resize(data.length() + 6);

    id = asio::detail::socket_ops::host_to_network_short(id);
    std::memcpy(buf.data(),&id,4);
    
    uint16_t len = static_cast<uint16_t>(data.length());
    len = asio::detail::socket_ops::host_to_network_short(len);

    std::memcpy(buf.data() + 4,&len,2);

    std::memcpy(buf.data() + 6, data.data(), data.length());

    asio::async_write(socket_,asio::buffer(buf.data(),buf.size()),
    [buf = std::move(buf),this](std::error_code ec,std::size_t)
    {
        if(ec)
        {
            socket_.close();
        }
        else
        {
            std::cout<<"sended:"<<buf[6]<<std::endl;
        }
    });
}

void connection::start()
{
    recv_msg();
}

void connection::recv_msg()
{
    msg_head.resize(6);
    asio::async_read(socket_,asio::buffer(msg_head.data(),6),
    [this](std::error_code ec,std::size_t){
        if (!ec)
        {
            Msg m;
            memcpy(&m.id,msg_head.data(),4);
            m.id = asio::detail::socket_ops::network_to_host_short(m.id);

            uint16_t len;
            memcpy(&len,msg_head.data() + 4,2);
            len = asio::detail::socket_ops::network_to_host_short(len);

            m.data.resize(len);

            asio::async_read(socket_,asio::buffer(m.data.data(),len),
            read_strand_.wrap([m = std::move(m),this](std::error_code ec,std::size_t){
                if (!ec)
                {
                    recv_queue_.enqueue(std::move(m));
                }
            }));
            recv_msg();
        }
        
    });
}

void connection::deal_msg(std::function<void(uint32_t,std::string)> handler)
{
    Msg m;
    while(recv_queue_.try_dequeue(m))
    {
        handler(m.id,std::move(m.data));
    }
}
    
}
