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
