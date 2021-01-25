#include <cmath>
#include <iostream>

#include "TutorialConfig.h"

#ifdef USE_MYMATH
#include "qtsqrt.hxx"
#endif

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        // report version
        std::cout << argv[0] << " Version " << Tutorial_VERSION_MAJOR << "."
                  << Tutorial_VERSION_MINOR << std::endl;
        std::cout << "Usage: " << argv[0] << " number" << std::endl;
    }

#ifdef USE_MYMATH
    std::cout << lol(4) << std::endl;
#else
    std::cout << sqrt(4) << std::endl;
#endif

    return EXIT_SUCCESS;
}
