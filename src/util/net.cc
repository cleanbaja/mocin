#include <cstring>
#include <iostream>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>

#include "util/net.h"

// Connects to hostname:port via TCP
static int dial(const char *host, int port) {
	static struct addrinfo hints;
	int srv;
	struct addrinfo *res, *r;
	std::string port_str = std::to_string(port);

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	if(getaddrinfo(host, port_str.c_str(), &hints, &res) != 0) {
		throw mocin::util::SocketException{"cannot resolve hostname, check your network!"};
	}

	for(r = res; r; r = r->ai_next) {
		if((srv = socket(r->ai_family, r->ai_socktype, r->ai_protocol)) == -1)
			continue;
		if(connect(srv, r->ai_addr, r->ai_addrlen) == 0)
			break;
		close(srv);
	}
	
	freeaddrinfo(res);
	if(!r) {
		throw mocin::util::SocketException{"cannot connect to host, check your network!"}; 
	} 

	return srv;

fail:
	return -1;
}

namespace mocin::util {

Socket::Socket(std::string srv, int prt) : hostname(srv), port(prt) {
  sock_fd = dial(srv.c_str(), prt);

  if (!(sock_fd > 0)) {
    throw mocin::util::SocketException{"socket file descriptor not valid!"}; 
  }
}

std::size_t Socket::read(void* buffer, std::size_t len) {
  int status = recv(sock_fd, buffer, len, 0);
  if (0 > status) {
    throw mocin::util::SocketException{"connection timed out!"};
  } else {
    return (std::size_t)status;
  } 
}

std::size_t Socket::write(void* buffer, std::size_t len) {
  int status = send(sock_fd, buffer, len, 0);
  if (0 > status) {
    throw mocin::util::SocketException{"error reading from socket!"};
  } else {
    return (std::size_t)status;
  } 
}

Socket::~Socket() {
  close(sock_fd);
}

}
