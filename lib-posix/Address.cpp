#include "Address.hpp"

Posix::Address::Address(const char *path)
{
    address = std::make_unique<struct sockaddr_un>();
    address->sun_family = AF_UNIX;
    strncpy(address->sun_path, path, sizeof(address->sun_path));
    size = std::make_unique<socklen_t>(sizeof(struct sockaddr_un));
}

Posix::Address::Address(struct sockaddr *addr)
{
    address = std::make_unique<struct sockaddr_un>();
    address->sun_family = AF_UNIX;
    strncpy(address->sun_path, reinterpret_cast<struct sockaddr_un *>(addr)->sun_path, sizeof(address->sun_path));
    size = std::make_unique<socklen_t>(sizeof(struct sockaddr_un));
}

const struct sockaddr *Posix::Address::get_address() const
{
    return reinterpret_cast<struct sockaddr *>(address.get());
}

struct sockaddr *Posix::Address::get_address()
{
    return reinterpret_cast<struct sockaddr *>(address.get());
}

const socklen_t *Posix::Address::get_size() const
{
    return size.get();
}

socklen_t *Posix::Address::get_size()
{
    return size.get();
}