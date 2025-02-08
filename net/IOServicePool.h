#pragma once
#include <asio/include/asio.hpp>
#include <vector>

namespace net
{
class IOServicePool
{
  public:
	IOServicePool();
	~IOServicePool();

	void start(size_t concurrency);
    void stop();
    
    asio::io_service& getIOService();
  private:
	std::vector<asio::io_service>       services_;
	std::vector<asio::io_service::work> works_;
	std::vector<std::thread>            threads_;
	size_t                         nextService_;
};
}        // namespace net