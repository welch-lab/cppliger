#include "cppliger/myfunction.h"
#include <algorithm>
#include <functional>
#include <stdexcept>

double cppliger::myfunction(double a, double b) { return a * b; }
std::vector<double> cppliger::vec_add(const std::span<const double> a,
                                    const std::span<const double> b)
{
    if (a.size() != b.size())
        throw std::runtime_error("Vectors a and b have different sizes");
    std::vector<double> ret(a.begin(), a.end());
    std::transform(a.begin(), a.end(), b.begin(), ret.begin(), std::plus<>{});
    return ret;
}
void cppliger::vec_square_inplace(std::span<double> a)
{
    for (auto& e : a) e *= e;
}
