#include "Socket.hpp"
#include "Listener.hpp"
#include "Address.hpp"
#include <iostream>
#include <vector>
#include <string>

int main()
{
    Posix::Listener listener;
    Posix::Address addr("/tmp/test");
    listener.listen(addr);
    Posix::Socket client = listener.accept();

    return 0;
}