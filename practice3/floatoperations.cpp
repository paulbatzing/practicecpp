#include "std_lib_facilities.h"

int main()
{
   cout << "please enter a floating-point value: ";
   double n;
   cin >> n;
   
   cout << "n==" <<n
        <<"\nn+1 == "<<n+1 
        <<"\nnthree times n == " <<3*n 
        <<"\ntwice n == "<<n+n 
        <<"\nn squared == "<< n*n
        <<"\nhalf of n == "<<n/2 
        <<"\nsquareroot of n == "<<sqrt(n)
        <<'\n';
    
    
}
