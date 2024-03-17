#ifndef DUMMY_MESSAGE_PROCESSING_HPP
#define DUMMY_MESSAGE_PROCESSING_HPP

#include <iostream>
#include <string>
#include <boost/signals2.hpp>
#include "MessageProcessingPolicy.hpp"

class DummyMessageProcessing : public MessageProcessingPolicy
{

    boost::signals2::connection m_connection;

public:
    DummyMessageProcessing() = default;

    ~DummyMessageProcessing()
    {
        m_connection.disconnect();
    }

    void configure(Server *server) override;
};

#endif // DUMMY_MESSAGE_PROCESSING_HPP