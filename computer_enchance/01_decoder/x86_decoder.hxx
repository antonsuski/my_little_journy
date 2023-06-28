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
#include <vector>

namespace binary_decoder
{
class x86_decoder
{
public:
    x86_decoder(/* args */);
    ~x86_decoder();

    void decode_instruction(const std::vector<uint8_t>& instruction);
};
} // namespace binary_decoder
