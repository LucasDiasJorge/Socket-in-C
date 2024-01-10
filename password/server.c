#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define PASSWORD "secret_password"

int main() {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // Criando o socket do servidor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Falha na criação do socket");
        exit(EXIT_FAILURE);
    }

    // Configurando as opções do socket
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("Falha ao configurar as opções do socket");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Associando o socket ao endereço e à porta
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Falha ao associar o socket ao endereço e à porta");
        exit(EXIT_FAILURE);
    }

    // Colocando o socket em modo de escuta
    if (listen(server_fd, 3) < 0) {
        perror("Falha ao colocar o socket em modo de escuta");
        exit(EXIT_FAILURE);
    }

    // Aceitando conexões de clientes
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Falha ao aceitar conexões de clientes");
        exit(EXIT_FAILURE);
    }

    // Recebendo a senha do cliente
    valread = read(new_socket, buffer, sizeof(buffer));
    if (valread <= 0) {
        perror("Erro na leitura do socket");
        close(new_socket);
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Verificando a senha
    if (strcmp(buffer, PASSWORD) != 0) {
        printf("Senha incorreta. Conexão encerrada.\n");
        close(new_socket);
        close(server_fd);
        exit(EXIT_SUCCESS);
    }

    // Senha correta, continua a execução
    printf("Senha correta. Conexão estabelecida.\n");

    // Agora você pode realizar as operações desejadas com o cliente

    // Exemplo: Enviando uma mensagem ao cliente
    char *message = "Conexão estabelecida com sucesso!";
    send(new_socket, message, strlen(message), 0);

    // Continua o código conforme necessário...

    close(new_socket);
    close(server_fd);

    return 0;
}
