#ifndef UTILS_H
#define UTILS_H

#include <array>
#include <cstdint>
#include <string>

#include "chacha20.h"

void Menu();
void Help();
void PrintState(const std::array<uint32_t, kStateSize>& state);
uint32_t ToLittleEndian(const std::vector<uint8_t>& bytes, size_t start);
ChaCha20 ReadChaCha20Input(const std::string& filename);
void SaveChaCha20Output(ChaCha20& chacha);

#endif // UTILS_H