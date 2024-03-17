#include <iostream>
#include <mutex>
#include "Server.hpp"

Server::Server()
{
    m_policy = std::make_unique<DummyMessageProcessing>();
    m_policy->configure(this);
}

void Server::join(std::shared_ptr<Client> &client)
{
    {
        std::mutex mutex;
        std::lock_guard<std::mutex> lock(mutex);
        m_clients.push_back(client);
        client->join_server(this);
    }
    std::cout << "Client joined" << std::endl;
}

void Server::leave(std::shared_ptr<Client> &client)
{
    {
        std::mutex mutex;
        std::lock_guard<std::mutex> lock(mutex);
        client->leave_server();
        m_clients.erase(std::remove(m_clients.begin(), m_clients.end(), client), m_clients.end());
    }
    std::cout << "Client left" << std::endl;
}