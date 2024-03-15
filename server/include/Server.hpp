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
    boost::signals2::signal<void(Query &, std::shared_ptr<Client> &)> m_queries;
    Server() = default;
    ~Server() = default;

    void join(std::shared_ptr<Client> &client)
    {
        boost::signals2::connection connection;
        {
            std::mutex mutex;
            std::lock_guard<std::mutex> lock(mutex);
            m_clients.push_back(client);
            client->join_server(this);

            // ADD subscription to query signal
            connection = m_queries.connect([this](Query &q, std::shared_ptr<Client> &c)
                                           {
                        if (q.type == Query::Type::SEND)
                        {
                            // Send the message to the client
                            std::mutex mutex;
                            std::lock_guard<std::mutex> lock(mutex);
                            std::cout << "Sending" << q.message << std::endl;
                            c->send(q.message);
                        } });
        }

        std::string message;
        if (client->receive(message) == 0)
        {
            Query query(message, Query::Type::RECEIVE);
            m_queries(query, client);
        }

        connection.disconnect();
    }
};

#endif // SERVER_HPP