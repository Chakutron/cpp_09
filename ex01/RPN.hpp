#pragma once

#include <stack>
#include <string>
#include <iostream>
#include <stdexcept>

#define RED "\e[31m"
#define GREEN "\e[32m"
#define YELLOW "\e[33m"
#define BLUE "\e[34m"
#define VIOLET "\e[35m"
#define CYAN "\e[36m"
#define NC "\e[0m"

class RPN
{
	public:
		RPN();
		RPN(RPN const &other);
		RPN &operator=(RPN const &other);
		~RPN();

		void    calculator(std::string expression);
	private:
		std::stack<double> _stack;
        bool    isOperator(char c);
};