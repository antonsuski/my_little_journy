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
#include <cstring>
#include <iostream>
#include <map>

using ft = binary_decoder::field;

static inline std::vector<binary_decoder::x86_instruction> instructions_map{
    { 0b10001000,
      "mov",
      "mov, r/m t/f r",
      {
          { ft::type::op_code, 0b11111100, 2 },
          { ft::type::d, 0b00000010, 1 },
          { ft::type::w, 0b00000001, 0 },
          { ft::type::mod, 0b11000000, 6 },
          { ft::type::reg, 0b00111000, 3 },
          { ft::type::rm, 0b00000111, 0 },
      } },
    // { 0b1011'0000,
    //   "mov",
    //   "mov, i t r",
    //   {
    //       { ft::type::op_code, 0b1111'0000, 4 },
    //       { ft::type::w, 0b0000'1000, 3 },
    //       { ft::type::reg, 0b0000'0111, 0 },
    //       { ft::type::data, 0b0, 0 },
    //   } },
    // { 0b1100'0110,
    //   "mov",
    //   "mov i t r/m",
    //   {
    //       { ft::type::op_code, 0b1111'1110, 1 },
    //       { ft::type::w, 0b0000'0001, 0 },
    //       { ft::type::mod, 0b1100'0000, 6 },
    //       { ft::type::any, 0b0011'1000, 3 },
    //       { ft::type::rm, 0b0000'0111, 0 },
    //       { ft::type::data, 0b0, 0 },
    //   } },
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
    { 0b0110, "bp" },      { 0b0111, "bx" },
};

namespace binary_decoder
{
x86_decoder::x86_decoder(/* args */) {}
x86_decoder::~x86_decoder() {}

std::stringstream x86_decoder::decode(const std::vector<uint8_t>& bytes)
{
    std::stringstream decoded_instructions_buffer;

    std::vector<uint8_t>::const_iterator i;

    for (i = bytes.begin(); i <= bytes.end(); ++i)
    {
        std::vector<x86_instruction>::iterator instruction =
            std::find_if(instructions_map.begin(), instructions_map.end(),
                         [&](const x86_instruction& inst) -> bool {
                             return inst.code == (*i & inst.fields[0].bit_mask);
                         });

        decoder_context context{};
        std::string     buffer{};

        if (instruction != instructions_map.end())
        {
            uint8_t byte_indicator{ 0b0000'0000 };

            for (std::vector<field>::iterator field_iter =
                     instruction->fields.begin();
                 field_iter <= instruction->fields.end(); field_iter++)
            {
                buffer += std::bitset<8>{ *i }.to_string();

                switch (field_iter->type)
                {
                    case ft::op_code:
                    {
                        context.instruction_buffer = instruction->name;
                        buffer += context.instruction_buffer;
                    }
                    break;
                    case ft::d:
                    {
                        context.d       = true;
                        context.d_field = (*i & field_iter->bit_mask);
                        context.d_field >>= field_iter->pos;
                        buffer += " d:" +
                                  std::bitset<1>{ context.d_field }.to_string();
                    }
                    case ft::w:
                    {
                        context.w       = true;
                        context.w_field = (*i & field_iter->bit_mask);
                        context.w_field >>= field_iter->pos;
                        buffer += " w:" +
                                  std::bitset<1>{ context.w_field }.to_string();
                    }
                    default:
                        break;
                }

                byte_indicator |= field_iter->bit_mask;
                if (byte_indicator == 0b1111'1111 &&
                    field_iter != instruction->fields.end())
                {
                    ++i;
                    byte_indicator = { 0b0000'0000 };
                    std::cout << buffer << std::endl;
                    buffer.clear();
                }
            }
        }

        std::cout << std::bitset<8>{ *i } << std::endl;
    }

    return decoded_instructions_buffer;
}

} // namespace binary_decoder
