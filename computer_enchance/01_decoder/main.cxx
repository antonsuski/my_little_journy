#include "x86_decoder.hxx"

#include <iostream>

int main(int argc, char const* argv[])
{
    binary_decoder::x86_decoder decoder;
    std::cout << "Hello, from decoder!" << std::endl;
    decoder.decode_instruction({ 0x89, 0xD9 });
    return 0;
}
