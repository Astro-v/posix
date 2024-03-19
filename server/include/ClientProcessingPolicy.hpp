#ifndef CLIENT_PROCESSING_POLICY_HPP
#define CLIENT_PROCESSING_POLICY_HPP

#include <memory>
#include <vector>

class Client;
class Server;

class ClientProcessingPolicy
{
protected:
    Server *m_server;
    std::vector<std::shared_ptr<Client>> m_clients;

public:
    virtual ~ClientProcessingPolicy() = default;
    virtual void configure(Server *server) = 0;
    virtual void add_client(std::shared_ptr<Client> &client) = 0;
    virtual void process() = 0;
};

#endif // CLIENT_PROCESSING_POLICY_HPP