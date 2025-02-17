#include "chacha20.h"
#include "utils.h"

#include <iostream>


int main() {
  std::array<uint32_t, 8> key;
  uint32_t counter;
  std::array<uint32_t, 3> nonce;
  int option;
  ChaCha20* chacha = nullptr;
  std::string filename;

  do {
    Menu();
    std::cout << "Choose option: ";
    std::cin >> option;

    switch (option) {
      case 1:
        for (int i = 0; i < 8; ++i) {
          std::cout << "Key " << i << ": ";
          std::cin >> std::hex >> key[i];
        }
        std::cout << "Counter: ";
        std::cin >> std::hex >> counter;
        for (int i = 0; i < 3; ++i) {
          std::cout << "Nonce " << i << ": ";
          std::cin >> std::hex >> nonce[i];
        }
        chacha = new ChaCha20(key, counter, nonce);
        std::cout << "Values introduced successfully.\n";
        break;
      case 2:
        std::cout << "Filename: ";
        std::cin >> filename;
        ReadFromFile(filename, key, counter, nonce);
        chacha = new ChaCha20(key, counter, nonce);
        std::cout << "File read successfully.\n";
        break;
      case 3:
        if (chacha == nullptr) {
          std::cout << "ERROR: No values introduced.\n";
          break;
        }
        std::cout << "Filename: ";
        std::cin >> filename;
        chacha->SaveResultsToFile(filename);
        std::cout << "Results saved to file.\n";
        break;
      case 4:
        Help();
        break;
      case 0:
        std::cout << "Exiting...\n";
        return;
      default:
        std::cout << "Invalid option.\n";
    }
  } while (option != 0);
  delete chacha;
  return 0;
}
