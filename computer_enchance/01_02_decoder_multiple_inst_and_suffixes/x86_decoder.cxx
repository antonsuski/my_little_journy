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
#include <bitset>
#include <iostream>
#include <map>

using ft = binary_decoder::field;

static inline std::vector<binary_decoder::x86_instruction> instructions_map{
    { 0b10001000,
      "mov",
      "mov, r/m t/f r",
      { { ft::type::op_code, 0b11111100, 2 },
        { ft::type::d, 0b00000010, 1 },
        { ft::type::w, 0b00000001, 0 },
        { ft::type::mod, 0b11000000, 6 },
        { ft::type::reg, 0b00111000, 3 },
        { ft::type::rm, 0b00000111, 0 },
        { ft::type::disp, 0b0, 0 } } }
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

    std::vector<uint8_t>::const_iterator i;

    for (i = bytes.begin(); i <= bytes.end(); ++i)
    {
        std::vector<x86_instruction>::iterator instruction =
            std::find_if(instructions_map.begin(), instructions_map.end(),
                         [&](const x86_instruction& inst) -> bool {
                             return inst.code == (*i & inst.fields[0].bit_mask);
                         });

        std::cout << std::bitset<8>{ *i } << ": ";

        if (instruction != instructions_map.end())
        {
            uint8_t byte_indecator{ 0b0000'0000 };

            for (auto&& field : instruction->fields)
            {
                switch (field.type)
                {
                    case ft::op_code:
                    {
                        byte_indecator |= field.bit_mask;
                    }
                    break;
                    case ft::type::d:
                    {
                        context.d       = true;
                        context.d_field = (*i & field.bit_mask);
                        context.d_field >>= field.pos;
                        byte_indecator |= field.bit_mask;
                    }
                    break;
                    case ft::type::w:
                    {
                        context.w       = true;
                        context.w_field = (*i & field.bit_mask);
                        context.w_field >>= field.pos;
                        byte_indecator |= field.bit_mask;
                    }
                    break;
                    case ft::type::mod:
                    {
                        context.mod       = true;
                        context.mod_field = (*i & field.bit_mask);
                        context.mod_field >>= field.pos;
                        byte_indecator |= field.bit_mask;
                    }
                    break;
                    case ft::type::reg:
                    {
                        context.reg       = true;
                        context.reg_field = (*i & field.bit_mask);
                        context.reg_field >>= field.pos;
                        byte_indecator |= field.bit_mask;
                    }
                    break;
                    case ft::type::rm:
                    {
                        context.rm       = true;
                        context.rm_field = (*i & field.bit_mask);
                        context.rm_field >>= field.pos;
                        byte_indecator |= field.bit_mask;
                    }
                    break;
                    case ft::type::disp:
                    {
                        switch (context.mod_field)
                        {
                            case 0b11:
                            {
                                context.disp = false;
                                --i;
                            }
                            break;

                            default:
                                break;
                        }
                    }
                    break;
                    default:
                        break;
                }
                if (byte_indecator == 0b1111'1111)
                {
                    ++i;
                    byte_indecator = 0b0000'0000;
                }
            }

            std::cout << instruction->description << " ";
            std::cout << " d: " << context.d << "/"
                      << std::bitset<8>{ context.d_field }
                      << " w: " << context.w << "/"
                      << std::bitset<8>{ context.w_field }
                      << " mod: " << context.mod << "/"
                      << std::bitset<8>{ context.mod_field }
                      << " reg: " << context.reg << "/"
                      << std::bitset<8>{ context.reg_field }
                      << " rm: " << context.rm << "/"
                      << std::bitset<8>{ context.rm_field }
                      << " disp: " << context.disp << "/"
                      << std::bitset<8>{ context.disp_field };
        }
        std::cout << std::endl;
    }

    return decoded_instructions_buffer;
}

} // namespace binary_decoder
