#include <thread>
#include "ParallelProcessingPolicy.hpp"
#include "Client.hpp"
#include "Server.hpp"

void ParallelProcessingPolicy::configure(Server *server)
{
    m_server = server;
}

void ParallelProcessingPolicy::process(std::shared_ptr<Client> &client)
{
    m_server->join(client);
    std::thread t([this, client]()
                  {
            while (!client->receive())
            {
            }
            m_server->leave(client); });
    t.detach();
}