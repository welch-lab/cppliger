#include <Rcpp.h>

#include "cppliger/myclass.h"

RCPP_MODULE(rligerModule)
{
    Rcpp::class_<CppLib::MyClass>("MyClass")
            .factory([]() -> cppliger::MyClass* {
                Rcpp::stop("Default constructor is disabled for this class");
            })
            .constructor<double>()
            .constructor<double, double>()
            .const_method("Area", &cppliger::MyClass::Area, "Returns the area of MyClass");
}

#include "rliger/myfunction.h"

//' Free function that returns the product of its two double arguments
//'
//' @return The product of its two double arguments
//'
//' @export
// [[Rcpp::export]]
double myfunction(const double a, const double b) { return cppliger::myfunction(a, b); }

#include <span>
namespace RConversions {
    namespace {
        template<typename>
        struct is_rcpp_vector : std::false_type {
        };

        template<int RTYPE, template<class> class StoragePolicy>
        struct is_rcpp_vector<Rcpp::Vector<RTYPE, StoragePolicy>> : std::true_type {
        };

        template<typename T>
        inline constexpr bool is_rcpp_vector_v = is_rcpp_vector<T>::value;

        template<typename Source>
        [[nodiscard]] auto getSpan(Source&& source)
        {
            using vector_type = std::remove_reference_t<Source>;
            static_assert(is_rcpp_vector_v<std::remove_const_t<vector_type>>);
            using value_type = std::remove_cvref_t<typename vector_type::value_type>;
            using T =
                    std::conditional_t<std::is_const_v<vector_type>, const value_type, value_type>;
            return std::span<T>(source.begin(), static_cast<std::size_t>(source.size()));
        }
    }// namespace
}// namespace RConversions
//' Free function that returns sum of two vectors elementwise
//'
//' @return The elementwise sum of its two vector arguments
//'
//' @export
// [[Rcpp::export]]
Rcpp::NumericVector vec_add(const Rcpp::NumericVector& a, const Rcpp::NumericVector& b)
{
    static_assert(std::is_same_v<std::remove_cvref_t<Rcpp::NumericVector::value_type>, double>);
    auto result = cppliger::vec_add(RConversions::getSpan(a), RConversions::getSpan(b));
    return Rcpp::wrap(result);
}

//' Free function that squares elements of a vector inplace
//'
//' @export
// [[Rcpp::export]]
void vec_square_inplace(Rcpp::NumericVector& a)
{
    cppliger::vec_square_inplace(RConversions::getSpan(a));
}
