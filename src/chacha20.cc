#include "chacha20.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <random>

constexpr std::array<uint32_t, 4> kChaChaConst = {
    0x61707865, 0x3320646e, 0x79622d32, 0x6b206574};

uint32_t RotateLeft(uint32_t value, int shift) {
  return (value << shift) | (value >> (32 - shift));
}

ChaCha20::ChaCha20(const std::array<uint32_t, kKeySize>& key,
                   uint32_t counter,
                   const std::array<uint32_t, kNonceSize>& nonce) {
  std::copy(kChaChaConst.begin(), kChaChaConst.end(), state_.begin());
  std::copy(key.begin(), key.end(), state_.begin() + 4);
  state_[12] = counter;
  std::copy(nonce.begin(), nonce.end(), state_.begin() + 13);
}

void ChaCha20::QuarterRound(uint32_t& a, uint32_t& b, uint32_t& c, uint32_t& d) {
  a += b; d ^= a; d = RotateLeft(d, 16);
  c += d; b ^= c; b = RotateLeft(b, 12);
  a += b; d ^= a; d = RotateLeft(d, 8);
  c += d; b ^= c; b = RotateLeft(b, 7);
}

// Modificación
void ChaCha20::QuarterRoundRandom(uint32_t& a, uint32_t& b, uint32_t& c, uint32_t& d) {
  int random_number;
  a += b; d ^= a; d = RotateLeft(d, random_number);
  c += d; b ^= c; b = RotateLeft(b, random_number);
  a += b; d ^= a; d = RotateLeft(d, random_number);
  c += d; b ^= c; b = RotateLeft(b, random_number);
}

void ChaCha20::InnerBlockRandom(std::array<uint32_t, kStateSize>& state) {
  for (int i = 0; i < kRounds; i += 2) {
    QuarterRoundRandom(state[0], state[4], state[8], state[12]);
    QuarterRoundRandom(state[1], state[5], state[9], state[13]);
    QuarterRoundRandom(state[2], state[6], state[10], state[14]);
    QuarterRoundRandom(state[3], state[7], state[11], state[15]);
    QuarterRoundRandom(state[0], state[5], state[10], state[15]);
    QuarterRoundRandom(state[1], state[6], state[11], state[12]);
    QuarterRoundRandom(state[2], state[7], state[8], state[13]);
    QuarterRoundRandom(state[3], state[4], state[9], state[14]);
  }
}

void ChaCha20::RunRoundsRandom(std::array<uint32_t, kStateSize>& output) {
  output = state_;
  InnerBlockRandom(output);
}

void ChaCha20::GenerateBlockRandom(std::array<uint32_t, kStateSize>& output) {
  RunRoundsRandom(output);
  for (size_t i = 0; i < kStateSize; ++i) {
    output[i] += state_[i];
  }
}

void ChaCha20::InnerBlock(std::array<uint32_t, kStateSize>& state) {
  for (int i = 0; i < kRounds; i += 2) {
    QuarterRound(state[0], state[4], state[8], state[12]);
    QuarterRound(state[1], state[5], state[9], state[13]);
    QuarterRound(state[2], state[6], state[10], state[14]);
    QuarterRound(state[3], state[7], state[11], state[15]);
    QuarterRound(state[0], state[5], state[10], state[15]);
    QuarterRound(state[1], state[6], state[11], state[12]);
    QuarterRound(state[2], state[7], state[8], state[13]);
    QuarterRound(state[3], state[4], state[9], state[14]);
  }
}

void ChaCha20::RunRounds(std::array<uint32_t, kStateSize>& output) {
  output = state_;
  InnerBlock(output);
}

void ChaCha20::GenerateBlock(std::array<uint32_t, kStateSize>& output) {
  RunRounds(output);
  for (size_t i = 0; i < kStateSize; ++i) {
    output[i] += state_[i];
  }
}

