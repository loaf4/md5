#include "md5.h"
#include "analysis.h"

#include <iostream>

int main(int argc, char* argv[]) {

    std::string aa("");
    MD5 a(aa);
    std::cout << "input: " << aa << std::endl << "hash: ";
    a.print_hash();
    std::cout << std::string(100, '-') << std::endl;
    std::string bb("md5");
    MD5 b(bb);
    std::cout << "input: " << bb << std::endl << "hash: ";
    b.print_hash();
    std::cout << std::string(100, '-') << std::endl;
    std::string cc("hello world");
    MD5 c(cc);
    std::cout << "input: " << cc << std::endl << "hash: ";
    c.print_hash();
    std::cout << std::string(100, '-') << std::endl;

    second_prototype();

    return 0;
}

