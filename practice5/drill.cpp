#include "std_lib_facilities.h"




int main()
{
  try{
      cout << "1.  Success!\n";
      
      cout << "2.  Success!\n";
      
      cout << "3.  Success"<<"!\n";
      
      string success = "4.  Success!";
      cout << success<<'\n';
      
      int res=7;
      vector<int>v(10);
      v[5]=res;
      cout <<"5.  Success!\n";
      
      vector<int>v6(10);
      v6[5]=7;
      if(v6[5]!=8)cout<<"6.  Success!\n";
      
      bool cond = true;
      if(cond)cout << "7.  Success!\n";
      else cout << "Fail!\n";
      
      bool c = false;
      if(!c) cout <<"8.  Success!\n";
      else cout << "Fail\n";
      
      string s = "zape";
      bool c9 = "fool"<s;
      if(c9)cout << "9.  Success!\n";
      
      string s10 = "ape";
      if(s10!="fool")cout << "10. Success!\n";
      
      string s11 = "fool";
      if(s11=="fool")cout << "11. Success!\n";
      
      string s12 = "ape";
      if(s12<"fool")cout << "12. Success!\n";
      
      vector<char> v13(5);
      for( int i=0; i<v13.size();i++);
      cout << "13. Success!\n";

      vector<char> v14(5);
      for( int i=0; i<v14.size();i++)v14[i]=0;
      cout << "14. Success!\n";
      
      string s15 = "15. Success!\n";
      for(int i=0;i<s15.length();i++)cout << s15[i];
      
      if(true) cout <<"16. Success!\n"; 
      else cout <<"Fail!\n";
      
      int x17 = 20;
      char c17 = x17;
      if(c17==20)cout<<"17. Success!\n";
      
      string s18 = "18. Success!\n";
      for(int i=0;i<s18.length();++i){
          cout <<s18[i];
      }
      
      vector<int> v19(5); 
      for(int i=0;i<=v.size();++i);
      cout << "19. Success!\n";
      
      int i20 = 0;
      int j20 = 9;
      while(i20<10)i20++;
      if(j20<i20)cout<< "20. Success!\n";
      
      int x21 = 2;
      double d21 = 5.0/(x21);
      if(d21==x21+0.5) cout <<"21. Success!\n";
      
      vector<char> s22 = {'2','2','.',' ','S','u','c','c','e','s','s','!','\n'};
      for(int i=0;i<s22.size();i++)cout <<s22[i];
      
      int i23 = 0;
      int j23 = 9;
      while(j23<10)++j23;
      if(j23>i23)cout << "23. Success!\n";
      
      int x24 = 4;
      double d24 = 5.0/(x24-2);
      if(d24==2*x24-5.5)cout << "24. Success!\n";
      
      cout<< "25. Success!\n";
      return 0;
  }
  catch(exception& e){
      cerr<<"error: "<< e.what()<<'\n';
      return 1;
  }
  catch(...){
      cerr<<"Oops: unknown exception!\n";
      return 2;
  }
}

