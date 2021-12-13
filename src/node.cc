#include <cstring>
#include <iostream>

#include "node.h"
#include "util/net.h"

using namespace mocin::util;

// By default, mocin operates on port 1245
// A list of default hostnames are as follows
static std::string default_hosts[] = {
  "node.mocin.org",
  "entry.cleanbaja.xyz",
  "localhost",
};

// A list of our 20 most close peers on the network
std::vector<Socket*> peers;

// Initializes the p2p network by either connecting
// to a mocin cluster, or creating one ourselves
// NOTE: The main node network is the only network that containes coins of value
// that are convertable to real currency.
void mocin::p2p_connect() {
  Socket* cluster_socket;
  bool am_connected = false;

  for (int i = 0; i < 3; i++) {
    // Attempt to connect to one of the node hosts
    try {
      cluster_socket = new Socket(default_hosts[i], 1245);
      am_connected = true;
      break;
    } catch (SocketException& ex) {
        std::cerr << ex.get_info() << " (host: " << default_hosts[i] << ")\n";
    }
  }

  if (!am_connected) {
    // TODO: Create our own cluster
    std::exit(1);
  }
}


