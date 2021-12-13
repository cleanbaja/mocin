#include <iostream>
#include <vector>

#include "block.h"
#include "node.h"
#include "util/crypto.h"

int main() {
  crypto_init();

  std::vector<mocin::Transaction> t;
  mocin::Block blk = generate_block(t);
  blk.solve();

  mocin::p2p_connect();

  crypto_shutdown();

  return 0;
}

