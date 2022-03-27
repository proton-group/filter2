#include "filter.hpp"
#include <sstream>

int main()
{
    std::stringstream teststream;
    bmp::Bitmap image(30, 30);
    for (int32_t y = 0; y < image.Height(); ++y)
    {
        for (int32_t x = 0; x < image.Width(); ++x)
        {
            bmp::Pixel point(x, x, x);
            image.Set(x, y, point);
        }
    }
    image.Save("aboba_test.bmp");
    teststream << "aboba_filtred.bmp" << 4 << 3 << "aboba_test.bmp";
    mfilter(teststream);
}