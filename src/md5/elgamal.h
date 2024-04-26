#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/fwd.hpp>
#include <utility>

namespace mp = boost::multiprecision;

class Elgamal {
    mp::cpp_int p;
    mp::cpp_int g;
    mp::cpp_int y;

    mp::cpp_int x;
public:
    Elgamal();
    std::pair<mp::cpp_int, mp::cpp_int> encrypt(std::string const &);
    mp::cpp_int decrypt(std::pair<mp::cpp_int, mp::cpp_int>);
    std::pair<mp::cpp_int, mp::cpp_int> signature(std::string const &);
    bool signature_auth(std::string const &, std::pair<mp::cpp_int, mp::cpp_int>);
private:
    void generate_keys();
    mp::cpp_int power_mod(mp::cpp_int, mp::cpp_int, mp::cpp_int);
    mp::cpp_int generate_prime();
    mp::cpp_int gcd(mp::cpp_int, mp::cpp_int);
    mp::cpp_int extended_gcd(mp::cpp_int, mp::cpp_int, mp::cpp_int &, mp::cpp_int &);
    mp::cpp_int mod_reverse(mp::cpp_int, mp::cpp_int);
    bool is_prime(mp::cpp_int const &);
};
