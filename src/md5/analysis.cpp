#include "analysis.h"
#include "md5.h"

#include <array>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <string>

const std::string alpha {"0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPRQSTUVWXYZ"};
const std::vector<std::string> passwords {"", "md5", "hello"};
const std::vector<int> bits {8, 10, 12, 14, 16};

void second_prototype() {
    std::srand(std::time(nullptr));
    std::vector<std::array<uint8_t, 16>> passwords_digests(3);
    std::vector<std::vector<int>> freq_proto(3);
    for (auto &a : freq_proto) {
        a = std::vector<int>(5, 0);
    }
    std::vector<int> freq_coll(5, 0);
    for (int i {}; i < 3; ++i) {
        passwords_digests[i] = MD5(passwords[i]).get_digest();
    }
    for (int i {}; i < 3; ++i) {
        for (int y {}; y < 5; ++y) {
            uint16_t cur_pass {slice_digest(passwords_digests[i], bits[y])};
            for (int k {}; k < 1000; ++k) {
                std::vector<uint16_t> found_digest;
                for (int j {1}; ; ++j) {
                    std::string random_password {generate_data(8)};
                    uint16_t rand_pass {slice_digest(MD5(random_password).get_digest(), bits[y])};
                    found_digest.push_back(rand_pass);
                    if (cur_pass == rand_pass) {
                        freq_proto[i][y] += j;
                        break;
                    }
                }
                freq_coll[y] += find_collisions(found_digest);
            }
        }
    }
    for (int i {}; i < 3; ++i) {
        for (int k {}; k < 5; ++k) {
            std::cout << std::dec << passwords[i] << ":" << k << ":" << freq_proto[i][k] / 1000 << std::endl;
        }
    }
    for (int k {}; k < 5; ++k) {
        std::cout << std::dec << k << ":" << freq_coll[k] << std::endl;
    }
}

int find_collisions(const std::vector<uint16_t> &found) {
    int steps {};
    for (size_t i {}; i != found.size(); ++i) {
        for (size_t j {}; j != found.size(); ++j) {
            ++steps;
            if (found[i] == found[j]) {
                return steps;
            }
        }
    }
    return 0;
}

uint16_t slice_digest(const std::array<uint8_t, 16> &digest, const size_t size) {
    uint16_t res {};
    for (int i {}, j {}; i + 8 <= size; i += 8, ++j) {
        if (size / 8 > j) {
            res <<= 8;
            res |= digest[j];
        } else {
            res <<= size % 8;
            res |= digest[j] >> (8 - size % 8);
        }
    }
    return res;
}

std::string generate_data(size_t len) {
    std::string res;
    for (int i {}; i < len; ++i) {
        res += alpha[std::rand() % alpha.size()];
    }
    return res;
}
