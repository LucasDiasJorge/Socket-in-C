# Socket-in-C

struct sockaddr_in: é uma estrutura de dados que contém informações sobre o endereço de um socket, como o endereço IP e a porta. É usada para definir o endereço de um socket.

char *hello: é uma variável que armazena uma string de caracteres, que neste caso é uma mensagem em formato HTML. Essa variável é usada para enviar a mensagem do cliente para o servidor.

socket(): é uma função do sistema que cria um endpoint para comunicação de rede. É usada para criar um socket.

setsockopt(): é uma função que define opções para o socket. É usada para configurar o socket.

bind(): é uma função que associa um endereço local a um socket. É usada para vincular o endereço e a porta ao socket.

exit(): é uma função que termina o programa imediatamente. É usada para encerrar o programa em caso de erro ou conclusão bem-sucedida.

listen(): é uma função que coloca um socket em modo passivo, permitindo que ele aguarde conexões de entrada. É usada para ouvir conexões de entrada.

read(): é uma função que lê dados de um arquivo ou de um socket. É usada para ler os dados recebidos pelo socket.

valread: é uma variável que armazena o número de bytes lidos pelo socket.

inet_pton(): é uma função que converte um endereço IP de formato texto para formato binário. É usada para converter o endereço IP do servidor.

memset(): é uma função que preenche uma área de memória com um valor específico. É usada para preencher a estrutura serv_addr com zeros.

htons(): é uma função que converte um valor short de ordem de bytes do host para ordem de bytes da rede. É usada para converter a porta para a ordem de bytes da rede.

```c
#include <sys/types.h>
#include <sys/socket.h>
int socket(int domain, int type, int protocol);
```

- `domain`: Este argumento especifica o domínio de comunicação que o socket usará. O domínio define a família de protocolos de rede que o socket utilizará. Alguns valores comuns incluem `AF_INET` (IPv4), `AF_INET6` (IPv6) e `AF_UNIX` (Unix domain sockets).

- `type`: Este argumento especifica o tipo de socket que você deseja criar. Os tipos comuns incluem `SOCK_STREAM` para sockets TCP (que fornecem uma comunicação confiável e orientada a conexões) e `SOCK_DGRAM` para sockets UDP (que fornecem comunicação não confiável e sem conexão).

- `protocol`: Este argumento especifica o protocolo a ser usado com o socket. Normalmente, você pode usar `0` para que o sistema operacional escolha o protocolo apropriado com base no domínio e no tipo. No entanto, em algumas situações específicas, você pode especificar um protocolo, como `IPPROTO_TCP` para sockets TCP ou `IPPROTO_UDP` para sockets UDP.
