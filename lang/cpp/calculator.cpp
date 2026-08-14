#include "calculator.hpp"

#include <cctype>
#include <iostream>
#include <string>
#include <algorithm>

using std::cin;
using std::cout;
using std::string;


string
getInput(void) {
    string input;

    cout << "계산식을 입력해주세요: ";
    std::getline(cin, input);
    if (cin.fail() || cin.eof() || cin.bad()) {
        cout << "\n종료합니다.\n";
        exit(1);
    }
    return input;
}

void
delSpace(string& exp) {
    exp.erase(std::remove_if(exp.begin(), exp.end(), [](unsigned char c) { return std::isspace(c); }), exp.end());
}

bool
isOperator(char x) {
    return x == '+' || x == '*' || x == '/' || x == '-' || x == '(' || x == ')';
}

bool
isBracket(char x) {
    return x == '(' || x == ')';
}

bool
isNumber(const string x) {
    for (int i = 0; x[i] != '\0'; ++i) {
        if (!std::isdigit(x[i])) return false;
    }
    return true;
}

void
calculate(char x, std::stack<long double>& nums) {
    long double foo, bar;

    foo = nums.top();
    nums.pop();
    bar = nums.top();
    nums.pop();

    if (x == '+') nums.push(bar + foo);
    else if (x == '-') nums.push(bar - foo);
    else if (x == '*') nums.push(bar * foo);
    else {
        if (foo == 0) {
            cout << "0 나누기 할 수 없습니다.\n";
            exit(1);
        }
        nums.push(bar / foo);
    }
}

void
handleOp(char x, ops& op, std::stack<long double>& nums) {
    switch (x) {
        case ')':
            if (op.bracket == 0) {
                cout << "괄호 수가 맞지 않습니다.\n";
                exit(1);
            }
            op.bracket--;
            while (op.op_stack.top() != '(') {
                calculate(op.op_stack.top(), nums);
                op.op_stack.pop();
            }
            op.op_stack.pop();
            break;
        case '(':
            if (op.flag & FLAG_NUM)
                op.op_stack.push('*');
            op.bracket++;
            op.op_stack.push(x);
            break;
        case '*':
        case '/':
            op.flag |= FLAG_OP;
        case '+':
        case '-':
            op.op_stack.push(x);
            break;
    }
}

long double
parseNum(const string number) {
    if (!isNumber(number)) {
        cout << "숫자가 아닌 형식이 있습니다. " << number << '\n';
        exit(1);
    }

    return std::stold(number);
}

void
handleException(char back, char front, ops& op) {
    if (back == '+' && front == '-') {
        op.op_stack.pop();
        op.op_stack.push('-');
    } else if (back == '-' && front == '-') {
        op.op_stack.pop();
    }
}

long double
parse(const string exp) {
    ops op = {0, 0, {}};
    std::stack<long double> nums;
    size_t pos, next;

    if (exp.size() < 1) {
        cout << "계산식이 없습니다.\n";
        exit(1);
    } else if (exp.size() < 2 && !isdigit(exp[0])) {
        cout << "계산식이 아닙니다.\n";
    } else if (exp.size() < 2) {
        return static_cast<long double>(exp[0] - '0');
    }

    pos = 0;
    if (isOperator(exp[pos])) {
        nums.push(0);
        op.op_stack.push(exp[pos]);
        pos++;
    }

    next = 0;
    while (exp[pos] != '\0') {
        while (exp[pos + next] != '\0' && !isOperator(exp[pos + next])) {
            ++next;
        }

        if (next == 0) {
            handleException(exp[pos - 1], exp[pos], op);
            op.flag &= ~FLAG_NUM;
        } else {
            nums.push(parseNum(exp.substr(pos, next)));
            op.flag |= FLAG_NUM;
        }

        if ((op.flag & (FLAG_OP | FLAG_NUM)) == (FLAG_OP | FLAG_NUM)) {
            calculate(exp[pos + next], nums);
            op.op_stack.pop();
            op.flag &= ~FLAG_OP;
        }

        if (exp[pos + next] == '\0') break;

        handleOp(exp[pos + next], op, nums);

        pos = pos + next + 1;
        next = 0;
    }
    while (!op.op_stack.empty()) {
        calculate(op.op_stack.top(), nums);
        op.op_stack.pop();
    }
    return nums.top();
}

int
main(void) {
    string input;
    long double ans;

    input = getInput();
    delSpace(input);
    ans = parse(input);
    cout << "결과는 " << ans << '\n';
    return 0;
}
