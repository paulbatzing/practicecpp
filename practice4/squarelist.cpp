#include "std_lib_facilities.h"

int square(int i){
    //produces the square of the integer i
    int squareres = 0;
    for(int j = 0;j<i;++j){
        squareres +=i;
    }
    return squareres;
}

int main()
{
    for(int i = 1;i<101;++i){
        cout << i << " " << square(i)<< "\n";
    }
    return 0;
}
