#ifndef ADDRESS_HPP
#define ADDRESS_HPP

#include <memory>
#include <sys/socket.h>
#include <sys/un.h>

namespace Posix
{
    struct Address
    {
        /**
         * @brief The address of the Unix domain socket
         */
        std::unique_ptr<struct sockaddr_un> address;

        /**
         * @brief The size of the address
         */
        std::unique_ptr<socklen_t> size;

        Address() = default;

        /**
         * @brief Construct a new Address object
         * @param path The path to the Unix domain socket
         */
        Address(const char *path);

        /**
         * @brief Construct a new Address object
         * @param addr The address to copy
         */
        Address(struct sockaddr *addr);

        /**
         * @brief Get the address object
         * @return const struct sockaddr* The address object
         */
        const struct sockaddr *get_address() const;

        /**
         * @brief Get the address object
         * @return struct sockaddr* The address object
         */
        struct sockaddr *get_address();

        /**
         * @brief Get the size object
         * @return const socklen_t* The size object
         */
        const socklen_t *get_size() const;

        /**
         * @brief Get the size object
         * @return socklen_t* The size object
         */
        socklen_t *get_size();
    };

} // namespace Posix

#endif // ADDRESS_HPP