#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define PORT 8082

int *stock;
int total_koneksi = 0;

void *jml_stock(void *arg)
{
    while (1)
    {
        printf("stock : %d\n", *stock);
        sleep(5);
        system("clear");
    }
}

void *koneksi(void *arg_socket)
{

    int sock = *(int *)arg_socket;
    int size;
    char pesan[100];

    while ((size = recv(sock, pesan, 100, 0)) > 0)
    {
        if (strcmp(pesan, "tambah") == 0)
        {
            *stock += 1;
        }
        else if (strcmp(pesan, "exit") == 0)
        {
            size = 0;
            break;
        }

        memset(pesan, 0, 100);
    }

    total_koneksi -= 1;

    if (size == 0)
    {
        printf("Client Disconnected\n");
    }

    close(sock);

    return 0;
}

int main(int argc, char const *argv[])
{
    key_t kode = 123456;
    pthread_t thread;
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char pesan[100] = {0};

    int shmid = shmget(kode, sizeof(int), IPC_CREAT | 0666);
    stock = shmat(shmid, NULL, 0);

    *stock = 0;

    if (pthread_create(&thread, NULL, jml_stock, NULL) < 0)
    {
        perror("can't create thread");
        exit(EXIT_FAILURE);
    }

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen))
    {
        memset(pesan, 0, 100);
        if (total_koneksi < 1)
        {
            strcpy(pesan, "Koneksi diterima");
            printf("Sambungan client penjual diterima\n");
            if (pthread_create(&thread, NULL, koneksi, (void *)&new_socket) < 0)
            {
                perror("could not create thread");
                return 1;
            }
            write(new_socket, pesan, strlen(pesan));
            total_koneksi += 1;
        }
        else
        {
            strcpy(pesan, "Koneksi ditolak");
            printf("Sambungan client penjual ditolak\n");
            write(new_socket, pesan, strlen(pesan));
            close(new_socket);
        }
    }

    return 0;
}