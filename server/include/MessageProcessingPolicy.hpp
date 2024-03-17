#ifndef MESSAGE_PROCESSING_POLICY_HPP
#define MESSAGE_PROCESSING_POLICY_HPP

class Server;

class MessageProcessingPolicy
{
protected:
    Server *m_server;

public:
    MessageProcessingPolicy() = default;
    virtual ~MessageProcessingPolicy() = default;
    virtual void configure(Server *server) = 0;
};

#endif // MESSAGE_PROCESSING_POLICY_HPP