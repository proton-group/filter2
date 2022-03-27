#include "filter.hpp"

const int MINPARAM = 2;

int main(int argc, char* argv[])
{
    if(argc < MINPARAM)
    {
        return -1;
    }
    std::ifstream in(argv[1]); // окрываем файл для чтения
    return mfilter(in);
}