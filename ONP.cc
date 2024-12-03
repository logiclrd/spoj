#include <iostream>
#include <string>

using namespace std;

class Expression
{
public:
  virtual ~Expression()
  {
  }

  virtual void OutputRPN() = 0;
};

class VariableExpression : public Expression
{
  char ch;
public:
  VariableExpression(char ch)
  {
    this->ch = ch;
  }

  virtual void OutputRPN()
  {
    cout << ch;
  }
};

class OperatorExpression : public Expression
{
  Expression *left, *right;
  char oper;
public:
  OperatorExpression(Expression *left, char oper, Expression *right)
  {
    this->left = left;
    this->oper = oper;
    this->right = right;
  }

  virtual ~OperatorExpression()
  {
    delete left;
    delete right;
  }

  virtual void OutputRPN()
  {
    left->OutputRPN();
    right->OutputRPN();
    cout << oper;
  }
};

class MalformedExpression : public Expression
{
public:
  virtual void OutputRPN()
  {
    cout << "(malformed input)";
  }
};

char operators[] = "+-*/^";

Expression *parse_expression(string str)
{
  for (int i=0; i < str.size(); i++)
    if (!isspace(str[i]))
    {
      if (i > 0)
        str.erase(0, i);
      break;
    }

  for (int i = str.size() - 1; i >= 0; i--)
    if (!isspace(str[i]))
    {
      if (i + 1 < str.size())
        str.erase(i + 1, str.size() - i - 1);
      break;
    }

  size_t last_operator_offset = string::npos;
  char last_operator;

  if (str.size() == 1)
    return new VariableExpression(str[0]);

  int bracket_level = 0;
  bool had_zero = false;

  for (int i = (int)str.size() - 1; i >= 0; i--)
  {
    if (str[i] == ')')
      bracket_level++;
    else if (str[i] == '(')
      bracket_level--;
    else if (bracket_level == 0)
    {
      if (isspace(str[i]))
        continue;

      had_zero = true;

      for (int j=0; j < 5; j++)
        if (str[i] == operators[j])
        {
          last_operator = operators[j];
          last_operator_offset = i;
          break;
        }

      if (last_operator_offset != string::npos)
        break;
    }
  }

  if (bracket_level != 0)
    return new MalformedExpression();

  if (last_operator_offset == string::npos)
  {
    if ((!had_zero)
     && (str[0] == '(')
     && (str[str.size() - 1] == ')'))
      return parse_expression(str.substr(1, str.size() - 2));
    else
      return new MalformedExpression();
  }

  Expression *left = parse_expression(str.substr(0, last_operator_offset));
  Expression *right = parse_expression(str.substr(last_operator_offset + 1));

  return new OperatorExpression(left, last_operator, right);
}

int main()
{
  string expression;

  getline(cin, expression);

  int num_expressions = atoi(expression.c_str());

  for (int i=0; i < num_expressions; i++)
  {
    getline(cin, expression);
    Expression *expr = parse_expression(expression);
    expr->OutputRPN();
    cout << endl;
    delete expr;
  }
}
