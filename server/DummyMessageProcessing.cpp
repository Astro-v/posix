#include "DummyMessageProcessing.hpp"
#include "Server.hpp"
#include "Query.hpp"
#include "Client.hpp"

void DummyMessageProcessing::configure(Server *server)
{
    m_server = server;
    server->m_queries.connect([this](Query &q, Client *c)
                              {
                                if (q.type == Query::Type::RECEIVE)
                                {
                                    std::cout << "Treat :" << q.message << std::endl;
                                    Query response("OK", Query::Type::SEND);
                                    m_server->m_queries(response, c);
                                } });
}