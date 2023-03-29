#include "Set.h"
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;

bool isValidInfix(string infix) { //failures: a(, (), &), )), a!, )!, &&, &), *, A, aa, )a
    stack <char> parenthesisStack;
    string noSpace = "";
    noSpace += '!'; //dummy value

    for (int i = 0; i < infix.length(); i++) {
        char c = infix[i];
        char last = noSpace[noSpace.length() - 1];

        switch (c) {
            case '(':
                if (isalpha(last) || last == ')') { // a(, ()
                    return false;
                }
                parenthesisStack.push(c);
                noSpace += c;
                break;

            case ')':
                if (!isalpha(last) && last != ')') { //&)
                    return false;
                }
                noSpace += c;
                if (parenthesisStack.empty()) { //floating )
                    return false;
                }
                parenthesisStack.pop(); //pop the previous ()
                break;

            case ' ':
                break;

            case '!':
                if (isalpha(last) || last == ')') { //a!, )!
                    return false;
                }
                noSpace += c;
                break;

            case '&':
            case '|':
                if (!isalpha(last) && last != ')') { //&&, &)
                    return false;
                }
                noSpace += c;
                break;

            default: //letter
                if (!isalpha(c) || !islower(c) || isalpha(last) || last == ')') { //random char, A, aa, )a
                    return false;
                }
                noSpace += c;
        }
    }

    int i; //index of final non ) char
    for (i = noSpace.length() - 1; i >= 0; i--) {
        if (noSpace[i] != ')') {
            break;
        }
    }
    if (!isalpha(noSpace[i])) {
        return false;
    }
    // while (operatorStack.top() == ')') {
    //     operatorStack.pop();
    // }
    // if (!isalpha(operatorStack.top())) {
    //     return false;
    // }
    return parenthesisStack.empty(); //no floating (
}

int precedence(char c) {
    switch (c) {
        case '!': 
            return 2;
        
        case '&':
            return 1;

        case '|':
            return 0;
        
        default:
            return 3;
    }
}

int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result) {
    if (!isValidInfix(infix)) {
        // cout << "NOT VALID STRING" << endl;
        return 1;
    }

    for (int i = 0; i < infix.length(); i++) {
        char ch = infix[i];

        if (isalpha(ch)) {
            if (!trueValues.contains(ch) && !falseValues.contains(ch)) {
                return 2;
            } else if (trueValues.contains(ch) && falseValues.contains(ch)) {
                return 3;
            }
        }
    }

    postfix = "";
    stack <char> operatorStack;

    for (int i = 0; i < infix.length(); i++) {
        char ch = infix[i];

        switch (ch) {
            case '(': 
                operatorStack.push(ch);
                break;

            case ')': 
                while (operatorStack.top() != '(') {
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.pop(); //pop the '('
                break;

            case ' ':
                break;
            
            case '!':
            case '&':
            case '|':
                while (!operatorStack.empty() && operatorStack.top() != '(' && precedence(ch) <= precedence(operatorStack.top())) {
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.push(ch);
                break;

            default: //letter
                postfix += ch;
                break;
        }
    }

    while (!operatorStack.empty()) {
        postfix += operatorStack.top();
        operatorStack.pop();
    }

    stack <bool> operandStack;

    for (int i = 0; i < postfix.length(); i++) {
        char ch = postfix[i];

        if (isalpha(ch)) {
            if (trueValues.contains(ch)) {
                operandStack.push(true);
            } else {
                operandStack.push(false);
            }
        } else {
            bool op2 = operandStack.top();
            operandStack.pop();
            bool op1 = operandStack.top();
            operandStack.pop();

            if (ch == '|') {
                operandStack.push(op2 || op1);
            } else if (ch == '&') {
                operandStack.push(op2 && op1);
            } else { // ch == '!'
                operandStack.push(op1);
                operandStack.push(!op2);
            }
        }
    }
    result = operandStack.top();
    return 0;
}

int main() {
    string trueChars  = "tywz";
    string falseChars = "fnx";
    Set trues;
    Set falses;
    for (int k = 0; k < trueChars.size(); k++)
        trues.insert(trueChars[k]);
    for (int k = 0; k < falseChars.size(); k++)
        falses.insert(falseChars[k]);

    string pf;
    bool answer;
    assert(evaluate("w| f", trues, falses, pf, answer) == 0  &&  pf == "wf|" &&  answer);
    assert(evaluate("y|", trues, falses, pf, answer) == 1);
    assert(evaluate("n t", trues, falses, pf, answer) == 1);
    assert(evaluate("nt", trues, falses, pf, answer) == 1);
    assert(evaluate("()", trues, falses, pf, answer) == 1);
    assert(evaluate("()z", trues, falses, pf, answer) == 1);
    assert(evaluate("y(n|y)", trues, falses, pf, answer) == 1);
    assert(evaluate("t(&n)", trues, falses, pf, answer) == 1);
    assert(evaluate("(n&(t|y)", trues, falses, pf, answer) == 1);
    assert(evaluate("n+y", trues, falses, pf, answer) == 1);
    assert(evaluate("", trues, falses, pf, answer) == 1);
    assert(evaluate("f  |  !f & (t&n) ", trues, falses, pf, answer) == 0
                            &&  pf == "ff!tn&&|"  &&  !answer);
    assert(evaluate(" x  ", trues, falses, pf, answer) == 0  &&  pf == "x"  &&  !answer);
    trues.insert('x');                
    assert(evaluate("((x))", trues, falses, pf, answer) == 3);
    falses.erase('x');
    assert(evaluate("((x))", trues, falses, pf, answer) == 0  &&  pf == "x"  &&  answer);
    trues.erase('w');
    assert(evaluate("w| f", trues, falses, pf, answer) == 2);
    falses.insert('w');
    assert(evaluate("w| f", trues, falses, pf, answer) == 0  &&  pf == "wf|" &&  !answer);
    cout << "Passed all tests" << endl;
}