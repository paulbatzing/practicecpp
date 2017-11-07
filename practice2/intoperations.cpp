#include "std_lib_facilities.h"

int main()
{
   cout << "please enter an integer value: ";
   int  n;
   cin >> n;
   double nd = n;
   
   cout << "n==" <<n
        <<"\nn+1 == "<<n+1 
        <<"\nnthree times n == " <<3*n 
        <<"\ntwice n == "<<n+n 
        <<"\nn squared == "<< n*n
        <<"\nhalf of n == "<<n/2 
        <<"\nsquareroot of n == "<<sqrt(nd)
        <<'\n';
    
    
}
