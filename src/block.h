#ifndef MOCIN_BLOCK_H
#define MOCIN_BLOCK_H

#include <cstdint>
#include <vector>

#include "transaction.h"

namespace mocin {
  class Block {
    uint64_t index, timestamp, nonce;
    std::vector<mocin::Transaction> tx;
  public:
    void solve();
    void hash();
    uint32_t digest[8], previous_digest[8];

    friend Block generate_block(std::vector<mocin::Transaction> tx);
  };

  static constexpr int difficulty = 4;
  Block generate_block(std::vector<mocin::Transaction> tx);
}

#endif // MOCIN_BLOCK_H

