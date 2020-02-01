#ifndef FUNCTIONAL_H
#define FUNCTIONAL_H

#include <functional>

auto compose();
auto compose(auto f, auto... Args);

auto lift(auto H, auto... F);

#endif
