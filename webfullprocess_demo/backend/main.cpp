#include <winsock2.h>

#include <iostream>
#include <string>

using namespace std;

string replyData(const string& msg);

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cout << "usage: program <port>\n";
    return EXIT_FAILURE;
  }
  WSADATA wsa_data;
  if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
    std::cerr << "WSAStartup failed" << std::endl;
    return EXIT_FAILURE;
  }
  SOCKET serv_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (serv_sock == INVALID_SOCKET) {
    std::cerr << "invalid socket" << std::endl;
    WSACleanup();
    return EXIT_FAILURE;
  }
  sockaddr_in serv_addr;
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(static_cast<unsigned short>(std::stoul(argv[1])));
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  if (bind(serv_sock, reinterpret_cast<sockaddr*>(&serv_addr),
           sizeof(serv_addr)) == SOCKET_ERROR) {
    std::cerr << "bind failed\n";
    closesocket(serv_sock);
    WSACleanup();
    return EXIT_FAILURE;
  }
  if (listen(serv_sock, 1) == SOCKET_ERROR) {
    std::cerr << "listen failed\n";
    closesocket(serv_sock);
    WSACleanup();
    return EXIT_FAILURE;
  }
  std::cout << "waiting for client connection...\n";

  while (true) {
    sockaddr_in client_addr;
    int addr_size = sizeof(client_addr);
    SOCKET client_sock = accept(
        serv_sock, reinterpret_cast<sockaddr*>(&client_addr), &addr_size);
    if (client_sock == INVALID_SOCKET) {
      std::cerr << "accept failed\n";
      closesocket(serv_sock);
      WSACleanup();
      return EXIT_FAILURE;
    }
    std::cout << "client connected!\n";

    // 接收消息
    char buff[4096]{};
    int bytesize = recv(client_sock, buff, sizeof(buff) - 1, 0);
    if (bytesize > 0) {
      std::cout << "client message: " << buff << std::endl;
    }

    // 发送消息，复读机
    string data = replyData(buff);
    send(client_sock, data.c_str(), data.size(), 0);

    closesocket(client_sock);
  }

  closesocket(serv_sock);
  WSACleanup();
  return 0;
}

string replyData(const string& msg) {
  return "HTTP/1.1 200 OK\r\n"
         "Content-Type: text/plain\r\n"
         "Connection: close\r\n"
         "Access-Control-Allow-Origin: *\r\n"
         "Access-Control-Allow-Methods: POST, GET, OPTIONS\r\n"
         "Access-Control-Allow-Headers: Content-Type\r\n"
         "\r\n"
         "Backend Received HTTP Request: \r\n" +
         msg;
}
