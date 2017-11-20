/*
    Simple calculator
    
    This program implements a basic expression calculator.
    Input from cin; output to cout.
    The grammar for the input is:
    
    Calculation:
        Statement
        Print
        Quit
        Calculation Statement
    Print:
        ;
    Quit:
        q
    Statements:
        Declaration
        Name = Expression
        Expression
    Declaration:
        "let" Name "=" Expression
    Expression:
        Term
        Expression + Term
        Expression - Term
    Term:
        Secondary
        Term *Secondary
        Term /Secondary
        Term %Secondary
    Secondary:
        Primary
        Primary !
    Primary:
        Number
        ( Expression )
        sqrt( Expression )
        pow( Expression, Expression )
        - Primary
        + Primary
    Number
        floating-point-literal
        
    Input comes from cin through the Token_stream called ts.

*/

#include "std_lib_facilities.h"

//------------------------------------------------------------------------------

const char number   = '8';  //t.kind==number means that t is a number Token
const char quit     = 'q';  //t.kind==quit means that t is a quit Token
const char print    = ';';  //t.kind==print means that t is a print Token
const char name     = 'n';  //t.kind==name means that t is a name Token
const char let      = 'L';  //t.kind==L means that t is a declaration Token;
const char helpl    = 'H';  //t.kind==H means that t is a help token.
const char powerof  = 'P';  //t.kind==P means that t is a power of token.
const char squareroot  = 'S';  //t.kind==S means that t is a squareroot of token.

const string declkey = "let";//keyword for declarations
const string help    = "help";//keyword to print the full helptext
const string root    = "sqrt";//keyword for the sqrt function
const string power   = "pow";//keyword for the pow(x,i) function

const string prompt = "> ";
const string result = "= ";  //used to indicate what follows is a result.

class Token {
public:
    char kind;        // what kind of token
    double value;     // for numbers: a value 
    string name;      // for names
    
    Token(char ch)    // make a Token from a char
        :kind(ch), value(0) , name(""){ }    
    Token(char ch, double val)     // make a Token from a char and a double
        :kind(ch), value(val) , name(""){ }
    Token(char ch, string n)     // make a Token from a char and a double
        :kind(ch), value(0) , name(n){ }
    
};

class Variable{
public:
    string name;
    double value;
};
//------------------------------------------------------------------------------

class Token_stream {
public: 
    Token_stream();         // make a Token_stream that reads from cin
    Token get();            // get a Token (get() is defined elsewhere)
    void putback(Token t);  // put a Token back
    void ignore(char c);    //discards characters up to and including a c  
private:
    bool full;              // is there a Token in the buffer?
    Token buffer;           // here is where we keep a Token put back using putback()
};


// The constructor just sets full to indicate that the buffer is empty:
Token_stream::Token_stream()
:full(false), buffer(0)    // no Token in buffer
{
}


// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback(Token t)
{
    if (full) error("putback() into a full buffer");
    buffer = t;       // copy t to buffer
    full = true;      // buffer is now full
}


Token Token_stream::get()
{
    if (full) {       // do we already have a Token ready?
        // remove token from buffer
        full=false;
        return buffer;
    } 

    char ch;
    cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)
    switch (ch) {
    case print:
    case quit:    
    case '(': 
    case ')': 
    case '}': 
    case '{':
    case '+': 
    case '-': 
    case '*': 
    case '/': 
    case '!': 
    case '%':
    case '=':
    case ',':
        return Token(ch);        // let each character represent itself
    case '.':
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '9':
        {    
            cin.putback(ch);         // put digit back into the input stream
            double val;
            cin >> val;              // read a floating-point number
            return Token(number,val);  
        }
    default:
        if(isalpha(ch)){
            string s;
            s+=ch;
            while(cin.get(ch)&&(isalpha(ch)||isdigit(ch)))s+=ch;
            cin.putback(ch);
            if(s==declkey)return Token{let};
            if((s==help)||(s=="H")||(s=="h")) return Token{helpl};
            if((s=="quit")||(s=="Q"))return Token{quit};
            if(s==power)return Token{powerof};
            if(s==root)return Token{squareroot};
            return Token{name, s};
        }
        cout <<"\n"<< ch << "\n";
        error("Bad token");
    }
}

