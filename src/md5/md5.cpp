#include "md5.h"

MD5::MD5() {
    buffer[0] = 0x67452301;
    buffer[1] = 0xEFCDAB89;
    buffer[2] = 0x98BADCFE;
    buffer[3] = 0x10325476;
}

MD5::MD5(const std::string& input) : MD5() {
}

inline uint32_t MD5::cyclic_rotate_left(uint32_t a, int n) {
    return (a << n | a >> (32 - n));
}

inline uint32_t MD5::F(uint32_t x, uint32_t y, uint32_t z) {
    return (x & y) | (~x ^ z);
}

inline uint32_t MD5::G(uint32_t x, uint32_t y, uint32_t z) {
    return (x & z) | (~z ^ y);
}

inline uint32_t MD5::H(uint32_t x, uint32_t y, uint32_t z) {
    return x ^ y ^ z;
}

inline uint32_t MD5::I(uint32_t x, uint32_t y, uint32_t z) {
    return y ^ (~z | x);
}

inline void MD5::FF(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t t) {
    a = b + cyclic_rotate_left((a + F(b, c, d) + x + t), s);
}

inline void MD5::GG(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t t) {
    a = b + cyclic_rotate_left((a + G(b, c, d) + x + t), s);
}

inline void MD5::HH(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t t) {
    a = b + cyclic_rotate_left((a + H(b, c, d) + x + t), s);
}

inline void MD5::II(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t t) {
    a = b + cyclic_rotate_left((a + I(b, c, d) + x + t), s);
}

void MD5::encode(const std::vector<uint32_t>& input, std::vector<uint8_t>& output) {
    for (size_t i {0}; i < input.size(); i++) {
        output.push_back(input[i] & 0xff);
        output.push_back((input[i] >> 8) & 0xff);
        output.push_back((input[i] >> 16) & 0xff);
        output.push_back((input[i] >> 24) & 0xff);
    }
}

void MD5::decode(const std::vector<uint8_t>& input, std::vector<uint32_t>& output) {
    for (size_t i {0}; i < input.size(); i += 4) {
        output.push_back((static_cast<uint32_t>(input[i])) |
                (static_cast<uint32_t>(input[i + 1]) << 8) |
                (static_cast<uint32_t>(input[i + 2]) << 16) |
                (static_cast<uint32_t>(input[i + 3]) << 24));
    }
}

