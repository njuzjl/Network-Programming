#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>

int main()
{
    int sockfd, n;
    struct sockaddr_in srvaddr, cliaddr;
    char buf[1024];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&srvaddr, sizeof(srvaddr));
    srvaddr.sin_family = AF_INET;
    srvaddr.sin_port = htons(8887);        //将16位整数由主机字节顺序转换成网络字节顺序
    srvaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockfd, (struct sockaddr*)&srvaddr, sizeof(struct sockaddr));

    write(sockfd, "Hello, network!", 20);

    n = read(sockfd, buf, 1024);
    buf[n] = '\0';

    fputs(buf, stdout);

    close(sockfd);

    return 0;

}
