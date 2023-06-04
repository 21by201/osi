#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
 
#define BUFFER_SIZE 1024
#define PORT 12345
 
int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len;
    char buffer[BUFFER_SIZE];
 
    // Создание UDP сокета
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("Ошибка при создании сокета");
        exit(1);
    }
 
    // Инициализация серверного адреса
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    memset(server_addr.sin_zero, '\0', sizeof(server_addr.sin_zero));
 
    // Привязка сокета к серверному адресу
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Ошибка при привязке сокета");
        exit(1);
    }
 
    printf("UDP-сервер запущен и ожидает подключений...\n");
 
    while (1) {
        memset(buffer, '\0', BUFFER_SIZE);
 
        // Прием данных от клиента
        client_addr_len = sizeof(client_addr);
        if (recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &client_addr_len) == -1) {
            perror("Ошибка при приеме данных");
            exit(1);
        }
 
        printf("Получены данные от клиента %s:%d: %s\n",
               inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buffer);
 
        // Отправка данных обратно клиенту
        if (sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&client_addr, client_addr_len) == -1) {
            perror("Ошибка при отправке данных");
            exit(1);
        }
 
        printf("Отправлены данные обратно клиенту %s:%d: %s\n",
               inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buffer);
    }
 
    // Закрытие сокета
    close(sockfd);
 
    return 0;
}