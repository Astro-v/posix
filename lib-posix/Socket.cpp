#include "Socket.hpp"

#include <sys/socket.h>
#include <sys/un.h>
#include <sys/time.h>
#include <unistd.h>
#include <iostream>

Posix::Socket::Socket() : Socket(::socket(AF_UNIX, SOCK_STREAM, 0))
{
}

Posix::Socket::Socket(int fd) : m_fd(fd)
{
    // Check if the socket was created
    if (m_fd == -1)
    {
        std::cerr << "Error: socket" << std::endl;
        throw std::runtime_error("Error: socket");
    }

    set_timeout(1);
}

Posix::Socket::Socket(Socket &&other)
{
    m_fd = other.m_fd;
    other.m_fd = -1;
}

Posix::Socket::~Socket()
{
    // Close the file descriptor
    if (m_fd != -1)
    {
        ::close(m_fd);
    }
}

/**
 * @brief Set the timeout for send and receive operations
 * @param seconds The timeout in seconds
 * @return 0 if everything works fine, 1 otherwise
 */
int Posix::Socket::set_timeout(int seconds)
{
    struct timeval timeout;
    timeout.tv_sec = seconds;
    timeout.tv_usec = 0;

    // Set the timeout for receive operations
    if (::setsockopt(m_fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
    {
        std::cerr << "Error: setsockopt SO_RCVTIMEO" << std::endl;
        return 1;
    }

    // Set the timeout for send operations
    if (::setsockopt(m_fd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
    {
        std::cerr << "Error: setsockopt SO_SNDTIMEO" << std::endl;
        return 1;
    }

    return 0;
}

/**
 * @brief Connect to a server
 * @param address The address of the server
 * @return 0 if everything works fine, 1 otherwise
 */
int Posix::Socket::connect(Address &address)
{
    if (::connect(m_fd, address.get_address(), *address.get_size()) == -1)
    {
        // Error
        return 1;
    }
    // Everything works fine
    return 0;
}

/**
 * @brief Send a message
 * @param message The message to send
 * @return 0 if everything works fine, 1 otherwise
 */
int Posix::Socket::send(const std::string &message)
{
    ssize_t bytes_sent;

    // Send the message
    bytes_sent = ::send(m_fd, message.c_str(), message.size(), MSG_NOSIGNAL);

    if (bytes_sent <= 0)
    {
        // Error or end of the connection
        return 1;
    }

    // Everything works fine
    return 0;
}

/**
 * @brief Receive a message
 * @param message The received message
 * @return 0 if everything works fine, 1 otherwise
 */
int Posix::Socket::receive(std::string &message)
{
    ssize_t n = 0;
    char buf[100];

    memset(buf, 0, sizeof(buf));

    // Wait to receive the message (Blocking call)
    n = ::recv(m_fd, &buf, sizeof(buf), 0);

    if (n == -1)
    {
        // Error or end of the connection
        return 1;
    }

    // Store the received message
    message = std::string(buf, n);

    // Everything works fine
    return 0;
}
