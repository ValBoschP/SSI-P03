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
        system("clear");
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
        system("clear");
        std::cout << "Input file name: ";
        std::cin >> filename;
        ReadFromFile(filename, key, counter, nonce);
        chacha = new ChaCha20(key, counter, nonce);
        std::cout << "File read successfully.\n";
        break;
      case 3:
        system("clear");
        if (chacha == nullptr) {
          std::cout << "ERROR: No values introduced.\n";
          break;
        }
        std::cout << "Output file name: ";
        std::cin >> filename;
        chacha->SaveResultsToFile(filename);
        std::cout << "Results saved to file.\n";
        break;
      case 4:
        system("clear");
        Help();
        break;
      case 0:
        std::cout << "Exiting...\n";
        return 0;
      default:
        std::cout << "Invalid option.\n";
    }
  } while (option != 0);
  delete chacha;
  return 0;
}
