#include <iostream>
#include <stack>
#include <sstream>
#include <limits> // for numeric_limits
#include <algorithm> // for max

using namespace std;

int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/' || op == '%')
        return 2;
    return 0;
}

int applyOp(int a, int b, char op) {
    switch(op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '%': return a % b;
    }
    return 0;
}

int evaluateExpression(const string& expression) {
    stack<int> values;
    stack<char> ops;
    istringstream iss(expression);
    char token;
    while (iss >> token) {
        if (isdigit(token)) {
            int num;
            iss.putback(token);
            iss >> num;
            values.push(num);
        } else if (token == '(') {
            ops.push(token);
        } else if (token == ')') {
            while (ops.top() != '(') {
                int val2 = values.top(); values.pop();
                int val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            ops.pop(); // Pop '('
        } else if (token == '+' || token == '-' || token == '*' || token == '/' || token == '%') {
            while (!ops.empty() && precedence(ops.top()) >= precedence(token)) {
                int val2 = values.top(); values.pop();
                int val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            ops.push(token);
        }
    }
    while (!ops.empty()) {
        int val2 = values.top(); values.pop();
        int val1 = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(applyOp(val1, val2, op));
    }
    return values.top();
}

int main() {
    char choice;
    do {
        cout << "Welcome to the Calculator!" << endl;
        cout << "Please enter your arithmetic expression: ";
        string expression;
        getline(cin, expression);
        int result = evaluateExpression(expression);
        cout << "Result: " << result << endl;
        cout << "Do you want to continue? (y/n): ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
    } while (choice == 'y' || choice == 'Y');

    cout << "Thank you for using the Calculator!" << endl;

    return 0;
}
