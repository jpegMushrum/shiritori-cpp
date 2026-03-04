#include <boost/asio.hpp>
#include <iostream>
#include "server.hpp"

using boost::asio::ip::tcp;

int main() {
    try {
        boost::asio::io_context io;
        Server server(io, 8080);

        std::cout << "Server started on port 8080...\n";

        server.startAccepting();
    }
    catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}