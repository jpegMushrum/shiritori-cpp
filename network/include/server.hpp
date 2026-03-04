#pragma once

#include <boost/asio.hpp>
#include "session.hpp"

using tcp = boost::asio::ip::tcp;

class Server : public std::enable_shared_from_this<Server> {
public:
    Server(boost::asio::io_context&, unsigned short port);

    void startAccepting();

private:
    void doAccept();
    void clientSession(tcp::socket);

    boost::asio::io_context& ioContext_;
    tcp::acceptor acceptor_;
};