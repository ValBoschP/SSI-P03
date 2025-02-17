#include "utils.h"

#include <iostream>
#include <fstream>

void Menu() {
  std::cout << "==== CHACHA20 GENERATOR ====\n";
  std::cout << "1. Introduce key, nonce and counter\n";
  std::cout << "2. Introduce key, nonce and counter from file\n";
  std::cout << "3. Save results to file\n";
  std::cout << "4. Help\n";
  std::cout << "0. Exit\n";
}

void Help() {
  std::cout << "This program implements the ChaCha20 generator.\n";
  std::cout << "Must enter a key of 8 hexadecimal values, a counter of 1 value and a nonce of 3 values.\n";
  std::cout << "The program will generate a block of ChaCha20 and show the current status.\n";
  std::cout << "Example input:\n";
  std::cout << "Key: 00010203 04050607 08090a0b 0c0d0e0f 10111213 14151617 18191a1b 1c1d1e1f\n";
  std::cout << "Counter: 00000001\n";
  std::cout << "Nonce: 00000009 0000004a 00000000\n";
}

void ReadFromFile(const std::string& filename, std::array<uint32_t, 8>& key, uint32_t& counter, std::array<uint32_t, 3>& nonce) {
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "ERROR: Cannot open file." << std::endl;
    return;
  }
  for (auto& k : key) file >> std::hex >> k;
  file >> std::hex >> counter;
  for (auto& n : nonce) file >> std::hex >> n;
}