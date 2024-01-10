#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define SERVER_IP "127.0.0.1"
#define PASSWORD "secret_password"

int main() {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    // Criando o socket do cliente
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Falha na criação do socket");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convertendo o endereço IP para binário
    if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0) {
        perror("Conversão de endereço falhou");
        return -1;
    }

    // Conectando ao servidor
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Falha na conexão");
        return -1;
    }

    // Enviando a senha ao servidor
    send(sock, PASSWORD, strlen(PASSWORD), 0);

    // Lendo a resposta do servidor
    valread = read(sock, buffer, sizeof(buffer));
    if (valread <= 0) {
        perror("Erro na leitura do socket");
        close(sock);
        return -1;
    }

    // Imprimindo a resposta do servidor
    printf("Server response: %s\n", buffer);

    close(sock);

    return 0;
}
