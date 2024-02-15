#ifndef MD5_H
#define MD5_H

#include <alloca.h>
#include <cstdint>
#include <vector>
#include <string>

// constants for shifting bits in every round 
#define R11 7
#define R12 12
#define R13 17
#define R14 22
#define R21 5
#define R22 9
#define R23 14
#define R24 20
#define R31 4
#define R32 11
#define R33 16
#define R34 23
#define R41 6
#define R42 10
#define R43 15
#define R44 21

// table of pre-calculated cosines using T[i] = 2^32 * abs(sin(i))
const uint32_t T[64] {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
    0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
    0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
    0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
    0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

class MD5 {

    std::vector<uint8_t> output;
    uint32_t buffer[4];

    static uint32_t cyclic_rotate_left(uint32_t a, int n);
    static uint32_t F(uint32_t x, uint32_t y, uint32_t z);
    static uint32_t G(uint32_t x, uint32_t y, uint32_t z);
    static uint32_t H(uint32_t x, uint32_t y, uint32_t z);
    static uint32_t I(uint32_t x, uint32_t y, uint32_t z);
    static void FF(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t k, uint32_t s, uint32_t i);
    static void GG(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t k, uint32_t s, uint32_t i);
    static void HH(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t k, uint32_t s, uint32_t i);
    static void II(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t k, uint32_t s, uint32_t i);

    static void encode(const std::vector<uint32_t>& input, std::vector<uint8_t>& output);
    static void decode(const std::vector<uint8_t>& input, std::vector<uint32_t>& output);
    void encode_block(const std::vector<uint32_t>& data, int offset);
    void encode_mess(const std::vector<uint32_t>& input);
public:
    MD5();
    MD5(const std::string& input);
    void hash_string(const std::string& input);
};

#endif

