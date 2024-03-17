#ifndef SERVER_HPP
#define SERVER_HPP

#include <vector>
#include <memory>
#include <boost/signals2.hpp>
#include "Client.hpp"
#include "Query.hpp"
#include "MessageProcessingPolicy.hpp"
#include "DummyMessageProcessing.hpp"

class Server
{
    std::vector<std::shared_ptr<Client>> m_clients;
    std::unique_ptr<MessageProcessingPolicy> m_policy;

public:
    boost::signals2::signal<void(Query &, Client *)> m_queries;
    Server();
    ~Server() = default;

    void join(std::shared_ptr<Client> &client);

    void leave(std::shared_ptr<Client> &client);
};

#endif // SERVER_HPP