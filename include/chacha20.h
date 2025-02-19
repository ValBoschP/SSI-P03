#ifndef CHACHA20_H
#define CHACHA20_H

#include <array>
#include <cstdint>
#include <vector>
#include <string>
#include <fstream>

constexpr int kRounds = 20;
constexpr int kStateSize = 16;
constexpr int kKeySize = 8;
constexpr int kNonceSize = 3;

class ChaCha20 {
 public:
  ChaCha20(const std::array<uint32_t, kKeySize>& key,
           uint32_t counter,
           const std::array<uint32_t, kNonceSize>& nonce);
           
  void GenerateBlock(std::array<uint32_t, kStateSize>& output);
  void RunRounds(std::array<uint32_t, kStateSize>& output);

  const std::array<uint32_t, kStateSize>& GetState() const { return state_; }

  // Modificación
  void QuarterRoundRandom(uint32_t& a, uint32_t& b, uint32_t& c, uint32_t& d);
  void InnerBlockRandom(std::array<uint32_t, kStateSize>& state);
  void RunRoundsRandom(std::array<uint32_t, kStateSize>& output);
  void GenerateBlockRandom(std::array<uint32_t, kStateSize>& output);
  
 private:
  void QuarterRound(uint32_t& a, uint32_t& b, uint32_t& c, uint32_t& d);
  void InnerBlock(std::array<uint32_t, kStateSize>& state);

  std::array<uint32_t, kStateSize> state_;
};

#endif  // CHACHA20_H