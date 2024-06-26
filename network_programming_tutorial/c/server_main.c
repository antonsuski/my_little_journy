#include "cnetwork.h"

#define IP_LOCAL "127.0.0.1"

int main(int argc, char* argv[])
{
    int                     sockfd, new_fd; // слушать на sock_fd, новое подключение на new_fd
    struct addrinfo         hints, *servinfo, *p;
    struct sockaddr_storage their_addr; // адресная информация подключившегося
    socklen_t               sin_size;
    struct sigaction        sa;
    int                     yes = 1;
    char                    s[INET6_ADDRSTRLEN];
    int                     rv;

    memset(&hints, 0, sizeof hints);
    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags    = AI_PASSIVE; // использовать мой IP
    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }
    // цикл по всем результатам и связывание с первым возможным
    for (p = servinfo; p != NULL; p = p->ai_next)
    {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) ==
            -1)
        {
            perror("server: socket");
            continue;
        }
        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) ==
            -1)
        {
            perror("setsockopt");
            exit(1);
        }
        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1)
        {
            close(sockfd);
            perror("server: bind");
            continue;
        }
        break;
    }
    if (p == NULL)
    {
        fprintf(stderr, "server: failed to bind\n");
        return 2;
    }
    freeaddrinfo(servinfo); // со структурой закончили
    if (listen(sockfd, BACKLOG) == -1)
    {
        perror("listen");
        exit(1);
    }
    sa.sa_handler = sigchld_handler; // обработка всех удаленных процессов
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1)
    {
        perror("sigaction");
        exit(1);
    }

    char str[256];
    int str_length;

    if(!gethostname(str, str_length))
    {
        printf("hostname: %s\n", str);
    }

    printf("server: waiting for connections…\n");
    while (1)
    { // главный цикл accept()
        sin_size = sizeof their_addr;
        new_fd   = accept(sockfd, (struct sockaddr*)&their_addr, &sin_size);
        if (new_fd == -1)
        {
            perror("accept");
            continue;
        }
        inet_ntop(their_addr.ss_family,
                  get_in_addr((struct sockaddr*)&their_addr), s, sizeof s);
        printf("server: got connection from %s\n", s);
        if (!fork())
        {                  // это порождённые процесс
            close(sockfd); // его слушать не нужно
            if (send(new_fd, "Hello, world!", 13, 0) == -1)
                perror("send");
            close(new_fd);
            exit(0);
        }
        close(new_fd); // родителю это не нужно
    }
    return 0;
}
