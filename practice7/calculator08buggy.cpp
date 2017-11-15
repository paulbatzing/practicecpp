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
        Primary
        Term *Primary
        Term /Primary
        Term %Primary
    Primary:
        Number
        ( Expression )
        sqrt( Expression )
        pow( Expression , Expression )
        - Primary
        + Primary
    Number
        floating-point-literal
        
    Input comes from cin through the Token_stream called ts.

*/

#include "std_lib_facilities.h"
class Token//class to hold tokens and values/names
{
public:
    char kind;
	double value;
	string name;
	Token(char ch) :kind(ch), value(0) { }
	Token(char ch, double val) :kind(ch), value(val) { }
	Token(char ch, string n)   :kind(ch), name(n){}
};

class Token_stream//class to hold the token stream
{
public:
	Token_stream() :full(false), buffer(0) { }
	Token get();
	void unget(Token t) { buffer=t; full=true; }
	void ignore(char);
private:
    bool full;
	Token buffer;
};


const char let = 'L';
const char quit = 'Q';
const char print = ';';
const char number = '8';
const char name = 'a';
const char squrt = 's';
const char powerof= 'p';

const string quits = "exit";
const string declar = "let";
const string squareroot = "sqrt";
const string power = "pow";

Token Token_stream::get()
{
	if (full) { full=false; return buffer; }
	char ch;
	cin >> ch;
	switch (ch) {
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case ';':
	case '=':
    case ',':
    case quit:
		return Token(ch);//characters represent themselves
    case 'q': return Token(quit);//I want both Q and q
	case '.': case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{	//we find the value
        cin.unget();
		double val;
		cin >> val;
		return Token(number,val);
	}
	default:
		if (isalpha(ch)) {//if its a string, it can be a name or a declaration
			string s;
			s += ch;
			while(cin.get(ch) && (isalpha(ch) || isdigit(ch))) s+=ch;
			cin.unget();
			if (s == declar) return Token(let);	
			if (s == quits) return Token(quit);
            if (s == squareroot) return Token(squrt);
            if (s == power) return Token(powerof);
			return Token(name,s);
		}
		error("Bad token");
	}
}

void Token_stream::ignore(char c)//ignore all characters up to c
{
	if (full && c==buffer.kind) 
    {
		full = false;
		return;
	}
	full = false;

	char ch;
	while (cin>>ch)
		if (ch==c) return;
}

struct Variable {
	string name;
	double value;
	Variable(string n, double v) :name(n), value(v) { }
};

vector<Variable> names;	

double get_value(string s)
{
	for (int i = 0; i<names.size(); ++i)
		if (names[i].name == s) return names[i].value;
	error("get: undefined name ",s);
}

void set_value(string s, double d)
{
	for (int i = 0; i<=names.size(); ++i)
		if (names[i].name == s) {
			names[i].value = d;
			return;
		}
	error("set: undefined name ",s);
}

bool is_declared(string s)//check if s is already declared
{
	for (int i = 0; i<names.size(); ++i)
		if (names[i].name == s) return true;
	return false;
}

void define_name(string name, double val){
    names.push_back(Variable(name,val));
}

Token_stream ts;

double expression();

double primary()//takes care of literal numbers and variables
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{	double d = expression();
		t = ts.get();
		if (t.kind != ')') error("'(' expected");
	}
    case squrt://test that the grammar sqrt( Exp ) is used
    {
        t = ts.get();
        if(t.kind !='(')error("sqrt: ( expected");
        double d = expression();
        //test for negative input:
        if(0>d)error("sqrt: Takes only positive input");
        t = ts.get();
        if(t.kind !=')')error("sqrt: ) expected");
        return sqrt(d);
    }
    case powerof://test that the grammar pow( Exp ) is used
    {
        t = ts.get();
        if(t.kind !='(')error("pow: ( expected");
        double d = expression();
        t = ts.get();
        if(t.kind !=',')error("pow: , expected");        
        int i = narrow_cast<int>(expression());
        t = ts.get();
        if(t.kind !=')')error("pow: ) expected");
        if(i<0)error("pow(d,i) expects i to be a positive integer");
        double r = 1;
        for(int j=1;j<=i;++j){r*=d;}
        return r;
    }        
	case '-':
		return - primary();
    case '+':
        return + primary();
	case number:
		return t.value;
	case name:
		return get_value(t.name);
	default:
		error("primary expected");
	}
}

double term()//takes care of * and /
{
	double left = primary();
	while(true) {
		Token t = ts.get();
		switch(t.kind) {
		case '*':
			left *= primary();
			break;
		case '/'://secure against dividing by zero
		{	double d = primary();
			if (d == 0) error("divide by zero");
			left /= d;
			break;
		}

		default:
			ts.unget(t);
			return left;
		}
	}
}

double expression()//take care of +/-
{
	double left = term();
	while(true) {
		Token t = ts.get();
		switch(t.kind) {
		case '+':
			left += term();
			break;
		case '-':
			left -= term();
			break;
		default:
			ts.unget(t);
			return left;
		}
	}
}

double declaration()
{
	Token t = ts.get();
	if (t.kind != 'a') error ("name expected in declaration");
	string name = t.name;
	if (is_declared(name)) error(name, " declared twice");
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of " ,name);
	double d = expression();
	names.push_back(Variable(name,d));
	return d;
}

double statement()
{
	Token t = ts.get();
	switch(t.kind) {
	case let:
		return declaration();
	default:
		ts.unget(t);
		return expression();
	}
}

void clean_up_mess()
{
	ts.ignore(print);
}

const string prompt = "> ";
const string result = "= ";

void calculate()
{
	while(true) try {
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t=ts.get();//eat ;
		if (t.kind == quit) return;
		ts.unget(t);
		cout << result << statement() << endl;
	}
	catch(runtime_error& e) {
		cerr << e.what() << endl;
		clean_up_mess();
	}
}

int main(){
    cout << " Welcome to our simple calculator.\n"
    << " Please enter expressions using floating-point numbers.\n"
    << " The operations +,-,*, "<<squareroot<<"(d) and "<<power<<"(d,i)  supported.\n"
    << " ( are ) are supported as delimiters.\n"
    << " "<<squareroot<<"(d) returns the squareroot of any positive float, while "<<power<<"(d,i) is only defined for positive integer i.\n"
    << " Please end a calculation with "<<print<<" to print the result to the screen.\n"
    << " To declare a variable, type "<<declar<<" name = val where name is alphanumerical and val is a float.\n"
    << " To exit the calculator, please enter "<<quits<<".\n";
	try {
        define_name("k",1000);
		calculate();
		return 0;
	}
	catch (exception& e) {
		cerr << "exception: " << e.what() << endl;
		char c;
		while (cin >>c&& c!=';') ;
		return 1;
	}
	catch (...) {
		cerr << "exception\n";
		char c;
		while (cin>>c && c!=';');
		return 2;
	}
}
