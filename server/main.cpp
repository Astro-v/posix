#include "Socket.hpp"
#include "Listener.hpp"
#include "Address.hpp"

#include "Client.hpp"
#include "Server.hpp"
#include "Query.hpp"

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

    Server server;

    std::shared_ptr<Client> client(std::make_shared<Client>(listener.accept()));

    server.join(client);

    while (!client->receive())
    {
    }

    server.leave(client);

    std::cout << "END" << std::endl;
    return 0;
}