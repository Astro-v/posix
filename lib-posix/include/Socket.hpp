#ifndef SOCKET_HPP
#define SOCKET_HPP

#include "Address.hpp"

namespace Posix
{
    class Socket
    {
    private:
        int m_fd;

    public:
        Socket();
        Socket(int fd);
        Socket(const Socket &) = delete;
        Socket &operator=(const Socket &) = delete;
        Socket(Socket &&other);
        ~Socket();

        int set_timeout(int seconds);
        int connect(Address &address);
        int send(const std::string &message);
        int receive(std::string &message);
    };

} // namespace Posix

#endif // SOCKET_HPP