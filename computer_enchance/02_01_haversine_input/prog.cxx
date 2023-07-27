#include "haversine.hxx"

#include <iostream>

int main(int argc, char* argv[])
{
    std::cout << "Hello, haversine generator!\n";
    // Haversine pairs generator
    haversine::generate(1.f);
    // Output pairs for testing
    return 0;
}