void Token_stream::ignore(char c) //c represents the token where everything is fine after;
{
    //first look in the buffer:
    if(full && c==buffer.kind){
        full = false;
        return;
    }
    full = false;
    //now search input:
    char ch = 0;
    while(cin>>ch)
    {
        if(ch==c)return;
    }
    return;
}



Token_stream ts;        // provides get() and putback() 


// Functions needed for dynamic variable handling
vector<Variable>var_table;//to contain variables

double get_value(string s)//return value of the Variable named s
{
    for(const Variable& v : var_table)
        if(v.name==s)return v.value;
}

void set_value(string s, double d)//set Variable named s to value d
{
    for(Variable& v:var_table)
        if(v.name==s){
            v.value=d;
            return;
        }
    error("set: undifined variable", s);
}

bool is_declared(string var)//check if Variable var is in var_table
{
    for(const Variable& v:var_table)if(v.name==var)return true;
    return false;
}

double define_name(string var, double val)//add {var,val} to var_table
{
    if(is_declared(var))error(var," declared twice");
    var_table.push_back(Variable{var,val});
    return val;
}

//========================================

void welcome(){
    cout << " Welcome to our simple calculator.\n"
    << " Please end a calculation with "<<print<<" to print the result to the screen.\n"
    << " To exit the calculator, please press "<<quit<<".\n"
    << " For a full helptext enter "<<help<<".\n";
}

void helpf(){
    cout << " Please enter expressions using floating-point numbers.\n"
    << " The operations +,-,*, /,% and ! are supported.\n"
    << " The functions sqrt( float) and pow(float,int) are supported.\n"
    << " (,),{ and } are supported as delimiters.\n"
    << " % returns the floating point reminder, while ! is only defined for integers.\n"
    << " Please end a calculation with "<<print<<" to print the result to the screen.\n"
    << " To exit the calculator, please press "<<quit<<".\n";
}

//Grammar parser:
double expression();    // declaration so that primary() can call expression()

void clean_up_mess()    // removes unusable input
{  
    ts.ignore(print);
}


double primary()// deal with numbers and parentheses
{
    Token t = ts.get();
    switch (t.kind) {
        case '(':    // handle '(' expression ')'
            {    
                double d = expression();
                t = ts.get();
                if (t.kind != ')') error("')' expected");
                return d;
            }
        case '{':  // handle '{' expression '}'
            {    
                double d = expression();
                t = ts.get();
                if (t.kind != '}') error("'}' expected");
                return d;
            }
        case squareroot://handle sqrt '(' expression ')'
            {
                t = ts.get();
                char closechar = ' ';
                if(t.kind=='(')closechar=')';
                else if(t.kind=='{')closechar='}';
                else error("sqrt: delimiter expected");
                
                double d = expression();
                t = ts.get();
                if(!(t.kind==closechar))error("sqrt: missing ",closechar);
                if(d<0)error("sqrt: Only defined for positive floats.");
                return sqrt(d);
                
            }
        case powerof://handle sqrt '(' expression ')'
            {
                t = ts.get();
                char closechar = ' ';
                if(t.kind=='(')closechar=')';
                else if(t.kind=='{')closechar='}';
                else error("pow: delimiter expected");
                
                double d = expression();
                t = ts.get();
                if(!t.kind==',')error("pow: delimiter ',' needed between the float and the integer.");
                int i = narrow_cast<int>(expression());//i needs to be an integer
                if(!(t.kind==closechar))error("pow: missing "+closechar);
                if(d<0)error("sqrt: Only defined for positive floats.");
                double res = 1;
                for(int j=1;j<=i;++j)res*=d;
                return d;            
            }            
        case number:            
            return t.value;  // return the number's value
        case name:
            return get_value(t.name);
        
        case '-':
            return -primary();
        case '+':
            return +primary();
        default:
            error("primary expected");
    }
}

