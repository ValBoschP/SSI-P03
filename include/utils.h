#ifndef UTILS_H
#define UTILS_H

#include <array>
#include <cstdint>
#include <string>

void Menu();
void Help();
void ReadFromFile(const std::string& filename, std::array<uint32_t, 8>& key, uint32_t& counter, std::array<uint32_t, 3>& nonce);

#endif