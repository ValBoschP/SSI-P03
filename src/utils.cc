#include "chacha20.h"
#include "utils.h"

#include <iostream>
#include <iomanip>
#include <fstream>

void Menu() {
  std::cout << "==== CHACHA20 GENERATOR ====" << std::endl;
  std::cout << "1. Input file data chacha20" << std::endl;
  std::cout << "2. Show results" << std::endl;
  std::cout << "3. Save results to file" << std::endl;
  std::cout << "4. Help" << std::endl;
  std::cout << "0. Exit" << std::endl;
}

void Help() {
  std::cout << "This program implements the ChaCha20 generator.\n";
  std::cout << "Must enter a key of 8 hexadecimal values, a counter of 1 value and a nonce of 3 values.\n";
  std::cout << "The program will generate a block of ChaCha20 and show the current status.\n";
}