double secondary()//deal with factorials
{
    double left     = primary();
    int    leftint  = left;//narrow into int
    Token t         = ts.get();        // get the next token from token stream

    while(true) {
        switch (t.kind) {
        case '!':
        {
            int sign = 1;
            if(left - leftint !=0) error("Factorial of a floating-point number."); //reject for narrowing.
            if(leftint == 0)return 1; //0! is defined as 1
            if(leftint<0){sign = -1;}
            leftint *= sign;          // make leftint a positive definite integer.  
            for(int i = leftint-1;i>1;--i)leftint*=i;
            left = leftint;
            t = ts.get();
            break;
        }
        default: 
            ts.putback(t);     // put t back into the token stream
            return left;
        }
    }
}

double term()// deal with *, /, and %
{
    double left = secondary();
    Token t = ts.get();        // get the next token from token stream

    while(true) {
        switch (t.kind) {
        case '*':
            left *= secondary();
            t = ts.get();
            break;
        case '/':
            {    
                double d = secondary();
                if (d == 0) error("divide by zero");
                left /= d; 
                t = ts.get();
                break;
            }
        case '%':
            {
                double d = secondary();
                if(d==0)error("%: divide by zero");
                left = fmod(left,d);
                t = ts.get();
                break;
            }
        default: 
            ts.putback(t);     // put t back into the token stream
            return left;
        }
    }
}


double expression()// deal with + and -
{
    double left = term();      // read and evaluate a Term
    Token t = ts.get();        // get the next token from token stream

    while(true) {    
        switch(t.kind) {
        case '+':
            left += term();    // evaluate Term and add
            t = ts.get();
            break;
        case '-':
            left -= term();    // evaluate Term and subtract
            t = ts.get();
            break;
        default: 
            ts.putback(t);     // put t back into the token stream
            return left;       // finally: no more + or -: return the answer
        }
    }
}

double declaration()//We have seen let, handles name=expression and declares {name, expression} in var_table
{
    Token t=ts.get();
    if(t.kind!=name)error("name expected in declaration");
    string var_name=t.name;
    
    Token t2=ts.get();
    if(t2.kind != '=')error("= missing in declaration of ", var_name);
    
    double d = expression();
    define_name(var_name,d);
    return d;
}

double assign()//assign the name the new value
{
    Token t=ts.get();
    string name = t.name;
    if(!is_declared(name))error(name," is not declared yet, declare using let ",name);
    //if the next character is a '=', assign, else put back everything and calculate expression as normal.
    char ch;
    cin >> ch;
    if(ch=='='){
        double d = expression();
        set_value(name,d);
        return d;
    }
    else{
        cin.putback(ch);
        ts.putback(t);
        return expression();
    }
}

double statement()
{
    Token t=ts.get();
    switch (t.kind){
        case let:
            return declaration();
        case name:
            ts.putback(t);
            return assign();
        default:
            ts.putback(t);
            return expression();
    }
}

void calculate()
{
    bool printprompt = true;
    while(cin){
        try{
            
            if(true)cout << prompt;
            
            Token t = ts.get();
            while(t.kind==print){t=ts.get();printprompt=true;} //first discard all prints;
            if(t.kind==quit)return;
            if(t.kind==helpl){helpf();t=ts.get();}
            ts.putback(t);
            cout << result<<statement()<<'\n';
            printprompt = false;
            while(t.kind==print){t=ts.get();printprompt=true;} 

        }
        catch(exception& e){
            cerr<< e.what() <<'\n';
            clean_up_mess();
            printprompt==true;
        }
    }
}
//=======================================


int main()
{
    try{   
        welcome();
        calculate();
    }
    catch (exception& e) {
        cerr << "error: " << e.what() << '\n'; 
        keep_window_open("~~");
        return 1;
    }
    catch (...) {
        cerr << "Oops: unknown exception!\n"; 
        keep_window_open("~~");
        return 2;
    }
}
