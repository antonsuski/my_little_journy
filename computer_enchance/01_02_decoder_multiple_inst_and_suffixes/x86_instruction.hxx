#pragma once

#include <bitset>
#include <iomanip>
#include <iostream>
#include <string_view>
#include <vector>

namespace binary_decoder
{

struct x86_instruction
{

    unsigned int byte;
    unsigned int base;

    std::string_view name;

    friend bool operator==(const x86_instruction& lhs,
                           const x86_instruction& rhs);
};

bool operator==(const x86_instruction& lhs, const x86_instruction rhs)
{
    return (lhs.byte == rhs.byte) || (lhs.name == rhs.name);
}

bool operator==(const x86_instruction& lhs, const uint8_t byte)
{
    return lhs.byte == static_cast<unsigned int>(byte);
}

std::ostream& operator<<(std::ostream& out, const x86_instruction& instruction)
{
    return out << std::setw(4) << std::bitset<8>{ instruction.byte } << " "
               << std::setw(4) << instruction.name;
}

} // namespace binary_decoder
