#include "std_lib_facilities.h"


int area(int length,int width){
    if(length<=0||width<=0)return -1;
    return length*width;
}

constexpr int frame_width = 2;

int framed_area(int x, int y){
    return area(x-frame_width,y-frame_width);
}

int f(int x, int y, int z){
        int area1 = area(x,y);
        if(area1<=0) error("non-positive area");
        int area2 = framed_area(1,z);
        int area3 = framed_area(y,z);
        double ratio
}

int main()
{
    //test compiler errors

    return 0;
}
