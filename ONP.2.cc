#include <iostream>
#include <string>
#include <stack>

using namespace std;

struct have_op_type
{
  bool have_op[5];

  have_op_type()
  {
  }
} const zeroes;

const char op[] = "+-*/^";

void add_op(have_op_type &state, int level)
{
  for (int i=4; i >= level; i--)
    if (state.have_op[i])
    {
      cout << op[i];
      state.have_op[i] = false;
    }

  state.have_op[level] = true;
}

int main()
{
  string expression;

  getline(cin, expression);

  int num_expressions = atoi(expression.c_str());

  for (int i=0; i < num_expressions; i++)
  {
    getline(cin, expression);

    stack<have_op_type> opstack;

    for (int i=0; i < expression.size(); i++)
      switch (expression[i])
      {
        case '(':
          opstack.push(zeroes);
          break;
        case ')':
          if (opstack.size())
          {
            for (int j=4; j >= 0; j--)
              if (opstack.top().have_op[j])
                cout << op[j];
            opstack.pop();
          }
          break;
        case '+': add_op(opstack.top(), 0); break;
        case '-': add_op(opstack.top(), 1); break;
        case '*': add_op(opstack.top(), 2); break;
        case '/': add_op(opstack.top(), 3); break;
        case '^': add_op(opstack.top(), 4); break;
        default:
          cout << expression[i];
      }

    while (opstack.size())
    {
      for (int i=4; i >= 0; i--)
        if (opstack.top().have_op[i])
          cout << op[i];
      opstack.pop();
    }

    cout << endl;
  }
}
