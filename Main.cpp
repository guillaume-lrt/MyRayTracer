#include <iostream>
#include "Image.hpp"
#include <cmath>
#include "Vec3.h"

int main()
{
    Image image = Image(10000,10000);
    image.fillBackground();
    image.savePPM("image.ppm");
    return 0;
}