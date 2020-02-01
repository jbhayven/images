#include "images.h"

namespace Detail {
    Point polar(const Point p) {
        return p.is_polar ? p : to_polar(p);
    }

    Point cartesian(const Point p) {
        return p.is_polar ? from_polar(p) : p;
    }

    double square(double a) {
        return a * a;
    }

    double dist_squared(Point a, Point b) {
        return square(cartesian(a).first - cartesian(b).first) +
               square(cartesian(a).second - cartesian(b).second);
    }
}

Image cond(Region region, Image this_way, Image that_way) {
    return [=](const Point p) {
        return region(p) ? this_way(p) : that_way(p);
    };
}

Image lerp(Blend blend, Image this_way, Image that_way) {
    return [=](const Point p) {
        return that_way(p).weighted_mean(this_way(p), blend(p));
    };
}

Image darken(Image image, Blend blend) {
    return lerp(blend, image, constant(Colors::black));
}

Image lighten(Image image, Blend blend) {
    return lerp(blend, image, constant(Colors::white));
}
