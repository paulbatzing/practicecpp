#include "my.h"

int foo;

int main(){
    foo = 7;
    print_foo();
    print(99);
    
    int x = 7;
    int y = 9;
    print(x);
    print(y);
    swap_r(x,y);
    print(x);
    print(y);
    swap_v(x,y);
    print(x);
    print(y);
    
//     swap_r(7,9); Doesnt work, swap_r takes references, not literals
    swap_v(7,9);
    const int cx = 7;
    const int cy = 9;
//     print(cx);
//     print(cy);
//     swap_r(cx,cy);doesnt take constant variables as arguments
    print(cx);
    print(cy);
    swap_v(cx,cy);
    print(cx);
    print(cy);
//     swap_r(7.7,9.9);doesnt take literals
    swap_v(7.7,9.9);//works, but does nothing. 7.7 and 9.9 are trunkated into int
    
    double dx = 7.7;
    double dy = 9.9;
//     print(dx);
//     print(dy);
//     swap_r(dx,dy);//reference doesnt match type
    print(dx);
    print(dy);
    swap_v(dx,dy);
    print(dx);
    print(dy);
}
