/**
 * @file ex1-3.c
 * @author Anton Syskiy
 * @brief Exercise 1.4 - Write program to print the corresponding Celsius to
 * Fahrenheit table
 * @version 0.1
 * @date 2023-02-17
 */

#include <stdio.h>

int main(int argc, char const* argv[])
{
    float fahr, celsius;
    int   lower, upper, step;

    celsius = lower = -10;
    upper           = 60;
    step            = 10;

    while (celsius <= upper)
    {
        fahr = (9.f / 5.f) * celsius + 32;
        printf("%3.1f %6.0f\n", fahr, celsius);
        celsius += step;
    }

    return 0;
}
