#pragma once
#include <asio/include/asio.hpp>
#include <readerwriterqueue.h>
#include <string>
#include <iostream>
#include <thread>

class connection
{
  public:
	connection();

	asio::ip::tcp::socket &get_socket()
	{
		return socket_;
	}
	void send_msg(std::string_view msg);

	//void tick_recv(std::function<void(const std::string &)> handler)
	//{
	//	std::string* msg;
	//	do
	//	{
	//		msg = recive_queue_.peek();
//
	//		if (msg)
	//		{
	//			handler(*msg);
	//			recive_queue_.pop();
	//		}
	//	} while (msg);
	//}

  private:
	//void send()
	//{
	//	std::string* msg = send_queue_.peek();
	//	if (msg)
	//	{
	//		asio::async_write(socket_,
	//		                  asio::buffer(msg->data(), msg->size()),
	//		                  [this](std::error_code ec, std::size_t) {
	//			                  if (!ec)
	//			                  {
	//				                  send_queue_.pop();
	//				                  send();
	//			                  }
	//			                  else
	//			                  {
	//				                  socket_.close();
	//			                  }
	//		                  });
	//	}
	//}
	//void recv()
	//{
	//	recv_msg_length();
	//}
	//void recv_msg_length()
	//{
	//	asio::async_read(socket_,
	//	                 asio::buffer(recv_buf, 4),
	//	                 [this](std::error_code ec, std::size_t) {
	//		                 if (!ec)
	//		                 {
	//			                 auto len = std::atoi(recv_buf);
	//			                 recv_msg_content(len);
	//		                 }
	//		                 else
	//		                 {
	//			                 socket_.close();
	//		                 }
	//	                 });
	//}
//
	//void recv_msg_content(uint32_t length)
	//{
	//	asio::async_read(socket_, asio::buffer(recv_buf, length),
	//	                 [=](std::error_code ec, std::size_t len) {
	//		                 if (!ec)
	//		                 {
	//			                 recive_queue_.enqueue(std::string(recv_buf,len));
	//			                 recv_msg_length();
	//		                 }
	//		                 else
	//		                 {
	//			                 socket_.close();
	//		                 }
	//	                 });
	//}
	asio::io_service      io_context_;
	asio::io_service::strand write_strand;

	asio::ip::tcp::socket socket_;
};