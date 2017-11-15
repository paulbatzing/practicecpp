#include "std_lib_facilities.h"


int area(int length,int width){
    return length*width;
}

int main()
{
    //test compiler errors
//     int s1 = area(7;
//     int s2 = area(7)
//     Int s3 = area(7);
//     int s4 = area('7);
//     int x0 = arena(7);
//     int x1 = area(7);
    int x2 = area("seven",2);
    return 0;
}
