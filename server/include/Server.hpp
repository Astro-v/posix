#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <vector>
#include <memory>
#include <mutex>
#include <boost/signals2.hpp>
#include "Client.hpp"
#include "Listener.hpp"
#include "Query.hpp"

class Server
{
    std::vector<std::shared_ptr<Client>> m_clients;

public:
    boost::signals2::signal<void(Query &, Client *)> m_queries;
    Server() = default;
    ~Server() = default;

    void join(std::shared_ptr<Client> &client)
    {
        {
            std::mutex mutex;
            std::lock_guard<std::mutex> lock(mutex);
            m_clients.push_back(client);
            client->join_server(this);
        }
        std::cout << "Client joined" << std::endl;
    }

    void leave(std::shared_ptr<Client> &client)
    {
        {
            std::mutex mutex;
            std::lock_guard<std::mutex> lock(mutex);
            client->leave_server();
            m_clients.erase(std::remove(m_clients.begin(), m_clients.end(), client), m_clients.end());
        }
        std::cout << "Client left" << std::endl;
    }
};

#endif // SERVER_HPP