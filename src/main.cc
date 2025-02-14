#include "chacha20.h"
#include "utils.h"

#include <iostream>


int main() {
  std::array<uint32_t, 8> key;
  uint32_t counter;
  std::array<uint32_t, 3> nonce;
  int option;
  ChaCha20* chacha = nullptr;

  do {
    Menu();
    std::cout << "Choose option: ";
    std::cin >> option;

    switch (option) {
      case 1:
        std::cout << "Introduce keys (8 hexadecimal values): ";
        for (auto& k : key) {
          std::cout << std::endl << "Key " << std::distance(&key[0], &k) + 1 << ": ";
          std::cin >> std::hex >> k;
        }
        std::cout << "Introduce counter (1 hexadecimal value): ";
        std::cin >> std::hex >> counter;
        std::cout << "Introduce nonce (3 hexadecimal values): ";
        for (auto& n : nonce) {
          std::cout << std::endl << "Nonce " << std::distance(&nonce[0], &n) + 1 << ": ";
          std::cin >> std::hex >> n;
        }
        delete chacha;
        std::cout << "Data entered successfully!\n";
        chacha = new ChaCha20(key, counter, nonce);
        std::cout << std::endl << "Press ENTER to continue...";
        std::cin.get();
        break;
      case 2:
        if (chacha) {
          chacha->GenerateBlock();
        } else {
          std::cout << "Must introduce data first (option 1).\n";
        }
        break;
      case 3:
        if (chacha) {
          chacha->PrintState();
        } else {
          std::cout << "Must introduce data first (option 1).\n";
        }
        break;
      case 4:
        Help();
        std::cout << std::endl << "Press ENTER to continue...";
        std::cin.get();
        break;
      case 0:
        break;  
      default:
        std::cout << "Invalid Option.\n";
    }
  } while (option != 0);

  delete chacha;
  return 0;
}
