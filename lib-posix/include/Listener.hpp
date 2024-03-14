#ifndef LISTENER_HPP
#define LISTENER_HPP

#include "Socket.hpp"
#include "Address.hpp"
#include <memory>

namespace Posix
{
    class Listener
    {
    private:
        int m_fd;
        void handle_bind_error(int error);
        void handle_close_error(int error);

    public:
        Listener();
        ~Listener();
        Listener(const Listener &) = delete;
        Listener &operator=(const Listener &) = delete;

        void listen(Address &address, int backlog = 5);
        Socket accept();
    };

} // namespace Posix

#endif // LISTENER_HPP