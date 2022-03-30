#include "filter.hpp"

namespace
{
    const int MINPARAM = 2;
    void listSetter(int32_t x, 
                    int32_t y, 
                    int squadSize, 
                    bmp::Bitmap& image, 
                    std::vector<int>& red, 
                    std::vector<int>& green, 
                    std::vector<int>& blue)
    {
        int cur = squadSize/2;
        red.clear();
        green.clear();
        blue.clear();
        for(int32_t xcur = x-cur; xcur <= x+cur; ++xcur)
        {
            for(int32_t ycur = y-cur; ycur <= y+cur; ++ycur)
            {
                if(xcur >= 0 && ycur >= 0 && xcur < image.Width() && ycur < image.Height())
                {
                    red.push_back((image.Get(xcur, ycur)).r);
                    green.push_back((image.Get(xcur, ycur)).g);
                    blue.push_back((image.Get(xcur, ycur)).b);
                }
            }
        }
    }

    void check_limits(int& current, int hight, int low)
    {
        if(current > hight)
        {
            current = hight;
        }
        else if(current < low)
        {
            current = low;
        }
    }

    void _mfilter(const std::string& inputName, const std::string& outputName, int squadSize, int limit)
    {
        bmp::Bitmap image(inputName);
        if(squadSize < 3 || squadSize % 2 == 0 || limit > squadSize * squadSize)
        {
            std::cout << "Input error" << std::endl;
            image.Save(outputName);
            return;
        }
        int cred = 0;
        int cgreen = 0; 
        int cblue = 0;
        int max = squadSize*squadSize/2+limit;
        int min = squadSize*squadSize/2-limit;
        std::vector<int> red, green, blue;
        for (int32_t y = 0; y < image.Height(); ++y)
        {
            for (int32_t x = 0; x < image.Width(); ++x)
            {
                listSetter(x, y, squadSize, image, red, green, blue);
                sort(red.begin(), red.end());
                sort(green.begin(), green.end());
                sort(blue.begin(), blue.end());
                cred = image.Get(x,y).r;
                cgreen = image.Get(x,y).g;
                cblue = image.Get(x,y).b;
                check_limits(cred, red[max], red[min]);
                check_limits(cgreen, green[max], green[min]);
                check_limits(cblue, blue[max], blue[min]);
                image.Set(x,y, bmp::Pixel(cred, cgreen, cblue));
            }
        }
        image.Save(outputName);
        return;
    }
}

int mfilter(std::stringstream& in, std::stringstream& out)
{
    std::string buf;
    std::string data[4];
    int i = 0;
    while(std::getline(in, buf))
    {
        data[i] = buf;
        i++;
    }
    
    //in >> data[0] >> data[1] >> data[2] >> data[3];
    _mfilter(data[0], data[3], std::stoi(data[1]), std::stoi(data[2]));
    return 0;
}