#include "md5.h"
#include "elgamal.h"
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/detail/integer_ops.hpp>
#include <boost/multiprecision/fwd.hpp>
#include <boost/multiprecision/miller_rabin.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <ctime>
#include <iostream>
#include <utility>

namespace mp = boost::multiprecision;

Elgamal::Elgamal() {
    generate_keys();
}

std::pair<mp::cpp_int, mp::cpp_int> Elgamal::encrypt(std::string const &message) {
    mp::cpp_int m(message);
    mp::cpp_int k;
    do {
        k = generate_prime();
    } while (k >= p && gcd(k, p - 1) > 1);

    mp::cpp_int a = power_mod(g, k, p);
    mp::cpp_int b = (power_mod(y, k, p) * power_mod(m, 1, p)) % p;

    return {a, b};
}

mp::cpp_int Elgamal::decrypt(std::pair<mp::cpp_int, mp::cpp_int> key) {
    return (power_mod(key.second, 1, p) * power_mod(key.first, p - 1 - x, p) % p);
}

std::pair<mp::cpp_int, mp::cpp_int> Elgamal::signature(std::string const &message) {
    MD5 md5(message);
    mp::cpp_int m(md5.hex_string_digest());
    mp::cpp_int k;
    do {
        k = generate_prime();
    } while (k >= p - 1 && gcd(k, p - 1) == 1);

    mp::cpp_int r = power_mod(g, k, p);
    mp::cpp_int k_gcd = mod_reverse(k, p - 1);

    mp::cpp_int tmp = (m - ((x * r) % (p - 1)));
    if (tmp < 0) { tmp += (p - 1); }
    mp::cpp_int s = (tmp * k_gcd) % (p - 1);

    return {r, s};
}

bool Elgamal::signature_auth(std::string const &message, std::pair<mp::cpp_int, mp::cpp_int> sign) {
    if (!(0 < sign.first && sign.first < p && 0 < sign.second && sign.second < p - 1)) { return false; }
    MD5 md5(message);
    mp::cpp_int m(md5.hex_string_digest());

    return ((power_mod(y, sign.first, p) * power_mod(sign.first, sign.second, p) % p) == power_mod(g, m, p));
}

void Elgamal::generate_keys() {
    p = generate_prime();

    do {
        g = generate_prime();
    } while (g >= p && gcd(g, p) > 1);

    do {
        x = generate_prime();
    } while (x >= p - 1);

    y = power_mod(g, x, p);
}

mp::cpp_int Elgamal::power_mod(mp::cpp_int g, mp::cpp_int x, mp::cpp_int p) {
    mp::cpp_int res = 1;

    while (x > 0) {
        if (x % 2 == 1) {
            res = (res * g) % p;
        }
        g = (g * g) % p;
        x /= 2;
    }

    return res;
}

mp::cpp_int Elgamal::generate_prime() {
    boost::random::mt19937 mt(std::time(0));
    boost::random::uniform_int_distribution<mp::cpp_int> gen(mp::cpp_int(2), mp::cpp_int(1) << 256);

    mp::cpp_int res;
    while (true) {
        res = gen(mt);
        if (is_prime(res)) { break; }
    }
    return res;
}

mp::cpp_int Elgamal::gcd(mp::cpp_int a, mp::cpp_int b) {
    if (a < b) {
        a += b;
        b = a - b;
        a -= b;
    }
    if (b == 0) { return a; }

    while (a % b != 0) {
        a += b;
        b = a - b;
        a -= b;
        b %= a;
    }
    return b;
}

mp::cpp_int Elgamal::extended_gcd(mp::cpp_int a, mp::cpp_int b, mp::cpp_int &x, mp::cpp_int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    mp::cpp_int x1, y1, gcd = extended_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

mp::cpp_int Elgamal::mod_reverse(mp::cpp_int a, mp::cpp_int m) {
    mp::cpp_int a_mp = a;
    mp::cpp_int m_mp = m;

    mp::cpp_int x, y;
    mp::cpp_int gcd = extended_gcd(a_mp, m_mp, x, y);

    if (gcd != 1) { return 0; }
    if (x < 0) { x += m_mp; }

    return x;
}

bool Elgamal::is_prime(mp::cpp_int const &n) {
    return mp::miller_rabin_test(n, 25);
}
