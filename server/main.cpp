#include "Socket.hpp"
#include "Listener.hpp"
#include "Address.hpp"
#include "include/Client.hpp"
#include <iostream>
#include <vector>
#include <string>

int main()
{
    Posix::Listener listener;
    Posix::Address addr("/tmp/test");
    listener.listen(addr);
    std::cout << "Listening on "
              << "/tmp/test" << std::endl;
    Client client(listener.accept());
    std::cout << "Accepted connection" << std::endl;
    std::string message;
    std::cout << message << std::endl;
    return 0;
}