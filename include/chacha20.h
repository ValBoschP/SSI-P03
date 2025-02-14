#ifndef CHACHA20_H
#define CHACHA20_H

#include <array>
#include <cstdint>
#include <vector>

static const int kRounds = 20;
using State = std::array<uint32_t, 16>;

class ChaCha20 {
 public:
  // Constructor
  ChaCha20() {}
  ChaCha20(const std::array<uint32_t, 8>& key, uint32_t counter,
           const std::array<uint32_t, 3>& nonce);
  // Getter
  State GetState() const { return state_; };
  // Methods
  void GenerateBlock();
  void PrintState() const;

  void QuarterRound(uint32_t& a, uint32_t& b, uint32_t& c, uint32_t& d);

 private:
  State state_;
};


#endif