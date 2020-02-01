#include "functional.h"

auto compose() {
    return [](auto x){ return x; };
}

auto compose(auto f, auto... Args) {
    return [=](auto x) { return compose(Args...)(f(x)); };
}

auto lift(auto H, auto... F) {
    return [=](auto p) { return H(F(p)...); };
}

