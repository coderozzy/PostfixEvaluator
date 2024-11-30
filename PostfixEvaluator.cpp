#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <cctype>

int performOperation(int operand1, int operand2, char op) {
    switch (op) {
        case '+': return operand1 + operand2;
        case '-': return operand1 - operand2;
        case '*': return operand1 * operand2;
        case '/': 
            if (operand2 == 0) throw std::runtime_error("Division by zero");
            return operand1 / operand2;
        default: throw std::invalid_argument("Invalid operator");
    }
}

int evaluatePostfix(const std::string& expression) {
    std::stack<int> stack;
    std::istringstream tokens(expression);
    std::string token;

    while (tokens >> token) {
        if (std::isdigit(token[0]) || (token[0] == '-' && token.size() > 1)) {
            stack.push(std::stoi(token));
        } else if (token.size() == 1 && std::string("+-*/").find(token[0]) != std::string::npos) {
            if (stack.size() < 2) throw std::runtime_error("Invalid postfix expression");
            int operand2 = stack.top(); stack.pop();
            int operand1 = stack.top(); stack.pop();
            int result = performOperation(operand1, operand2, token[0]);
            stack.push(result);
        } else {
            throw std::invalid_argument("Invalid token in expression");
        }
    }

    if (stack.size() != 1) throw std::runtime_error("Invalid postfix expression");
    return stack.top();
}

int main() {
    try {
        std::string postfixExpression;
        std::cout << "Enter a postfix expression: ";
        std::getline(std::cin, postfixExpression);

        int result = evaluatePostfix(postfixExpression);
        std::cout << "The result is: " << result << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
    return 0;
}
