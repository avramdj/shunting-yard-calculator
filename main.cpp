#include <iostream>
#include <string>
#include "calculator_ints.h"

using namespace std;

int main(int argc, char** argv){

    string expr;
    cin >> expr;
    Calculator c;
    cout << c.calculate(expr);
    cout << endl;

    exit(EXIT_SUCCESS);
}