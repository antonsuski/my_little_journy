/**
 * @file x86_decoder.cxx
 * @author Anton Suskiy (antonsyski@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-06-27
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "x86_decoder.hxx"

#include <algorithm>
#include <iostream>
#include <map>

using ft = binary_decoder::filed;

static inline std::vector<binary_decoder::x86_instruction> instructions_map{
    { 0b100010,
      "mov",
      "mov, r/m t/f r",
      { { ft::type::op_code, 1, 6 },
        { ft::type::d, 2, 1 },
        { ft::type::w, 3, 1 },
        { ft::type::mod, 4, 2 },
        { ft::type::reg, 5, 3 },
        { ft::type::rm, 6, 3 },
        { ft::type::disp, 7, 0 } } }
};

static inline std::map<uint8_t, std::string> regs_map{
    { 0b0000, "al" }, { 0b0001, "cl" }, { 0b0010, "dl" }, { 0b0011, "bl" },
    { 0b0100, "ah" }, { 0b0101, "ch" }, { 0b0110, "dh" }, { 0b0111, "bh" },
    { 0b1000, "ax" }, { 0b1001, "cx" }, { 0b1010, "dx" }, { 0b1011, "bx" },
    { 0b1100, "sp" }, { 0b1101, "bp" }, { 0b1110, "si" }, { 0b1111, "di" },
};

// for case where mod = 11 use regs_map (the registry positions same)
static inline std::map<uint8_t, std::string> ef_map{
    { 0b0000, "bx + si" }, { 0b0001, "bx + di" }, { 0b0010, "bp + si" },
    { 0b0011, "bp + di" }, { 0b0100, "si" },      { 0b0101, "di" },
    { 0b0110, "dp" },      { 0b0111, "bx" },
};

namespace binary_decoder
{
x86_decoder::x86_decoder(/* args */) {}
x86_decoder::~x86_decoder() {}

std::stringstream x86_decoder::decode(const std::vector<uint8_t>& bytes)
{
    std::stringstream decoded_instructions_buffer;
    decoder_context   context;

    for (auto&& i : bytes)
    {
        std::vector<x86_instruction>::iterator instruction =
            std::find_if(instructions_map.begin(), instructions_map.end(),
                         [&](const x86_instruction& inst) -> bool
                         {
                             uint8_t tmp_inst = i;
                             tmp_inst >>= (BYTE_SIZE - inst.fileds[0].lenth);
                             return inst.code == tmp_inst;
                         });
        std::cout << std::hex << +i << ": ";

        if (instruction != instructions_map.end())
        {
            int instruction_size{ 0 };

            for (auto&& filed : instruction->fileds)
            {
                switch (filed.type)
                {
                    case ft::type::w:
                    {
                    }
                    break;

                    default:
                        break;
                }
            }

            std::cout << instruction->description << " "
                      << instruction_size / BYTE_SIZE;
        }
        std::cout << std::endl;
    }

    return decoded_instructions_buffer;
}

} // namespace binary_decoder
