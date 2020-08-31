#include <sys/socket.h>
#include <vector>
#include <arpa/inet.h>

#ifndef TCP_EXAMPLE_SERVER_H
#define TCP_EXAMPLE_SERVER_H

namespace TcpExample {
class Server {
private:
  int port;
  int srvSocket;
  int server;
  int bufSize;
  bool isExit;
  struct sockaddr_in serverAddr;
  socklen_t size;
  std::vector<int> clients;

public:
  void start();
  void accept_connections();
  Server(int port);
  const int& getPort() const;
};
} // namespace TcpExample
#endif

