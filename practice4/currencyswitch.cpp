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
    
    char incurrency  =' ';                //char to hold currency symbol
    char outcurrency =' ';
    
    cout <<"Please enter an amount of money followed by a symbol y (yen), k (danish kroner), n (norwegian kroner), s (swedish kroner), p (pound sterling), e (euro) or d (dollar):\n";
    cin >> money >> incurrency;
    
    cout << "Please enter a currency to convert to by a symbol y (yen), k (danish kroner), n (norwegian kroner), s (swedish kroner), p (pound sterling), e (euro) or d (dollar):\n";
    cin >> outcurrency;
    if(incurrency==outcurrency){
        cout << "You asked to convert " << incurrency << " to " << incurrency << ", so nothing changes and you still have " << money << " " << incurrency<< "\n"; 
        return 0;
    }    
    else{
        //convert to dollar
        switch(incurrency){
            case 'd':
                break;
            case 'y':
                money/=yrate;
                break;
            case 'k':
                money/=dkrrate;
                break;
            case 'n':
                money/=nkrrate;
                break;

            case 's':
                money/=skrrate;
                break;

            case 'p':
                money/=prate;
                break;

            case 'e':
                money/=erate;
                break;
            default:
                cout <<"Sorry, I don't know a currency called "<<incurrency<<"\n";
                return 0;
        }
    }
    //now money is in dollars
    switch(outcurrency){
        case 'd':
            cout << "You have "<<money<<" dollars.\n";
            break;
        case 'y':
            cout << "You have "<<money*yrate<<" yen.\n";
            break;
        case 'k':
            cout << "You have "<<money*dkrrate<<" danish kroners.\n";
            break;
        case 'n':
            cout << "You have "<<money*nkrrate<<" norwegian kroners.\n";
            break;
        case 's':
            cout << "You have "<<money*skrrate<<" swedish kroners.\n";
            break;
        case 'p':
            cout << "You have "<<money*prate<<" pound sterling.\n";
            break;
        case 'e':
            cout << "You have "<<money*erate<<" euros.\n";    
            break;
        default:
            cout <<"Sorry, I don't know a currency called "<<incurrency<<"\n";
            return 0;
            
    }    
    return 0;
}
