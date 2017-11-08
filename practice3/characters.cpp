#include "std_lib_facilities.h"

int main()
{
    int i = '!';
    while(i<'z'+5){
        cout << char(i) << " " << i << "\n";
        ++i;
    }
    return 0;
}
