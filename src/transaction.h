#ifndef MOCIN_TRANSACTION_H
#define MOCIN_TRANSACTION_H

#include <cstdint>

namespace mocin {
  class Transaction {
    std::string address, sender;
    float amount;
  };
}

#endif // MOCIN_TRANSACTION_H

