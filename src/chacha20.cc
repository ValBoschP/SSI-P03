#include "chacha20.h"

#include <iostream>

ChaCha20::ChaCha20(const std::array<uint32_t, 8>& key, uint32_t counter,
                   const std::array<uint32_t, 3>& nonce) {
  state_ = {0x61707865, 0x3320646e, 0x79622d32, 0x6b206574,
            key[0], key[1], key[2], key[3],
            key[4], key[5], key[6], key[7],
            counter, nonce[0], nonce[1], nonce[2]};
}

void ChaCha20::QuarterRound(uint32_t& a, uint32_t& b, uint32_t& c, uint32_t& d) {
  a += b; d ^= a; d = (d << 16) | (d >> 16);
  c += d; b ^= c; b = (b << 12) | (b >> 20);
  a += b; d ^= a; d = (d << 8) | (d >> 24);
  c += d; b ^= c; b = (b << 7) | (b >> 25);
}

void ChaCha20::GenerateBlock() {
  for (int i = 0; i < kRounds; i += 2) {
    // Column rounds
    QuarterRound(state_[0], state_[4], state_[8], state_[12]);
    QuarterRound(state_[1], state_[5], state_[9], state_[13]);
    QuarterRound(state_[2], state_[6], state_[10], state_[14]);
    QuarterRound(state_[3], state_[7], state_[11], state_[15]);
    // Diagonal rounds
    QuarterRound(state_[0], state_[5], state_[10], state_[15]);
    QuarterRound(state_[1], state_[6], state_[11], state_[12]);
    QuarterRound(state_[2], state_[7], state_[8], state_[13]);
    QuarterRound(state_[3], state_[4], state_[9], state_[14]);
  }
}

void ChaCha20::PrintState() const {
  for (auto val : state_) {
    std::cout << std::hex << val << " ";
  }
  std::cout << std::endl;
}
