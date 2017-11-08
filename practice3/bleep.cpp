#include "std_lib_facilities.h"

vector<string> bleep(vector<string> text, vector<string>bleepwords){
    //returns the text with all bleepwords replaced by BLEEP
    sort(bleepwords);
    vector<string> bleepedtext;
    for(string word : text){
        for(string bleepword : bleepwords){
            if(bleepword<word){}//the bleepword is still lower in alphabet then word
            else if(word == bleepword){word = "BLEEP"; break;}
            else {break;} //the word is fine, dont replace.
        }
        bleepedtext.push_back(word);
    }
    return bleepedtext;
}

int main()
{
    vector<string> bleepwords = {"broccoli", "fucking", "cola","zeitgeist"};
    vector<string> text;
    for(string temp; cin>>temp;)text.push_back(temp);
    for(string word : bleep(text,bleepwords))cout << word << " ";
    cout << "\n";
    return 0;
}
