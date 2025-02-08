#pragma once
#include <asio/include/asio.hpp>
#include <readerwriterqueue.h>
#include <string>
#include <iostream>
#include <mutex>

namespace net
{
class connection
{
  public:
	connection(asio::io_service& io);

	asio::ip::tcp::socket &socket()
	{
		return socket_;
	}
	void send(uint32_t id,std::string_view data);
    
    void start();

    void deal_msg(std::function<void(uint32_t,std::string)> handler);

  private:
    void recv_msg();

    std::string msg_head;
	asio::io_service::strand write_strand_;
	asio::io_service::strand read_strand_;

	asio::ip::tcp::socket socket_;

    struct Msg
    {
        uint32_t id;
        std::string data;
    };
    moodycamel::ReaderWriterQueue<Msg> recv_queue_;

    std::mutex mutex_;
};
}