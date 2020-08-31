#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "server.h"

void TcpExample::Server::accept_connections() {
  // int socket
  this->srvSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (this->srvSocket < 0) {
    std::cout << "Error establishing connection." << std::endl;
    exit(1);
  }

  std::cout << "Server socket connection created." << std::endl;

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = htons(INADDR_ANY);
  serverAddr.sin_port = htons(this->port);

  if (bind(srvSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
    std::cout << "Error binding socket..." << std::endl;
    exit(1);
  }
  
  size = sizeof(serverAddr);
  std::cout << "Looking for clients..." << std::endl;

  // listening socket
  listen(srvSocket, 1);
  // accept client
  server = accept(srvSocket,(struct sockaddr*)&serverAddr, &size);
  if (server < 0) {
    std::cout << "Error on accepting..." << std::endl;
    exit(1);
  }
}

void TcpExample::Server::start() {
  accept_connections();

  char buffer[this->bufSize];

  while (server > 0) {
    strcpy(buffer, "Server connected....\n");
    send(server, buffer, bufSize, 0);

    std::cout << "Connected with client..." << std::endl;
    std::cout << "Enter # to end the connetion" << std::endl;

    std::cout << "Client: ";
    do {
      recv(server, buffer, bufSize, 0);
      std::cout << "buffer"
                << " ";
      if (*buffer == '#') {
        *buffer = '*';
        isExit = true;
      }
    } while (*buffer != '*');

    do {
      std::cout << "\nServer: ";
      std::cin >> buffer;
      send(server, buffer, bufSize, 0);
      if (*buffer == '*') {
        send(server, buffer, bufSize, 0);
        *buffer = '*';
        isExit = true;
      }
    } while (*buffer != '*');

    std::cout << "Client: ";
    do {
      recv(server, buffer, bufSize, 0);
      std::cout << buffer << " ";
      if (*buffer == '#') {
        *buffer = '*';
        isExit = true;
      }
    } while (!isExit);

    std::cout << "Connection terminated..." << std::endl;
    std::cout << "Goodbye!" << std::endl;
  }
}

