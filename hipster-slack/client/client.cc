#include <arpa/inet.h>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int client, server;
  int portNum = 1500;
  bool isExit;
  int bufsize = 1024;
  char buffer[bufsize];
  char *ip = "127.0.0.1";

  struct sockaddr_in server_addr;

  // inti socket
  client = socket(AF_INET, SOCK_STREAM, 0);

  if (client < 0) {
    std::cout << "Error creating socket ..." << std::endl;
    exit(1);
  }

  std::cout << "Client socket created." << std::endl;

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htons(portNum);

  // connecting socket server

  if (connect(client, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
      0) {
    std::cout << "Connecting confirmed" << std::endl;
  }
  recv(server, buffer, bufsize, 0);
  std::cout << "Connetion confirmed" << std::endl;

  std::cout << "Enter # to end the connection" << std::endl;

  do {
    std::cout << "Client: ";
    do {
      std::cin >> buffer;
      send(client, buffer, bufsize, 0);
      if (*buffer == '#') {
        send(client, buffer, bufsize, 0);
        *buffer = '*';
        isExit = true;
      }
    } while (*buffer != 42);
    std::cout << "Server: ";
    do {
      recv(client, buffer, bufsize, 0);
    } while (*buffer != 42);
    std::cout << std::endl;
  } while (isExit);

  return 0;
}
