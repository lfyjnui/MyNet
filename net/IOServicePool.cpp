#include "IOServicePool.h"

namespace net
{
    IOServicePool::IOServicePool()
    :nextService_(0)
    {

    }

    IOServicePool::~IOServicePool()
    {

    }

    void IOServicePool::start(size_t concurrency)
    {
        if (concurrency == 0)
        {
            concurrency = std::thread::hardware_concurrency();
        }
        
        services_ = std::move(std::vector<asio::io_context>(concurrency));
        for (size_t i = 0; i < concurrency; i++)
        {
            works_.emplace_back(services_[i]);
        }
        
        for (size_t i = 0; i < concurrency; i++)
        {
            threads_.emplace_back([this,i](){
                services_[i].run();
            });
        }
    }

    void IOServicePool::stop()
    {
        for (auto& io: services_)
        {
            io.stop();
        }
        
        works_.clear();
        services_.clear();

        for (auto& t:threads_)
        {
            t.join();
        }
        threads_.clear();
    }

    
    asio::io_service& IOServicePool::getIOService()
    {
        auto& service = services_[nextService_++];
        if (nextService_ == services_.size())
        {
            nextService_ = 0;
        }
        return service;
    }
}