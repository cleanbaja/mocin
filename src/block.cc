#include <string>
#include <cstring>
#include <sstream> 
#include <iomanip>
#include <iostream>
#include <ctime>

#include "util/crypto.h"
#include "block.h"

using namespace mocin;
static uint64_t current_index;
static Block last_block{};

// Helper function to print the digest bytes as a hex string
static std::string hash_to_str(const std::vector<uint8_t>& bytes) {
    std::ostringstream stream;
    for (uint8_t b : bytes)
    {
        stream << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(b);
    }
    return stream.str();
}

Block mocin::generate_block(std::vector<mocin::Transaction> tx) {
  Block new_block{};
  
  new_block.index = current_index++;
  new_block.timestamp = time(nullptr);
  memcpy(new_block.previous_digest, last_block.digest, sizeof(uint32_t) * 8); // Copy over the old digest
  new_block.tx = tx;

  // Generate the hash
  new_block.hash();

  *(&last_block) = new_block;
  return new_block;
}

// Re-hashes the entire block, and updates it
// NOTE: sha3-256 is used throught mocin for hashing, since its more secure.
void mocin::Block::hash() {
  // Determine the size of the hash buffer and create it
  uint64_t merge_size = 24 + 256 + (this->tx.size() * sizeof(Transaction));
  uint8_t* merge_buffer = new uint8_t[merge_size];
  
  // Copy the variables into their proper position
  memcpy(merge_buffer, this, 24);
  memcpy(merge_buffer + 24, this->previous_digest, 256);
  if (this->tx.size() != 0)
    memcpy(merge_buffer + 280, this->tx.data(), (this->tx.size() * sizeof(Transaction)));

  // Now, hash the buffer and store the result
  sha256_compute(merge_buffer, this->digest, merge_size);
}

// Solves a block according to difficulty 'mocin::difficulty'
// For a block to be considered solved, its hash has to start
// with 'mocin::difficulty' zeros.
void mocin::Block::solve() {
  uint64_t merge_size = 24 + 256 + (this->tx.size() * sizeof(Transaction));
  uint8_t* merge_buffer = new uint8_t[merge_size];

  // Create the buffer for use in hash comparisons
  std::vector<char> compare_vec;
  for (int i = 0; i < mocin::difficulty; i++)
    compare_vec.push_back('0');

  // Reuse the buffer between hashes, instead of calling malloc every time (faster)
  auto quick_hash = [merge_buffer, merge_size](Block* blok) {
    memcpy(merge_buffer, blok, 24);
    memcpy(merge_buffer + 24, blok->previous_digest, 256);
    if (blok->tx.size() != 0)
      memcpy(merge_buffer + 280, blok->tx.data(), (blok->tx.size() * sizeof(Transaction)));

    sha256_compute(merge_buffer, blok->digest, merge_size);
  };

  auto is_block_solved = [compare_vec](Block b) {
    std::string data = hash_to_str(std::vector<uint8_t>((uint8_t*)b.digest, (uint8_t*)(b.digest + 8)));
    if (memcmp(data.c_str(), compare_vec.data(), mocin::difficulty) == 0) {
      std::cout << "Solved block (nonce,hash) -> (" << b.nonce << "," << data << ")\n";
      return true;
    } else {
      // std::cout << "Failed block (nonce,hash) -> (" << b.nonce << "," << data << ")\n";
      return false;
    }
  };

  while (!is_block_solved(*this)) {
    nonce++;
    quick_hash(this);
  }

  delete[] merge_buffer;
}

