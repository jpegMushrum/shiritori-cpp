#include <boost/asio.hpp>
#include <iostream>
#include "server.hpp"

using tcp = boost::asio::ip::tcp;

Server::Server(boost::asio::io_context& ioContext, unsigned short port)
    : ioContext_(ioContext),
    acceptor_(ioContext, tcp::endpoint(tcp::v4(), port))
{
}

void Server::startAccepting()
{
    while (true)
    {
        tcp::socket socket(ioContext_);
        acceptor_.accept(socket);

        std::thread(&Server::clientSession, this, std::move(socket)).detach();
    }
}

void Server::clientSession(tcp::socket socket)
{
    try {
        while (true)
        {
            char data[512];
            size_t len = socket.read_some(boost::asio::buffer(data));

            if (len > 0)
                boost::asio::write(socket, boost::asio::buffer("ok", 2));
        }
    }
    catch (...)
    {
    }
}
