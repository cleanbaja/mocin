#ifndef UTIL_CRYPTO_H
#define UTIL_CRYPTO_H

#include <cstdint>

namespace util {
  // A pair of ECDSA keys used for signing mocin transactions
  class SignKeys {
  public:  
    uint64_t pub;
    uint64_t priv;
  };

  SignKeys* generate_keys();
}

void crypto_init();
void crypto_shutdown();

void sha256_compute(uint8_t* buffer, uint32_t digest[8], uint64_t datalen);

#endif // UTIL_CRYPTO_H

