#ifndef UTIL_NET_H
#define UTIL_NET_H

#include <string>
#include <exception>


namespace mocin::util {
  class Socket {
    int sock_fd, port;
    std::string hostname;
  public:
    Socket(std::string srv, int prt);
    ~Socket();
    std::size_t read(void* buffer, std::size_t len);
    std::size_t write(void* buffer, std::size_t len);
  };

  class SocketException : public std::exception {
    std::string message;
  public:
    SocketException(std::string mes) : message(mes) {}
    std::string get_info() { return message; }
  };
}

#endif // UTIL_NET_H

