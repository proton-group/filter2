#include "filter.hpp"

const int MINPARAM = 2;

int main(int argc, char* argv[])
{
    if(argc < MINPARAM)
    {
        return -1;
    }
    std::string buf;
    std::string data[4];
    std::stringstream in_str;
    std::stringstream out_str;
    std::ifstream in(argv[1]); // окрываем файл для чтения
    if (in.is_open())
    {
        int i = 0;
        while(std::getline(in, buf))
        {
            in_str << buf + "\n";
            i++;
        }
    }
    in.close();
    filter_from_stream(in_str, out_str);
    return;
}