#include "std_lib_facilities.h"

int main()
{
    //all conversion rates from 11-07-17
    constexpr double yrate      = 114.23;   //conversion rate, 1 dollar in yen
    constexpr double dkrrate    = 6.43;     //conversion rate, 1 dollar in danish kroner
    constexpr double nkrrate    = 8.17;     //conversion rate, 1 dollar in swedish kroner
    constexpr double skrrate    = 8.43;     //conversion rate, 1 dollar in norwegian kroner
    constexpr double prate      = 0.76;     //conversion rate, 1 dollar in pund
    constexpr double erate      = 0.86;     //conversion rate, 1 dollar in euro
    
    
    double money = 1;                       //money in any currency
    
    string incurrency  =" ";                //string to hold currency name
    string outcurrency =" ";
    
    cout <<"Please enter an amount of money followed by the currency (yen, dkr, nkr, skr, pound, euro or dollar):\n";
    cin >> money >> incurrency;
    
    cout << "Please enter a currency to convert to (yen, dkr, nkr, skr, pound, euro or dollar):\n";
    cin >> outcurrency;
    if(incurrency==outcurrency){
        cout << "You asked to convert " << incurrency << " to " << incurrency << ", so nothing changes and you still have " << money << " " << incurrency<< "\n"; 
        return 0;
    }
    else{
        //convert to dollar
        if(incurrency=="dollar");
        else if(incurrency=="yen")money/=yrate;
        else if(incurrency=="dkr")money/=dkrrate;
        else if(incurrency=="nkr")money/=nkrrate;
        else if(incurrency=="skr")money/=skrrate;
        else if(incurrency=="pound")money/=prate;
        else if(incurrency=="euro")money/=erate;
        else {cout <<"Sorry, I don't know a currency called "<<incurrency<<"\n";return 0;}
    }
    //now money is in dollars
    if(outcurrency=="dollar")cout << "You have "<<money<<" dollars.\n";
    else if(outcurrency=="yen")cout << "You have "<<money*yrate<<" yen.\n";
    else if(outcurrency=="dkr")cout << "You have "<<money*dkrrate<<" danish kroners.\n";
    else if(outcurrency=="nkr")cout << "You have "<<money*nkrrate<<" norwegian kroners.\n";
    else if(outcurrency=="skr")cout << "You have "<<money*skrrate<<" swedish kroners.\n";
    else if(outcurrency=="pound")cout << "You have "<<money*prate<<" pound sterling.\n";
    else if(outcurrency=="euro")cout << "You have "<<money*erate<<" euros.\n";    
    else {cout <<"Sorry, I don't know a currency called "<<outcurrency<<"\n";return 0;}
    return 0;
}
