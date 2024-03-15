#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Socket.hpp"

class Server;

class Client
{
    Posix::Socket m_socket;
    Server *m_server;

public:
    Client() = delete;
    Client(Posix::Socket &&socket) : m_socket(std::move(socket)) {}
    ~Client() = default;

    void join_server(Server *server)
    {
        m_server = server;
    }

    int send(const std::string &message)
    {

        return m_socket.send(message);
    }

    int receive(std::string &message)
    {
        return m_socket.receive(message);
    }
};

#endif // CLIENT_HPP