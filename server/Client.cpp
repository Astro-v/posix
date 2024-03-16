#include <iostream>
#include "Client.hpp"
#include "Server.hpp"
#include "Query.hpp"

Client::Client(Posix::Socket &&socket) : m_socket(std::move(socket)) {}

void Client::join_server(Server *server)
{
    if (server == nullptr)
    {
        return;
    }

    m_server = server;
    // ADD subscription to query signal
    m_send_connection = m_server->m_queries.connect([this](Query &q, Client *c)
                                                    {
                        if (q.type == Query::Type::SEND)
                        {
                            // Send the message to the client
                            std::mutex mutex;
                            std::lock_guard<std::mutex> lock(mutex);
                            std::cout << "Sending" << q.message << std::endl;
                            c->send(q.message);
                        } });

    m_end_connection = m_server->m_queries.connect([this](Query &q, Client *c)
                                                   {
                        if (q.type == Query::Type::END and c == this)
                        {
                            m_disconnected = true;
                        } });
}

void Client::leave_server()
{
    m_send_connection.disconnect();
    m_end_connection.disconnect();
    m_server = nullptr;
}

int Client::send(const std::string &message)
{

    return m_socket.send(message);
}

bool Client::receive()
{
    std::string message;
    int output = m_socket.receive(message);
    if (output == 1)
    {
        std::cout << "Client disconnected" << std::endl;
        Query q("", Query::Type::END);
        m_server->m_queries(q, this);
    }
    else
    {

        std::cout << "Received " << message << std::endl;
        Query q(message, Query::Type::RECEIVE);
        m_server->m_queries(q, this);
    }
    return m_disconnected;
}