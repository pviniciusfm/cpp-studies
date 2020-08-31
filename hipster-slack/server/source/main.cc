#include <iostream>
#include "server.h"

int main(int argc, char *argv[])
{
  std::cout << "Initializing a more organized server" << std::endl;

  TcpExample::Server server(1500);
  server.start();
  return 0;
}

