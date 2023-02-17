/**
 * @file ex1-5.c
 * @author anton
 * @brief Modify the remperature conversion program in backward order
 * @version 0.1
 * @date 2023-02-17
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <stdio.h>

int main(int argc, char** argv)
{
    for (float celsius = 300; celsius >= -100; celsius -= 20)
    {
        printf("%4.0f %6.0f\n", (9.f / 5.f) * celsius + 32.f, celsius);
    }
    return 0;
}