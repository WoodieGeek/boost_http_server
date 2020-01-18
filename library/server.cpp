#include "server.h"

#include <bits/stdc++.h>

class session : public std::enable_shared_from_this<session> {
public:
    session(boost::asio::ip::tcp::socket socket)
        : socket_(std::move(socket)) {
    }
    void Start() {
        DoRead();
    }
private:
    void DoRead() {
        auto self(shared_from_this());
        socket_.async_read_some(boost::asio::buffer(data_, 1024), [this, self](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                DoWrite(length);
            }
        });

    }

    void DoWrite(std::size_t) {
        auto self(shared_from_this());
        std::string msg = "HTTP/1.1 200 OK\r\n\r\nSOME TEXT";
        boost::asio::async_write(socket_, boost::asio::buffer(msg), [this, self] (boost::system::error_code ec, std::size_t) {
            if (!ec) {
                socket_.close();
                DoRead();
            }
        });
    }
private:
    boost::asio::ip::tcp::socket socket_;
    char data_[1024];
};

TServer::TServer(const std::string& address, const std::string& port)
    : Acceptor_(IoService_)
    , Socket_(IoService_)
{
    std::cout << "construct server\n";
    boost::asio::ip::tcp::resolver resolver(IoService_);
    boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve({address, port});
    Acceptor_.open(endpoint.protocol());
    Acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    Acceptor_.bind(endpoint);
    Acceptor_.listen();
    DoAccept();
}

void TServer::DoAccept() {
    Acceptor_.async_accept(Socket_, [this](boost::system::error_code ec) {
            if (!Acceptor_.is_open()) {
                std::cout << "acceptor is not open\n";
                return;
            }
            if (!ec) {
                std::make_shared<session>(std::move(Socket_))->Start();
            }
            DoAccept();
    });
}

void TServer::Run() {
    IoService_.run();
}


