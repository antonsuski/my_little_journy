#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <string>
#include <string_view>

constexpr std::string_view def_port{ "7777" };
// constexpr std::string_view def_dns{ "example.com" };

int main(int argc, char* argv[])
{
    addrinfo         hint;
    addrinfo*        addr;
    sockaddr_storage incomming_addr;
    int              local_socket_fd, external_socket_fd;
    int              status;

    char addr_str[INET6_ADDRSTRLEN];

    memset(&hint, 0, sizeof(hint));
    hint.ai_family   = AF_UNSPEC;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_flags    = AI_PASSIVE;

    if (0 != (status = getaddrinfo(nullptr, def_port.data(), &hint, &addr)))
    {
        std::cerr << status << " getaddrinfo error: " << gai_strerror(status)
                  << std::endl;
        return 0;
    }

    addrinfo* iter = addr;
    int       yes  = 1;
    while (iter != nullptr)
    {
        local_socket_fd =
            socket(iter->ai_family, iter->ai_socktype, iter->ai_protocol);
        if (local_socket_fd == -1)
        {
            perror("socket");
            close(local_socket_fd);
            iter = iter->ai_next;
            continue;
        }
        std::cout << "Socket was created\n";
        if (setsockopt(local_socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes,
                       sizeof(yes)) == -1)
        {
            perror("setsockopt");
            continue;
        }
        if (bind(local_socket_fd, iter->ai_addr, iter->ai_addrlen) == -1)
        {
            perror("bind");
        }
        std::cout << "Socket was bind\n";
        iter = iter->ai_next;
    }

    std::cout << "ip:"
              << inet_ntop(addr->ai_family, &addr->ai_addrlen, addr_str,
                           sizeof(addr_str))
              << std::endl;

    close(local_socket_fd);
    return EXIT_SUCCESS;
}