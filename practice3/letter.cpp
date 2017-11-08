#include "std_lib_facilities.h"

int main()
{
    cout << "Enter the name of the person you want to write to\n";
    string first_name = "???";
    cin >> first_name ;
    cout << "Enter age of the recipient\n";
    int age = 0;
    cin >> age;
    if (age <0 || age >110)simple_error("you're kidding!\n");
    
    cout << "Enter the name of another friend both of you know.\n";
    string friend_name = "???";
    cin >> friend_name ; 
    cout << "Enter m if the friend is male and f if the friend is female.\n";
    char friend_sex = 0;
    cin >> friend_sex;
    
    cout << "Dear " << first_name << ",\n"
    <<"\t How are you? I am fine. I miss you. \n"
    <<"Have you seen " << friend_name << " lately?\n";
    if(friend_sex=='m')
        cout <<"If you see "<<friend_name<<" please ask him to call me.\n";
    if(friend_sex=='f')
        cout <<"If you see "<<friend_name<<" please ask her to call me.\n";
    if(friend_sex!='m'&&friend_sex!='f')
        cout <<"If you see "<<friend_name<<" please ask it to call me.\n";
    cout << "I hear you just had your birthday and you are "<<age <<" years old.\n";
    if(age<=12)cout << "Next year you will be "<< age+1<< " .\n";
    if(age == 17) cout << "Next year you will be able to vote.\n";
    if(age>=70) cout << "I hope you are enjoying your retirement.\n";
    cout <<"Yours sincerely,\n\n Paul Bätzing\n";
    
}
