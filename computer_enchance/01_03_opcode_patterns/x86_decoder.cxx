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
#include <iomanip>
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
    { 0b1011'0000,
      "mov",
      "mov, i t r",
      {
          { ft::type::op_code, 0b1111'0000, 4 },
          { ft::type::w, 0b0000'1000, 3 },
          { ft::type::reg, 0b0000'0111, 0 },
          { ft::type::data, 0b1111'1111, 0 },
      } },
    { 0b1100'0110,
      "mov",
      "mov i t r/m",
      {
          { ft::type::op_code, 0b1111'1110, 1 },
          { ft::type::w, 0b0000'0001, 0 },
          { ft::type::mod, 0b1100'0000, 6 },
          { ft::type::any, 0b0011'1000, 3 },
          { ft::type::rm, 0b0000'0111, 0 },
          { ft::type::data, 0b1111'1111, 0 },
      } },
    { 0b1010'0000,
      "mov",
      "mov m/a t a/m",
      {
          { ft::type::op_code, 0b1111'1100, 2 },
          { ft::type::w, 0b0000'0001, 0 },
          { ft::type::reg, 0b0001'1100, 2, ft::sub_type::pattern },
          { ft::type::d, 0b0000'0010, 1 },
          { ft::type::addr, 0b1111'1111, 0 },
      } },
    { 0b00000000,
      "add",
      "mov, r/m t/f r",
      {
          { ft::type::op_code, 0b11111100, 2 },
          { ft::type::d, 0b00000010, 1 },
          { ft::type::w, 0b00000001, 0 },
          { ft::type::mod, 0b11000000, 6 },
          { ft::type::reg, 0b00111000, 3 },
          { ft::type::rm, 0b00000111, 0 },
      } },
    { 0b00000100,
      "add",
      "mov, imm to acc",
      {
          { ft::type::op_code, 0b11111110, 1 },
          { ft::type::w, 0b00000001, 0 },

          { ft::type::data, 0b1111'1111, 0 },
      } },
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

std::stringstream x86_decoder::decode(const std::vector<uint8_t>& bytes) {}

} // namespace binary_decoder
