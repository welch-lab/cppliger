#include "cppliger/myclass.h"

cppliger::MyClass::MyClass(double a)
    : a_(a), b_(a)
{}

cppliger::MyClass::MyClass(double a, double b)
    : a_(a), b_(b)
{}

double cppliger::MyClass::Area() const {
    return a_ * b_;
}
