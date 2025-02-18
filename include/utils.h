#ifndef UTILS_H
#define UTILS_H

#include <array>
#include <cstdint>
#include <string>

#include "chacha20.h"

void Menu();
void Help();
void PrintState(const std::array<uint32_t, kStateSize>& state);

#endif