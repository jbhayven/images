#include "functional.h"
#include "images.h"
#include "bmp.h"
#include "color.h"
#include "coordinate.h"
#include <cassert>
#include <cmath>
#include <cstdint>

int main()
{
  const uint32_t width = 400;
  const uint32_t height = 300;
  const Region rc = circle(Point(50., 100.), 10., true, false);
  const Image vs = vertical_stripe(100, Colors::Caribbean_blue, Colors::blue);
  const Blend cb = constant<Fraction>(.42);

  create_BMP("constant.bmp",
             width,
             height,
             constant(Colors::Caribbean_blue));
  create_BMP("rotate.bmp",
             width,
             height,
             rotate(vs, M_PI / 4.));
  create_BMP("translate.bmp",
             width,
             height,
             translate(vs, Vector(100., 0.)));
  create_BMP("scale.bmp",
             width,
             height,
             scale(vs, 2.));
  create_BMP("circle.bmp",
             width,
             height,
             circle(Point(50., 100.), 10., Colors::Caribbean_blue, Colors::blue));
  create_BMP("checker.bmp",
             width,
             height,
             checker(10., Colors::Caribbean_blue, Colors::blue));
  create_BMP("polar_checker.bmp",
             width,
             height,
             polar_checker(10., 4, Colors::Caribbean_blue, Colors::blue));
  create_BMP("rings.bmp",
             width,
             height,
             rings(Point(50., 100.), 10., Colors::Caribbean_blue, Colors::blue));
  create_BMP("vertical_stripe.bmp",
             width,
             height,
             vs);
    return 0;
}
