#ifndef IMAGES_H
#define IMAGES_H

#include "color.h"
#include "coordinate.h"
#include "functional.h"

namespace Detail {
    Point polar(const Point p);
    Point cartesian(const Point p);

    double square(double a);

    double dist_squared(Point a, Point b);
}

using Fraction = long double;

template<typename T>
using Base_image = std::function<T(const Point)>;

using Region = Base_image<bool>;
using Image = Base_image<Color>;
using Blend = Base_image<Fraction>;

template<typename T>
Base_image<T> constant(const T value) {
    return [=](const Point){ return value; };
}

template<typename T>
Base_image<T> rotate(Base_image<T> image, double phi) {
    return [=](const Point p) {
        return image(
            Point(
                Detail::polar(p).first,
                Detail::polar(p).second - phi,
                true
            )
        );
    };
}

template<typename T>
Base_image<T> translate(Base_image<T> image, Vector v) {
    return [=](const Point p) {
        return image(
            Point(
                Detail::cartesian(p).first - v.first,
                Detail::cartesian(p).second - v.second,
                false
            )
        );
    };
}

template<typename T>
Base_image<T> scale(Base_image<T> image, double s) {
    return [=](const Point p) {
        return image(
            Point(
                Detail::cartesian(p).first / s,
                Detail::cartesian(p).second / s,
                false
            )
        );
    };
}

template<typename T>
Base_image<T> circle(Point q, double r, T inner, T outer) {
    return [=](const Point p) {
        return Detail::dist_squared(p, q) > r * r ? outer : inner;
    };
}

template<typename T>
Base_image<T> checker(double d, T this_way, T that_way) {
    return [=](const Point p) {
        return static_cast<int>(floor(Detail::cartesian(p).first / d) +
            floor(Detail::cartesian(p).second / d)) % 2 == 0 ?
        this_way : that_way;
    };
}

template<typename T>
Base_image<T> polar_checker(double d, int n, T this_way, T that_way) {
    return [=](const Point p) {
        return checker(d, this_way, that_way)(
            Point(
                Detail::polar(p).first,
                (Detail::polar(p).second / (2.0 * M_PI)) * (d * n),
                false
            ));
    };
}

template<typename T>
Base_image<T> rings(Point q, double d, T this_way, T that_way) {
    return [=](const Point p) {
        return static_cast<int>(floor(sqrt(Detail::dist_squared(p, q)) / d)) % 2 == 0 ?
        this_way : that_way;
    };
}

template<typename T>
Base_image<T> vertical_stripe(double d, T this_way, T that_way) {
    return [=](const Point p) {
        return abs(Detail::cartesian(p).first) > d / 2 ? that_way : this_way;
    };
}

Image cond(Region region, Image this_way, Image that_way);

Image lerp(Blend blend, Image this_way, Image that_way);

Image darken(Image image, Blend blend);
Image lighten(Image image, Blend blend);

#endif // _IMAGES_H
