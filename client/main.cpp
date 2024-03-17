#include "Socket.hpp"
#include "Listener.hpp"
#include "Address.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>

int main()
{
    Posix::Socket client;
    Posix::Address addr("/tmp/test");
    client.connect(addr);
    std::string message = "Hello, server!";
    client.send(message);
    std::string response;
    client.receive(response);
    std::cout << "Server says: " << response << std::endl;

    return 0;
}