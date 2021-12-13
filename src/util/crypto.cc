#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <openssl/err.h>

#include "util/crypto.h"

EVP_MD_CTX* context;

void crypto_init() {
  /* Setup the crypto context */
  context = EVP_MD_CTX_new();
}

void crypto_shutdown() {
  /* Removes all digests and ciphers */
  EVP_cleanup();

  /* Destroy the crypto context */
  EVP_MD_CTX_destroy(context);
}

void sha256_compute(uint8_t* buffer, uint32_t digest[8], uint64_t datalen) {
  uint32_t digest_length = SHA256_DIGEST_LENGTH;
  const EVP_MD* algorithm = EVP_sha3_256();
  
  EVP_DigestInit_ex(context, algorithm, nullptr);
  EVP_DigestUpdate(context, buffer, datalen);
  
  EVP_DigestFinal_ex(context, (uint8_t*)digest, &digest_length);
}

