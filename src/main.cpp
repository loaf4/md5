#include "md5.h"
#include "elgamal.h"

#include <boost/multiprecision/fwd.hpp>
#include <iostream>
#include <utility>

namespace mp = boost::multiprecision;

int main(int argc, char* argv[]) {

    Elgamal e;

    std::cout << "Message: 123456789" << std::endl << "Decrypted message: ";
    std::pair<mp::cpp_int, mp::cpp_int> key = e.encrypt("123456789");
    mp::cpp_int res = e.decrypt(key);
    std::cout << res << std::endl;

    std::cout << "Message for signature: 1234" << std::endl;
    std::pair<mp::cpp_int, mp::cpp_int> sign = e.signature("1234");
    std::cout << "Trying to auth with: 12345, res = " << e.signature_auth("12345", sign) << std::endl;
    std::cout << "Trying to auth with: 1234, res = " << e.signature_auth("1234", sign) << std::endl;

    return 0;
}

