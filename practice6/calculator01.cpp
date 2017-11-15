#include "std_lib_facilities.h"

class Token
{
    public:
        char kind;                  //'8' for number, characters represent themselves.
        double value;
    
};

class Token_stream
{
    public:
        Token get();                //get a token
        void putback(Token t);      //put a token back
    private:
        bool full{false};           //Is there a Token in the buffer?
        Token buffer;
};

void Token_stream::putback(Token t)
{
    buffer = t;                     //copy to buffer
    full   = true;                  //buffer is full
}

Token Token_stream::get()
{
    if(full){                       //is there a token ready?
        full = false;               //empty buffer
        return buffer;
    }
    char ch;
    cin >> ch;
    switch(ch){
        case ';': case 'q':
        case '(': case ')':
        case '+': case '-':
        case '*': case '/':
            return Token{ch};       //characters represent themselves
        case '.':
        case '0': case '1': case '2': case '3': case '4': 
        case '5': case '6': case '7': case '8': case '9':
        {
            cin.putback(ch);        //put the character bacl into the input stream.
            double val;
            cin >> val;             //read a double
            return Token{'8',val};  //'8' represents a float
        }
        default:
            error("Bad token");        
    }
}


Token_stream ts;                    //provides get() and putback()
double expression();                //declaration so that primary() can call expression()

double primary()
{
    Token t = ts.get();
    switch(t.kind)
    {
        case '(':                   // handle '(' expression ')'
        {
            double d = expression();
            t=ts.get();
            if(t.kind!=')')error("')' expected, bad term.");
            return d;
        }
        case '8':                   // '8' represents a float
            return t.value;         // return value
        default:
            error("Primary expected.");
        
    }
    
}
double term()
{
    double left = primary();
    Token t = ts.get();
    
    while(true)
    {
        switch(t.kind)
        {
            case '*':
                left*=primary();
                t = ts.get();
                break;
            case '/':
            {
                double d = primary();
                if(d==0) error("divided by zero");
                left /=d;
                t = ts.get();
                break;
            }
            default:
                ts.putback(t);
                return left;
        }
    }
    
}

double expression()
{
    double left = term();           //read and evaluate a Term
    Token t = ts.get();             //get the next Token from the Token stream
    
    while(true)
    {
        switch(t.kind)
        {
            case '+':
                left += term();     //evaluate Term and add
                t=ts.get();
                break;
            case '-':
                left -=term();      //evaluate Term and substract
                t = ts.get();
                break;
            default:
                ts.putback(t);
                return left;
        } 
    }
}



int main()
{
    try{
        double val = 0;
        while(cin){
            Token t = ts.get();
            
            if(t.kind == 'q')break;     //'q' for quit
            if(t.kind == ';'){           //';' for "print now"
                cout << "=" << val << '\n';
            }
            else{ 
                ts.putback(t);
                val = expression();
            }
        }

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

