#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <mutex>
#include <memory>
#include <boost/signals2.hpp>
#include "Socket.hpp"

class Server;

class Client
{
    Posix::Socket m_socket;
    Server *m_server;
    boost::signals2::connection m_send_connection;
    boost::signals2::connection m_end_connection;
    bool m_disconnected = false;

public:
    Client() = delete;
    Client(Posix::Socket &&socket);
    ~Client() = default;

    void join_server(Server *server);
    void leave_server();

    int send(const std::string &message);
    bool receive();
};

#endif // CLIENT_HPP