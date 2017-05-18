#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <arpa/inet.h>

int main()
{
    int sockfd, new_fd;
    struct sockaddr_in srvaddr, cliaddr;    //套接口地址结构
    char buf[1024];
    int sin_size;
    int n;
    int i;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);   //监听描述符
    bzero(&srvaddr, sizeof(srvaddr));
    srvaddr.sin_family = AF_INET;
    srvaddr.sin_port = htons(8887);        //将16位整数由主机字节顺序转换成网络字节顺序
    srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(sockfd, (struct sockaddr*)&srvaddr, sizeof(struct sockaddr));

    listen(sockfd, 10);

    for(; ;)
    {
        sin_size = sizeof(struct sockaddr_in);
        printf("start!\n");

        new_fd = accept(sockfd, (struct sockaddr*)&cliaddr, &sin_size);  //返回已连接描述符

        printf("accept over\n");

        //n = recvfrom(new_fd, buf, 1024, 0, (struct sockaddr*)&cliaddr, &sin_size);
        //n = recv(new_fd, buf, 1024, 0);
        n = read(new_fd, buf, 1024);
        
        buf[n] = '\0';
        printf("recvfrom over\n");
        
        printf("server: got connection: %s\n",buf);
        printf("server: got connection from port %d: \n", ntohs(cliaddr.sin_port));
        //printf("%x\n", cliaddr.sin_addr);
        printf("server: got connection from IP %s: \n", inet_ntoa(cliaddr.sin_addr));

        //printf("server: got connection from IP %s, port %d: %s\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port), buf);
        //printf("server: got connection from IP %s, port %d: \n", cliaddr.sin_addr, cliaddr.sin_port);

        //send(new_fd, "Hello, client! \n", 20, 0);
        write(new_fd, "Hello, client! \n", 20);
        
        printf("send over\n");

        close(new_fd);
    }
    close(sockfd);
    return 0;

}
