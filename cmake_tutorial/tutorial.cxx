#include <cmath>
#include <iostream>

#include "TutorialConfig.h"
#include "matlib.hxx"

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        // report version
        std::cout << argv[0] << " Version " << Tutorial_VERSION_MAJOR << "."
                  << Tutorial_VERSION_MINOR << std::endl;
        std::cout << "Usage: " << argv[0] << " number" << std::endl;
    }

    matlib::sqrt(16.f);

    return EXIT_SUCCESS;
}