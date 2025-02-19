#include "chacha20.h"
#include "utils.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>

void Menu() {
  std::cout << "==== CHACHA20 GENERATOR ====" << std::endl;
  std::cout << "1. Input file data chacha20" << std::endl;
  std::cout << "2. Show results" << std::endl;
  std::cout << "3. Save results to file" << std::endl;
  std::cout << "4. Help" << std::endl;
  std::cout << "5. Show results with random QR" << std::endl;
  std::cout << "0. Exit" << std::endl;
}

void Help() {
  std::cout << "ChaCha20 Cipher Implementation\n"
            << "=====================================\n"
            << "This program reads ChaCha20 encryption parameters from a file\n"
            << "and performs various operations such as displaying the state,\n"
            << "executing rounds, and generating keystream blocks.\n\n"
            << "Usage:\n"
            << "  1. Enter the input filename when prompted.\n"
            << "  2. Select an operation from the menu:\n"
            << "     [1] Show initial state\n"
            << "     [2] Perform 20 ChaCha20 rounds\n"
            << "     [3] Generate a keystream block\n"
            << "     [4] Encrypt/Decrypt a message (TBD)\n"
            << "     [0] Exit the program\n\n"
            << "File format:\n"
            << "  - The file should contain hexadecimal values separated by colons.\n"
            << "  - First 32 bytes (128 hex digits) represent the encryption key.\n"
            << "  - Next 4 bytes (8 hex digits) are the counter.\n"
            << "  - Last 12 bytes (24 hex digits) form the nonce.\n\n"
            << "Example input file:\n"
            << "  00:01:02:03: 04:05:06:07: 08:09:0a:0b: 0c:0d:0e:0f:\n"
            << "  10:11:12:13: 14:15:16:17: 18:19:1a:1b: 1c:1d:1e:1f\n"
            << "  01:00:00:00\n"
            << "  00:00:00:09: 00:00:00:4a: 00:00:00:00\n\n"
            << "Notes:\n"
            << "  - Ensure the file is correctly formatted, or the program will fail.\n"
            << "  - ChaCha20 is a stream cipher; use it securely with unique nonces.\n"
            << "  - For more details, refer to RFC 7539 (ChaCha20 and Poly1305).\n"
            << "=====================================\n";
}

void PrintState(const std::array<uint32_t, kStateSize>& state) {
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      std::cout << std::hex << std::setw(8) << std::setfill('0')
                << state[i * 4 + j] << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

void PrintState(const std::array<uint32_t, kStateSize>& state, std::ostream& os = std::cout) {
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      os << std::hex << std::setw(8) << std::setfill('0') << state[i * 4 + j] << " ";
    }
    os << "\n";
  }
  os << "\n";
}

uint32_t ToLittleEndian(const std::vector<uint8_t>& bytes, size_t start) {
  return (static_cast<uint32_t>(bytes[start]) |
          (static_cast<uint32_t>(bytes[start + 1]) << 8) |
          (static_cast<uint32_t>(bytes[start + 2]) << 16) |
          (static_cast<uint32_t>(bytes[start + 3]) << 24));
}

ChaCha20 ReadChaCha20Input(const std::string& filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "ERROR: Could not open file " << filename << std::endl;
    throw std::runtime_error("File not found");
  }

  std::string line;
  std::vector<uint8_t> byte_values;

  while (std::getline(file, line)) {
    std::replace(line.begin(), line.end(), ':', ' '); // Reemplazar ':' por espacio
    std::istringstream iss(line);
    std::string hex_value;

    while (iss >> hex_value) {
      uint8_t byte = static_cast<uint8_t>(std::stoul(hex_value, nullptr, 16));
      byte_values.push_back(byte);
    }
  }

  if (byte_values.size() != (kKeySize * 4 + 4 + kNonceSize * 4)) {
    std::cerr << "ERROR: Incorrect data format in file." << std::endl;
    throw std::runtime_error("Invalid file format");
  }

  std::array<uint32_t, kKeySize> key;
  uint32_t counter;
  std::array<uint32_t, kNonceSize> nonce;

  for (size_t i = 0; i < kKeySize; ++i) {
    key[i] = ToLittleEndian(byte_values, i * 4);
  }

  counter = ToLittleEndian(byte_values, kKeySize * 4);

  for (size_t i = 0; i < kNonceSize; ++i) {
    nonce[i] = ToLittleEndian(byte_values, kKeySize * 4 + 4 + i * 4);
  }
  return ChaCha20(key, counter, nonce);
}

void SaveChaCha20Output(ChaCha20& chacha) {
  std::ofstream file("results.txt");
  std::array<uint32_t, kStateSize> output;
  
  if (!file) {
    std::cerr << "ERROR: Could not open file results.txt" << std::endl;
    throw std::runtime_error("File not found");
  }

  file << "- Estado inicial:\n";
  PrintState(chacha.GetState(), file);

  chacha.RunRounds(output);
  file << "- Estado tras 20 rondas:\n";
  PrintState(output, file);

  chacha.GenerateBlock(output);
  file << "- Estado de salida del generador:\n";
  PrintState(output, file);
  
  std::cout << "Results saved on results.txt\n";
}
