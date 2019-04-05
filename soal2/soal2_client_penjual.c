#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8082

int main(int argc, char const *argv[])
{
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char pesan[100] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }

    memset(pesan, 0, 100);
    valread = read(sock, pesan, 100);
    if (strcmp(pesan, "Koneksi ditolak") == 0)
    {
        printf("%s\n", pesan);
        return 0;
    }
    else
    {
        printf("%s\n", pesan);
    }

    while (1)
    {
        scanf("%s", pesan);
        send(sock, pesan, strlen(pesan), 0);
        if (strcmp(pesan, "exit") == 0)
        {
            return 0;
        }
    }

    return 0;
}