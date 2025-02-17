#include "chacha20.h"

#include <array>
#include <cstdint>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>

uint32_t ChaCha20::ToLittleEndian(uint32_t value) {
  return ((value >> 24) & 0x000000FF) |
         ((value >> 8)  & 0x0000FF00) |
         ((value << 8)  & 0x00FF0000) |
         ((value << 24) & 0xFF000000);
}

ChaCha20::ChaCha20(const std::array<uint32_t, 8>& key, uint32_t counter,
                   const std::array<uint32_t, 3>& nonce) {
  state_ = {ToLittleEndian(0x61707865), ToLittleEndian(0x3320646e),
            ToLittleEndian(0x79622d32), ToLittleEndian(0x6b206574),
            ToLittleEndian(key[0]), ToLittleEndian(key[1]),
            ToLittleEndian(key[2]), ToLittleEndian(key[3]),
            ToLittleEndian(key[4]), ToLittleEndian(key[5]),
            ToLittleEndian(key[6]), ToLittleEndian(key[7]),
            ToLittleEndian(counter), ToLittleEndian(nonce[0]),
            ToLittleEndian(nonce[1]), ToLittleEndian(nonce[2])};
}

void ChaCha20::QuarterRound(uint32_t& a, uint32_t& b, uint32_t& c, uint32_t& d) {
  a += b; d ^= a; d = (d << 16) | (d >> 16);
  c += d; b ^= c; b = (b << 12) | (b >> 20);
  a += b; d ^= a; d = (d << 8) | (d >> 24);
  c += d; b ^= c; b = (b << 7) | (b >> 25);
}

void ChaCha20::GenerateBlock() {
  State working_state = state_;
  State original_state = state_;
  for (int i = 0; i < kRounds; i += 2) {
    QuarterRound(working_state[0], working_state[4], working_state[8], working_state[12]);
    QuarterRound(working_state[1], working_state[5], working_state[9], working_state[13]);
    QuarterRound(working_state[2], working_state[6], working_state[10], working_state[14]);
    QuarterRound(working_state[3], working_state[7], working_state[11], working_state[15]);
    QuarterRound(working_state[0], working_state[5], working_state[10], working_state[15]);
    QuarterRound(working_state[1], working_state[6], working_state[11], working_state[12]);
    QuarterRound(working_state[2], working_state[7], working_state[8], working_state[13]);
    QuarterRound(working_state[3], working_state[4], working_state[9], working_state[14]);
  }
  for (int i = 0; i < 16; ++i) {
    state_[i] = working_state[i] + original_state[i];
  }
}

void ChaCha20::PrintState() const {
  for (int i = 0; i < 16; ++i) {
    std::cout << std::hex << state_[i] << " ";
  }
  std::cout << std::endl;
}

void ChaCha20::SaveResultsToFile(const std::string& filename) {
  std::ofstream file(filename);
  if (!file) {
    std::cerr << "ERROR: Cannot open file." << std::endl;
    return;
  }
  file << "• Estado inicial=\n";
  for (int i = 0; i < 16; ++i) {
    if (i % 4 == 0 && i != 0) file << "\n";
    file << std::hex << std::setw(8) << std::setfill('0') << state_[i] << " ";
  }
  file << "\n\n";

  file << "• Estado final tras las 20 iteraciones=\n";
  GenerateBlock();
  for (int i = 0; i < 16; ++i) {
    if (i % 4 == 0 && i != 0) file << "\n";
    file << std::hex << std::setw(8) << std::setfill('0') << state_[i] << " ";
  }
  file << "\n\n";

  file << "• Estado de salida del generador=\n";
  State output_state = state_;
  GenerateBlock();
  for (int i = 0; i < 16; ++i) {
    if (i % 4 == 0 && i != 0) file << "\n";
    file << std::hex << std::setw(8) << std::setfill('0') << state_[i] << " ";
  }
  state_ = output_state;
  file << "\n";
  file.close();
}
