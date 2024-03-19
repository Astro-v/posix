#ifndef SEQUENTIAL_PROCESSING_POLICY_HPP
#define SEQUENTIAL_PROCESSING_POLICY_HPP

#include "ClientProcessingPolicy.hpp"

class SequentialProcessingPolicy : public ClientProcessingPolicy
{

public:
    void configure(Server *server) override;
    void add_client(std::shared_ptr<Client> &client) override;
    void process() override;
};

#endif // SEQUENTIAL_PROCESSING_POLICY_HPP
