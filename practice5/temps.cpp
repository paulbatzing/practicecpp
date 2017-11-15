#include "std_lib_facilities.h"




int main()
{
    //test exceptions
    vector<double> temps;
    
    for(double temp; cin>>temp;)
        temps.push_back(temp);
    
    double sum          = 0;
    double high_temp    = temps[0];
    double low_temp     = temps[0];
    
    for(int x : temps)
    {
     if(x>high_temp) high_temp = x;
     if(x<low_temp)  low_temp  = x;
     sum +=x;
    }
    cout << "High temperature: "<<high_temp<<'\n';
    cout << "High temperature: "<<low_temp<<'\n';
    cout << "Average temperature: "<<sum/temps.size()<<'\n';
    return 0;
}
