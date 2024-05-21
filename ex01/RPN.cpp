#include "RPN.hpp"

RPN::RPN()
{}

RPN::RPN(RPN const &other) : _stack(other._stack)
{
	*this = other;
}

RPN &RPN::operator=(RPN const &other)
{
	if (this != &other)
		this->_stack = other._stack;
	return (*this);
}

RPN::~RPN()
{}

void RPN::calculator(std::string expression)
{
	int i = 0;
	int	num = 0;
	int	op = 0;
	int	space = 1;
	double	n1;
	double	n2;
	double	value = 0;

	while (expression[i])
	{
		if (expression[i] == ' ')
		{
			space = 1;
			i++;
		}
		else if (isdigit(expression[i]) && space == 1)
		{
			_stack.push(expression[i] - '0');
			num++;
			op = 0;
			space = 0;
			i++;
		}
		else if (isOperator(expression[i]) && num >= 2 && space == 1)
		{
			n2 = _stack.top();
			_stack.pop();
			n1 = _stack.top();
			_stack.pop();
			if (expression[i] == '+')
				value = n1 + n2;
			else if (expression[i] == '-')
				value = n1 - n2;
			else if (expression[i] == '/')
			{
				if (n2 == 0)
					throw std::runtime_error("Division by zero");
				value = n1 / n2;
			}
			else if (expression[i] == '*')
				value = n1 * n2;
			_stack.push(value);
			num--;
			op = 1;
			space = 0;
			i++;
		}
		else
			throw std::runtime_error("Invalid expression");
	}
	if (op == 0 || num != 1)
		throw std::runtime_error("Invalid expression");
	std::cout << "- Result: " << GREEN << _stack.top() << NC << std::endl;
}

bool	RPN::isOperator(char c)
{
	if (c == '+' || c == '-' || c == '/' || c == '*')
		return (true);
	return (false);
}