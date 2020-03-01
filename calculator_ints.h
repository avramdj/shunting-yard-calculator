#ifndef CALCULATOR_INTS_HEADER
#define CALCULATOR_INTS_HEADER

#include <iostream>
#include <cmath>
#include <string>
#include <stack>
#include <deque>

class Calculator{
private:
    int priority(const char& op){
        int prio;
        switch(op){
            case '-':
            case '+':
                prio = 1;
                break;
            case '*':
            case 'x':
                prio = 2;
                break;
            case '/':
                prio = 3;             
                break;
            case '(':
                prio = 0;
                break;
        }
        return prio;
    }
    bool check(const std::string& expr){
        for(char c : expr){
            if(isdigit(c)) continue;
            switch(c){
                case '(': break;
                case ')': break;
                case '+': break;
                case '-': break;
                case '*': break;
                case 'x': break;
                case '/': break;
                default: return false;
            }
        }
        return true;
    }
    std::deque<char> infix(const std::string& expr){
        std::stack<char> stek;
        std::deque<char> red;
        for(char c : expr){
            if(isdigit(c)){
                red.push_back(c);
            } else {
                red.push_back(';');
                switch(c){
                    case '(': stek.push(c); break;
                    case ')':
                        while(stek.top() != '('){
                            red.push_back(stek.top());
                            stek.pop();
                        }
                        stek.pop();
                        break;
                    default:
                        while(!stek.empty() && (priority(c) < priority(stek.top()))){
                            red.push_back(stek.top());
                            stek.pop();
                        }
                        stek.push(c);
                }
            }
        }
        while(!stek.empty()){
            red.push_back(stek.top());
            stek.pop();
        }
        return red;
    }
    double eval(std::deque<char> red){
        std::stack<int> stek;
        int a, b;
        double c;
        while(!red.empty()){
            int num = 0;
            if(isdigit(red.front())){
                for(int i = 0; isdigit(red.front()); i++){
                    num *= std::pow(10, i);
                    num += (red.front() - '0');
                    red.pop_front();
                }
                stek.push(num);
            } else {
                if(red.front() == ';'){
                    red.pop_front();
                    continue;
                }
                b = stek.top();
                stek.pop();
                a = stek.top();
                stek.pop();
                switch(red.front()){
                    case '+':
                        c = a+b;
                        break;
                    case '-':
                        c = a-b;
                        break;
                    case '*':
                    case 'x':
                        c = a*b;
                        break;
                    case '/':
                        if(b == 0){
                            std::cerr << "error: division by zero" << std::endl;
                            exit(EXIT_FAILURE);
                        }
                        c = a/b;
                        break;
                }
                stek.push(c);
                red.pop_front();
            }
        }
        return stek.top();
    }
public:
    double calculate(const std::string& expr){
        if(!check(expr)){
            std::cerr << "Expression can only contain [0-9], (, ), +, -, *, x, /" << std::endl;
            return -1;
        }
        std::deque<char> expr_infix = infix(expr);
        return eval(expr_infix);
    }
    std::string to_infix(const std::string& expr){
        std::deque<char> expr_infix = infix(expr);
        std::string str_inf;
        while(!expr_infix.empty()){
            str_inf += expr_infix.front();
            expr_infix.pop_front();
        }
        return str_inf; 
    }
};
#endif
