#pragma once
#include <boost/asio.hpp>

class TServer {
public:
    TServer(const TServer&) = delete;
    TServer& operator = (const TServer&) = delete;

    explicit TServer(const std::string& address, const std::string& port);
    void Run();
private:
    void DoAccept();
private:
    boost::asio::io_service IoService_;
    boost::asio::ip::tcp::acceptor Acceptor_;
    boost::asio::ip::tcp::socket Socket_;
};
