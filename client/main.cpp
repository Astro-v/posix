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

    return 0;
}