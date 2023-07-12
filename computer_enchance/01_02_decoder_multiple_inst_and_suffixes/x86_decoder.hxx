/**
 * @file x86_decoder.hxx
 * @author Anton Suskiy (antonsyski@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-06-27
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <cstdint>
#include <sstream>
#include <string>
#include <vector>

namespace binary_decoder
{
#define BYTE_SIZE 8

struct decoder_context
{
    bool d{ false };
    bool w{ false };
    bool mod{ false };
    bool reg{ false };
    bool rm{ false };
    bool disp{ false };
};

struct filed
{
    enum type
    {
        none    = 0,
        op_code = 1,
        d       = 2,
        w       = 3,
        mod     = 4,
        reg     = 5,
        rm      = 6,
        disp    = 7,
    };

    type   type{};
    int8_t pos{};
    int8_t lenth{};
};

struct x86_instruction
{
    uint8_t            code{};
    std::string        name{};
    std::string        description{};
    std::vector<filed> fileds{};
};

class x86_decoder
{
public:
    x86_decoder(/* args */);
    ~x86_decoder();

    std::stringstream decode(const std::vector<uint8_t>& bytes);
};
} // namespace binary_decoder
