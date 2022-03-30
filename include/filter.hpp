#pragma once
#include "BitmapPlusPlus.hpp"
#include <vector>
#include <iostream>
#include <sstream>

void filter_from_stream(std::stringstream& in, std::stringstream& out);

void filter_from_image(bmp::Bitmap& image, int squadSize, int limit);