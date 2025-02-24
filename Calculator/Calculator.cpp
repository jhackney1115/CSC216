#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <cmath>

using namespace std;

class Calculator {
    public:
    double evaluate(const string& equation){
        stack<double> res;
        stringstream input(infixToPostfix(equation));
        string token;
        while (getline(input, token, ' ')) {
            if(isdigit(token[0])){
                res.push(stod(token));
            }else{
                double b=res.top();
                res.pop();
                double a=res.top();
                res.pop();
                if(token=="+"){
                    res.push(a+b);
                }
                else if(token=="-"){
                    res.push(a-b);
                }
                else if(token=="*"){
                    res.push(a*b);
                }
                else if(token=="/"){
                    res.push(a/b);
                }
                else if (token=="^"){
                    res.push(pow(a,b));
                }
            }
        }
        return res.top();
    }
    
    //Credit to Rosetta Code for the infixToPostfix function
    string infixToPostfix(const string& infix) {
        const string ops = "-+/*^";
        stringstream ss;
        stack<int> s;
    
        stringstream input(infix);
        string token;
        while (getline(input, token, ' ')) {
            if (token.empty()) {
                continue;
            }
    
            char c = token[0];
            size_t idx = ops.find(c);
    
            // check for operator
            if (idx != string::npos) {
                while (!s.empty()) {
                    int prec2 = s.top() / 2;
                    int prec1 = static_cast<unsigned>(idx / 2);
                    if (prec2 > prec1 || (prec2 == prec1 && 
                        c != '^')) {
                        ss << ops[s.top()] << ' ';
                        s.pop();
                    } else break;
                }
                s.push(static_cast<unsigned>(idx));
            } else if (c == '(') {
                s.push(-2); // -2 stands for '('
            } else if (c == ')') {
                // until '(' on stack, pop operators.
                while (s.top() != -2) {
                    ss << ops[s.top()] << ' ';
                    s.pop();
                }
                s.pop();
            } else {
                ss << token << ' ';
            }
        }
    
        while (!s.empty()) {
            ss << ops[s.top()] << ' ';
            s.pop();
        }
    
        return ss.str();
    }
    

    private:
};

int main() {
    Calculator calculator;
    string infix = "4 + 4 / 2 ^ 2";
    cout << "infix:   " << infix << '\n';
    double res = calculator.evaluate(infix);
    cout << res << endl;
    infix="4 + ( 3 - 2 ) * 3";
    cout << "infix:   " << infix << '\n';
    cout << calculator.evaluate(infix) << endl;
    infix="5 * ( 4 - 2 ) * 8";
    cout << "infix:   " << infix << '\n';
    cout << calculator.evaluate(infix) << endl;
    infix="22 + ( 16 - 8 ) / 4 ^ 2";
    cout << "infix:   " << infix << '\n';
    cout << calculator.evaluate(infix) << endl;
    return 0;
}

