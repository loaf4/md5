#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <cstddef>
#include <cstdint>
#include <string>
#include <array>

void second_prototype();
void find_collisions();

uint16_t slice_digest(const std::array<uint8_t, 16> &digest, const size_t size);
std::string generate_data(size_t len);

#endif

