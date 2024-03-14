#include "Socket.hpp"
#include "Listener.hpp"
#include "Address.hpp"
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
    std::vector<Posix::Socket> clients;
    Posix::Socket &ref = clients.emplace_back(listener.accept());
    std::cout << "Accepted connection" << std::endl;
    std::string message;
    ref.receive(message);
    std::cout << message << std::endl;
    return 0;
}