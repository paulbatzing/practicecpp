#include "std_lib_facilities.h"



int main()
{
    cout << "Enter a length and a unit (cm, m, in, ft) seperated by a space.\n";
    double smallest = 0.0;
    double largest  = 0.0;
    double sum = 0.0;
    
    double onem    = 100.0;//meters in cm
    double oneinch  = 2.54;// in cm
    double onefoot = oneinch*12.0;//ft in cm
    double temp = 0;
    string tempunit = " ";
    vector<double>values;
    while(cin >> temp >> tempunit){
        cout << temp <<" "<< tempunit;
        if(tempunit=="cm"){}
        else if(tempunit=="m")  temp*=onem;
        else if(tempunit=="in") temp*=oneinch;
        else if(tempunit=="ft") temp*=onefoot;
        else {cout<<"\n The unit "<<tempunit<< " cant be converted by this program and the value is rejected.\n";continue;}
        if(smallest == 0.0  ) {largest = temp;smallest = temp;}
        if(temp>largest){
            cout << " the largest so far .\n";
            largest = temp;
        }
        else if(temp<smallest){
            cout << " the smallest so far .\n";
            smallest = temp;
        }
        else cout << "\n";
        sum += temp;
        values.push_back(temp/100.0);
        
    }
    cout << "The smallest number was "<<smallest/100 << " m, the largest number was "<< largest/100<<" m, and the sum was "<<sum/100<<" m.\n";
    sort(values);
    for(double value : values) cout << value << " m\n";
    return 0;
}
