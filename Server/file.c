#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define FILENAME "index.txt" // Nome do arquivo para download
#define SERVER_PORT 8765      // Porta do servidor

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    FILE *file;

    // Abrir o arquivo a ser disponibilizado para download
    file = fopen(FILENAME, "rb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo para download");
        exit(EXIT_FAILURE);
    }

    // Criar um socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Erro ao criar o socket do servidor");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // Configurar o endereço do servidor
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Vincular o socket ao endereço do servidor
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Erro ao vincular o socket do servidor");
        fclose(file);
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Ouça por conexões
    if (listen(server_socket, 1) == -1) {
        perror("Erro ao ouvir por conexões");
        fclose(file);
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Aguardando conexões...\n");

    while (listen(server_socket, 1) != -1) {
        socklen_t client_address_len = sizeof(client_address);

        // Aceitar a conexão do cliente
        client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_len);
        if (client_socket == -1) {
            perror("Erro ao aceitar a conexão do cliente");
            continue;
        }

        printf("Conexão estabelecida com o cliente\n");

        // Enviar o arquivo para o cliente
        char buffer[1024];
        size_t bytesRead;

        while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
            ssize_t bytesSent = send(client_socket, buffer, bytesRead, 0);
            if (bytesSent == -1) {
                perror("Erro ao enviar o arquivo para o cliente");
                break;
            }
        }

        printf("Arquivo enviado para o cliente\n");

        // Fechar o socket do cliente
        close(client_socket);
    }

    // Fechar o arquivo e o socket do servidor (isso normalmente não será alcançado)
    fclose(file);
    close(server_socket);
    printf("Servidor encerrado\n");

    return 0;
}
