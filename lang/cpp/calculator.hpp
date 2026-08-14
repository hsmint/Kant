#pragma once

#include <stack>
#include <cctype>

#define FLAG_NUM 1
#define FLAG_OP 2
#define FLAG_BRACKET 4
#define FLAG_MD 8
#define PREV_MULTI 16

typedef struct op {
    int flag;
    int bracket;
    std::stack<char> op_stack;
}ops;
