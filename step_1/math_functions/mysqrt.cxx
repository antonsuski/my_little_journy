#include "qtsqrt.hxx"

#include <cmath>

#ifdef USE_MYMATH
#include "mysqrt.hxx"
#endif

namespace matlib
{
double sqrt(double x)
{
#ifdef USE_MYMATH
    return detail::mysqrt(x);
#else
    return std::sqrt(x);
#endif
}
} // namespace matlib
