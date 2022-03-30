#include "filter.hpp"
#include <sstream>
#include <gtest/gtest.h>

bmp::Bitmap image_create()
{
    bmp::Bitmap image(3, 3);
    bmp::Pixel point1 {std::uint8_t(1), std::uint8_t(1), std::uint8_t(1)};
    bmp::Pixel point2 {std::uint8_t(2), std::uint8_t(3), std::uint8_t(4)};
    image.Set(0,0, point2);
    image.Set(0,1, point2);
    image.Set(0,2, point2);
    image.Set(1,0, point2);
    image.Set(1,1, point1);
    image.Set(1,2, point2);
    image.Set(2,0, point2);
    image.Set(2,1, point2);
    image.Set(2,2, point2);
    return image;
}

TEST(Filter, IO)
{
    std::stringstream teststream;
    std::stringstream out;
    bmp::Bitmap image = image_create();
    image.Save("test_image.bmp");
    teststream << "test_image.bmp\n" << "3\n" << "3\n" << "test.bmp\n";
    filter_from_stream(teststream, out);
    std::string buf;
    std::getline(out, buf);
    ASSERT_EQ(buf, "File loaded.");
    std::getline(out, buf);
    ASSERT_EQ(buf, "Image saved.");
}

TEST(Filter, InputInvalid)
{
    std::stringstream teststream;
    std::stringstream out;
    teststream << "test_image.bmp\n" << "4\n" << "3\n" << "test.bmp\n";
    filter_from_stream(teststream, out);
    std::string buf;
    std::getline(out, buf);
    ASSERT_EQ(buf, "Input error.");
    std::stringstream teststream2;
    std::stringstream out2;
    teststream2 << "NotExist.bmp\n" << "3\n" << "3\n" << "test.bmp\n";
    filter_from_stream(teststream2, out2);
    std::getline(out2, buf);
    ASSERT_EQ(buf, "Bitmap::Load(\"NotExist.bmp\"): Failed to load bitmap pixels from file.");
}

TEST(Filter, Algorithm)
{
    bmp::Bitmap image = image_create();
    filter_from_image(image, 3, 1);
    ASSERT_EQ(image.Get(1,1).r, 2);
    ASSERT_EQ(image.Get(1,1).g, 3);
    ASSERT_EQ(image.Get(1,1).b, 4);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}