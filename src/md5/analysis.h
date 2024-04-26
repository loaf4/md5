#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <cstddef>
#include <cstdint>
#include <string>
#include <array>
#include <vector>

void second_prototype();
int find_collisions(const std::vector<uint16_t> &found);

uint16_t slice_digest(const std::array<uint8_t, 16> &digest, const size_t size);
std::string generate_data(size_t len);

#endif

