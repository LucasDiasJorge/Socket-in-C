#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

// Função para verificar as credenciais de autenticação
int check_authentication(char *authorization) {
    // Aqui, você deve verificar as credenciais do cliente. Isso pode envolver
    // verificar um nome de usuário e senha em um banco de dados ou outro método.
    // Neste exemplo, estamos apenas verificando se as credenciais são "username:password".
    char *expected_auth = "dXNlcm5hbWU6cGFzc3dvcmQ=";
    if (strcmp(authorization, expected_auth) == 0) {
        printf("Credenciais corretas\n");
        return 1;  // Credenciais corretas
    } else {
        printf("Credenciais incorretas\n");
        return 0;  // Credenciais incorretas
    }
}


void handle_request(int client_socket) {
    char request[1024];
    char response[1024];
    char authorization[1024];
    ssize_t bytes_received = recv(client_socket, request, sizeof(request), 0);
    if (bytes_received < 0) {
        perror("Erro ao receber dados da solicitação");
        return;
    }

    // Analise a solicitação HTTP para obter o cabeçalho de autorização
    char *auth_start = strstr(request, "Authorization: ");
    if (auth_start) {
        sscanf(auth_start, "Authorization: Basic %s", authorization);
    }

    // Verifique as credenciais de autenticação
    if (check_authentication(authorization)) {
        // Credenciais corretas - responda com o conteúdo HTML e imprima os parâmetros
        char content[] = "HTTP/1.1 200 OK\r\n"
                         "Content-Type: text/html\r\n"
                         "\r\n"
                         "<html><body> <h1>R700 configuration </h1> <form><label>Serial:</label><input type=\"text\"value=\"Lucas\"> </form> </body></html>";
        write(client_socket, content, sizeof(content) - 1);
        
        // Procurar pela string POST no request
        char *post_start = strstr(request, "POST / HTTP/1.1");
        if (post_start) {
            // Se for uma solicitação POST
            char *body_start = strstr(request, "\r\n\r\n");
            if (body_start) {
                // Encontrar o início do corpo da solicitação
                char *body = body_start + 4; // Avançar além do \r\n\r\n
                printf("Body: %s\n", body); // Imprimir o corpo da solicitação
            }
        }
    } else {
        // Credenciais incorretas - responda com um erro de autenticação
        char auth_error[] = "HTTP/1.1 401 Unauthorized\r\n"
                            "WWW-Authenticate: Basic realm=\"Acesso Restrito\"\r\n"
                            "Content-Length: 0\r\n\r\n";
        write(client_socket, auth_error, sizeof(auth_error) - 1);
    }
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    // Crie um socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Erro ao criar o socket");
        exit(1);
    }

    // Configure o endereço do servidor
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8797);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Vincule o socket ao endereço do servidor
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Erro ao vincular o socket");
        exit(1);
    }

    // Ouça por conexões
    if (listen(server_socket, 5) == -1) {
        perror("Erro ao ouvir por conexões");
        exit(1);
    }

    printf("Aguardando conexões...\n");

    while (1) {
        // Aceite a conexão do cliente
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket == -1) {
            perror("Erro ao aceitar a conexão");
            continue;
        }

        printf("Conexão estabelecida\n");

        // Lide com a solicitação HTTP do cliente
        handle_request(client_socket);

        // Feche o socket do cliente
        close(client_socket);
        printf("Conexão encerrada\n");
    }

    // Feche o socket do servidor
    close(server_socket);

    return 0;
}