void MD5::encode_block(const std::vector<uint32_t>& data, int offset) {
    uint32_t a = buffer[0], b = buffer[1], c = buffer[2], d = buffer[3];

    // round 1
    FF(a, b, c, d, data[offset +  0], R11, T[ 0]); // 1
    FF(a, b, c, d, data[offset +  1], R12, T[ 1]); // 2
    FF(a, b, c, d, data[offset +  2], R13, T[ 2]); // 3
    FF(a, b, c, d, data[offset +  3], R14, T[ 3]); // 4
    FF(a, b, c, d, data[offset +  4], R11, T[ 4]); // 5
    FF(a, b, c, d, data[offset +  5], R12, T[ 5]); // 6
    FF(a, b, c, d, data[offset +  6], R13, T[ 6]); // 7
    FF(a, b, c, d, data[offset +  7], R14, T[ 7]); // 8
    FF(a, b, c, d, data[offset +  8], R11, T[ 8]); // 9
    FF(a, b, c, d, data[offset +  9], R12, T[ 9]); // 10
    FF(a, b, c, d, data[offset + 10], R13, T[10]); // 11
    FF(a, b, c, d, data[offset + 11], R14, T[11]); // 12
    FF(a, b, c, d, data[offset + 12], R11, T[12]); // 13
    FF(a, b, c, d, data[offset + 13], R12, T[13]); // 14
    FF(a, b, c, d, data[offset + 14], R13, T[14]); // 15
    FF(a, b, c, d, data[offset + 15], R14, T[15]); // 16

    // round 2
    FF(a, b, c, d, data[offset +  1], R21, T[16]); // 17
    FF(a, b, c, d, data[offset +  6], R22, T[17]); // 18
    FF(a, b, c, d, data[offset + 11], R23, T[18]); // 19
    FF(a, b, c, d, data[offset +  0], R24, T[19]); // 20
    FF(a, b, c, d, data[offset +  5], R21, T[20]); // 21
    FF(a, b, c, d, data[offset + 10], R22, T[21]); // 22
    FF(a, b, c, d, data[offset + 15], R23, T[22]); // 23
    FF(a, b, c, d, data[offset +  4], R24, T[23]); // 24
    FF(a, b, c, d, data[offset +  9], R21, T[24]); // 25
    FF(a, b, c, d, data[offset + 14], R22, T[25]); // 26
    FF(a, b, c, d, data[offset +  3], R23, T[26]); // 27
    FF(a, b, c, d, data[offset +  8], R24, T[27]); // 28
    FF(a, b, c, d, data[offset + 13], R21, T[28]); // 29
    FF(a, b, c, d, data[offset +  2], R22, T[29]); // 30
    FF(a, b, c, d, data[offset +  7], R23, T[30]); // 31
    FF(a, b, c, d, data[offset + 12], R24, T[31]); // 32

    // round 3
    FF(a, b, c, d, data[offset +  5], R31, T[32]); // 33
    FF(a, b, c, d, data[offset +  8], R32, T[33]); // 34
    FF(a, b, c, d, data[offset + 11], R33, T[34]); // 35
    FF(a, b, c, d, data[offset + 14], R34, T[35]); // 36
    FF(a, b, c, d, data[offset +  1], R31, T[36]); // 37
    FF(a, b, c, d, data[offset +  4], R32, T[37]); // 38
    FF(a, b, c, d, data[offset +  7], R33, T[38]); // 39
    FF(a, b, c, d, data[offset + 10], R34, T[39]); // 40
    FF(a, b, c, d, data[offset + 13], R31, T[40]); // 41
    FF(a, b, c, d, data[offset +  0], R32, T[41]); // 42
    FF(a, b, c, d, data[offset +  3], R33, T[42]); // 43
    FF(a, b, c, d, data[offset +  6], R34, T[43]); // 44
    FF(a, b, c, d, data[offset +  9], R31, T[44]); // 45
    FF(a, b, c, d, data[offset + 12], R32, T[45]); // 46
    FF(a, b, c, d, data[offset + 15], R33, T[46]); // 47
    FF(a, b, c, d, data[offset +  2], R34, T[47]); // 48

    // round 4
    FF(a, b, c, d, data[offset +  0], R41, T[48]); // 49
    FF(a, b, c, d, data[offset +  7], R42, T[49]); // 50
    FF(a, b, c, d, data[offset + 14], R43, T[50]); // 51
    FF(a, b, c, d, data[offset +  5], R44, T[51]); // 52
    FF(a, b, c, d, data[offset + 12], R41, T[52]); // 53
    FF(a, b, c, d, data[offset +  3], R42, T[53]); // 54
    FF(a, b, c, d, data[offset + 10], R43, T[54]); // 55
    FF(a, b, c, d, data[offset +  1], R44, T[55]); // 56
    FF(a, b, c, d, data[offset +  8], R41, T[56]); // 57
    FF(a, b, c, d, data[offset + 15], R42, T[57]); // 58
    FF(a, b, c, d, data[offset +  6], R43, T[58]); // 59
    FF(a, b, c, d, data[offset + 13], R44, T[59]); // 60
    FF(a, b, c, d, data[offset +  4], R41, T[60]); // 61
    FF(a, b, c, d, data[offset + 11], R42, T[61]); // 62
    FF(a, b, c, d, data[offset +  2], R43, T[62]); // 63
    FF(a, b, c, d, data[offset +  9], R44, T[63]); // 64

    buffer[0] += a;
    buffer[1] += b;
    buffer[2] += c;
    buffer[3] += d;
}
