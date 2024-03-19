#ifndef PARALLEL_PROCESSING_POLICY_HPP
#define PARALLEL_PROCESSING_POLICY_HPP

#include <memory>
#include "ClientProcessingPolicy.hpp"

class ParallelProcessingPolicy : public ClientProcessingPolicy
{

public:
    ParallelProcessingPolicy() = default;
    ~ParallelProcessingPolicy() = default;
    void configure(Server *server) override;

    void process(std::shared_ptr<Client> &client) override;
};
#endif // PARALLEL_PROCESSING_POLICY_HPP