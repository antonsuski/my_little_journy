/**
 * @file ex1-3.c
 * @author Anton Syskiy
 * @brief Exercise 1.3 - Add a hiding for Celsius programm from book.
 * @version 0.1
 * @date 2023-02-17
 */

#include <stdio.h>

int main(int argc, char const* argv[])
{
    float fahr, cealsius;
    int   lower, upper, step;

    fahr = lower = 0;
    upper        = 300;
    step         = 20;

    while (fahr <= upper)
    {
        cealsius = (5.f / 9.f) * (fahr - 32.f);
        printf("%3.0f %6.1f\n", fahr, cealsius);
        fahr = fahr + step;
    }

    return 0;
}
