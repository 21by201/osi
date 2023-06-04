#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
 
#define BUFFER_SIZE 1024
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 12345
 
int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    socklen_t server_addr_len;
    char buffer[BUFFER_SIZE];
 
    // Создание UDP сокета
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("Ошибка при создании сокета");
        exit(1);
    }
 
    // Инициализация серверного адреса
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    if (inet_aton(SERVER_IP, &server_addr.sin_addr) == 0) {
        perror("Ошибка при преобразовании IP-адреса");
        exit(1);
    }
    memset(server_addr.sin_zero, '\0', sizeof(server_addr.sin_zero));
    server_addr_len = sizeof(server_addr);
 
    while (1) {
        memset(buffer, '\0', BUFFER_SIZE);
 
        printf("Введите сообщение для отправки серверу: ");
        fgets(buffer, BUFFER_SIZE, stdin);
 
        // Отправка данных серверу
        if (sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, server_addr_len) == -1) {
            perror("Ошибка при отправке данных");
            exit(1);
        }
 
        // Прием данных от сервера
        if (recvfrom(sockfd, buffer, BUFFER_SIZE, 0, NULL, NULL) == -1) {
            perror("Ошибка при приеме данных");
            exit(1);
        }
 
        printf("Получен ответ от сервера: %s\n", buffer);
    }
 
    // Закрытие сокета
    close(sockfd);
 
    return 0;
}