#include "md5.h"
#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <cstdint>
#include <iterator>
#include <vector>

MD5::MD5() {
    init();
}

MD5::MD5(const std::string& input) : MD5() {
    init();
    std::vector<uint8_t> data(input.begin(), input.end());
    encode_mess(data, data.size());
    finalize();
}

void MD5::init() {
    finalized = false;

    count[0] = 0;
    count[1] = 0;

    state[0] = 0x67452301;
    state[1] = 0xEFCDAB89;
    state[2] = 0x98BADCFE;
    state[3] = 0x10325476;
}

inline uint32_t MD5::cyclic_rotate_left(uint32_t a, int n) {
    return (a << n | a >> (32 - n));
}

inline uint32_t MD5::F(uint32_t x, uint32_t y, uint32_t z) {
    return (x & y) | (~x & z);
}

inline uint32_t MD5::G(uint32_t x, uint32_t y, uint32_t z) {
    return (x & z) | (~z & y);
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

std::vector<uint8_t> MD5::encode(const std::vector<uint32_t>& input, size_t len) {
    std::vector<uint8_t> output;
    for (size_t i {}, j {}; j < len; i++, j += 4) {
        output.push_back(input[i] & 0xff);
        output.push_back((input[i] >> 8) & 0xff);
        output.push_back((input[i] >> 16) & 0xff);
        output.push_back((input[i] >> 24) & 0xff);
    }
    return output;
}

std::vector<uint32_t> MD5::decode(const std::vector<uint8_t>& input, size_t len, int offset) {
    std::vector<uint32_t> output;
    for (size_t i {0}; i < len; i += 4) {
        size_t j {offset + i};
        output.push_back((static_cast<uint32_t>(input[j])) |
                (static_cast<uint32_t>(input[j + 1]) << 8) |
                (static_cast<uint32_t>(input[j + 2]) << 16) |
                (static_cast<uint32_t>(input[j + 3]) << 24));
    }
    return output;
}

void MD5::encode_block(const std::vector<uint8_t>& input, int offset) {
    uint32_t a = state[0], b = state[1], c = state[2], d = state[3];
    std::vector<uint32_t> data {decode(input, 64, offset)};

    // round 1
    FF(a, b, c, d, data[ 0], R11, T[ 0]); // 1
    FF(d, a, b, c, data[ 1], R12, T[ 1]); // 2
    FF(c, d, a, b, data[ 2], R13, T[ 2]); // 3
    FF(b, c, d, a, data[ 3], R14, T[ 3]); // 4
    FF(a, b, c, d, data[ 4], R11, T[ 4]); // 5
    FF(d, a, b, c, data[ 5], R12, T[ 5]); // 6
    FF(c, d, a, b, data[ 6], R13, T[ 6]); // 7
    FF(b, c, d, a, data[ 7], R14, T[ 7]); // 8
    FF(a, b, c, d, data[ 8], R11, T[ 8]); // 9
    FF(d, a, b, c, data[ 9], R12, T[ 9]); // 10
    FF(c, d, a, b, data[10], R13, T[10]); // 11
    FF(b, c, d, a, data[11], R14, T[11]); // 12
    FF(a, b, c, d, data[12], R11, T[12]); // 13
    FF(d, a, b, c, data[13], R12, T[13]); // 14
    FF(c, d, a, b, data[14], R13, T[14]); // 15
    FF(b, c, d, a, data[15], R14, T[15]); // 16

    // round 2
    GG(a, b, c, d, data[ 1], R21, T[16]); // 17
    GG(d, a, b, c, data[ 6], R22, T[17]); // 18
    GG(c, d, a, b, data[11], R23, T[18]); // 19
    GG(b, c, d, a, data[ 0], R24, T[19]); // 20
    GG(a, b, c, d, data[ 5], R21, T[20]); // 21
    GG(d, a, b, c, data[10], R22, T[21]); // 22
    GG(c, d, a, b, data[15], R23, T[22]); // 23
    GG(b, c, d, a, data[ 4], R24, T[23]); // 24
    GG(a, b, c, d, data[ 9], R21, T[24]); // 25
    GG(d, a, b, c, data[14], R22, T[25]); // 26
    GG(c, d, a, b, data[ 3], R23, T[26]); // 27
    GG(b, c, d, a, data[ 8], R24, T[27]); // 28
    GG(a, b, c, d, data[13], R21, T[28]); // 29
    GG(d, a, b, c, data[ 2], R22, T[29]); // 30
    GG(c, d, a, b, data[ 7], R23, T[30]); // 31
    GG(b, c, d, a, data[12], R24, T[31]); // 32

    // round 3
    HH(a, b, c, d, data[ 5], R31, T[32]); // 33
    HH(d, a, b, c, data[ 8], R32, T[33]); // 34
    HH(c, d, a, b, data[11], R33, T[34]); // 35
    HH(b, c, d, a, data[14], R34, T[35]); // 36
    HH(a, b, c, d, data[ 1], R31, T[36]); // 37
    HH(d, a, b, c, data[ 4], R32, T[37]); // 38
    HH(c, d, a, b, data[ 7], R33, T[38]); // 39
    HH(b, c, d, a, data[10], R34, T[39]); // 40
    HH(a, b, c, d, data[13], R31, T[40]); // 41
    HH(d, a, b, c, data[ 0], R32, T[41]); // 42
    HH(c, d, a, b, data[ 3], R33, T[42]); // 43
    HH(b, c, d, a, data[ 6], R34, T[43]); // 44
    HH(a, b, c, d, data[ 9], R31, T[44]); // 45
    HH(d, a, b, c, data[12], R32, T[45]); // 46
    HH(c, d, a, b, data[15], R33, T[46]); // 47
    HH(b, c, d, a, data[ 2], R34, T[47]); // 48

    // round 4
    II(a, b, c, d, data[ 0], R41, T[48]); // 49
    II(d, a, b, c, data[ 7], R42, T[49]); // 50
    II(c, d, a, b, data[14], R43, T[50]); // 51
    II(b, c, d, a, data[ 5], R44, T[51]); // 52
    II(a, b, c, d, data[12], R41, T[52]); // 53
    II(d, a, b, c, data[ 3], R42, T[53]); // 54
    II(c, d, a, b, data[10], R43, T[54]); // 55
    II(b, c, d, a, data[ 1], R44, T[55]); // 56
    II(a, b, c, d, data[ 8], R41, T[56]); // 57
    II(d, a, b, c, data[15], R42, T[57]); // 58
    II(c, d, a, b, data[ 6], R43, T[58]); // 59
    II(b, c, d, a, data[13], R44, T[59]); // 60
    II(a, b, c, d, data[ 4], R41, T[60]); // 61
    II(d, a, b, c, data[11], R42, T[61]); // 62
    II(c, d, a, b, data[ 2], R43, T[62]); // 63
    II(b, c, d, a, data[ 9], R44, T[63]); // 64

    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
}

void MD5::encode_mess(const std::vector<uint8_t> &input, size_t len) {
    size_t index {count[0] / 8 % 64};

    if ((count[0] += (len << 3)) < (len << 3)) {
        ++count[1];
    }
    count[1] += (len >> 29);

    size_t f_part {64 - index};
    size_t i {};

    if (len >= f_part) {

        std::copy(input.begin(), input.begin() + f_part, buffer.begin() + index);
        encode_block(std::vector<uint8_t>(buffer.begin(), buffer.end()), 0);

        for (i = f_part; i + 64 <= len; i += 64) {
            encode_block(input, i);
        }
        index = 0;
    }

    std::copy(input.begin() + i, input.begin() + len, buffer.begin() + index);
}

MD5& MD5::finalize() {
    static std::vector<uint8_t> padding(64, 0);
    padding[0] = 0x80;

    if (!finalized) {
        std::vector<uint8_t> bits {encode(std::vector<uint32_t>(std::begin(count), std::end(count)), 8)};

        size_t index {count[0] / 8 % 64};
        size_t pad_len {(index < 56) ? (56 - index) : (120 - index)};

        encode_mess(padding, pad_len);
        encode_mess(bits, 8);

        std::vector<uint8_t> res {encode(std::vector(state.begin(), state.end()), 16)};
        std::copy(res.begin(), res.end(), digest.begin());

        finalized = true;
    }

    return *this;
}

void MD5::print_hash() {
    for (int i {}; i < 16; ++i) {
        std::cout << std::hex << (int)digest[i];
    }
    std::cout << std::endl;
}
