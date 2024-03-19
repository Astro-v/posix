#include "SequentialProcessingPolicy.hpp"
#include "Client.hpp"
#include "Server.hpp"

void SequentialProcessingPolicy::configure(Server *server)
{
    m_server = server;
}

void SequentialProcessingPolicy::add_client(std::shared_ptr<Client> &client)
{
    m_clients.push_back(client);
    m_server->join(client);
}

void SequentialProcessingPolicy::process()
{
    for (auto &it_client = m_clients.begin(); it_client != m_clients.end();)
    {
        if ((*it_client)->receive())
        {
            m_server->leave(*it_client);
            it_client = m_clients.erase(it_client);
        }
        else
        {
            ++it_client;
        }
    }
}