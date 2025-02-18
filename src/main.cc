#include "chacha20.h"
#include "utils.h"

#include <iostream>
#include <iomanip>

int main() {
  /*
  std::array<uint32_t, kKeySize> key_test = {0x03020100, 0x07060504, 0x0b0a0908, 0x0f0e0d0c,
                                        0x13121110, 0x17161514, 0x1b1a1918, 0x1f1e1d1c};
  uint32_t counter_test = 1;
  std::array<uint32_t, kNonceSize> nonce_test = {0x09000000, 0x4a000000, 0x00000000};

  ChaCha20 chacha(key_test, counter_test, nonce_test);
  */
  ChaCha20 chacha({0}, 0, {0});
  std::array<uint32_t, kStateSize> output;
  
  int option;
  std::string filename;

  do {
    Menu();
    std::cout << "Option: ";
    std::cin >> option;
    switch (option) {
      case 1:
        std::cout << "Enter the filename: ";
        std::cin >> filename;
        chacha = ReadChaCha20Input(filename);
        break;

      case 2:
        system("clear");
        std::cout << "- Estado inicial:\n";
        PrintState(chacha.GetState());
        chacha.RunRounds(output);
        std::cout << "- Estado tras 20 rondas:\n";
        PrintState(output);
        chacha.GenerateBlock(output);
        std::cout << "- Estado de salida del generador:\n";
        PrintState(output);
        break;

      case 3:
        SaveChaCha20Output(chacha);
        break;
        
      case 4:
        system("clear");
        Help();
        break;

      case 0:
        std::cout << "Exiting program." << std::endl;
        break;

      default:
        std::cerr << "ERROR: Invalid option." << std::endl;
        break;
    }
  } while (option != 0);
  return 0;
}
