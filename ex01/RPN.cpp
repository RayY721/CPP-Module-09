/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuyu <kuyu@student.codam.nl>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 00:50:39 by kuyu              #+#    #+#             */
/*   Updated: 2026/11/06 09:39:53 by kuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <stdexcept>
#include <sstream>

RPN::RPN() {}

RPN::RPN(const RPN &other) : _values(other._values) {}

RPN &RPN::operator=(const RPN &other)
{
	if (this != &other)
		_values = other._values;
	return (*this);
}

RPN::~RPN() {}

static bool isOperator(char c) {
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

static bool isDigit(char c) {
	return (c >= '0' && c <= '9');
}

int	RPN::evaluate(const std::string input) {
	
	std::istringstream	stream(input);
	std::string			token;
	_values.clear();
	while (stream >> token)
	{
		if (token.size() != 1)
			throw std::runtime_error("Invalid character");
		char c = token[0];

		if (isDigit(c))
		{
			_values.push_back(c - '0');
			continue;
		}
		if (!isOperator(c))
			throw std::runtime_error("Invalid character");
		if (_values.size() < 2)
			throw std::runtime_error("Invalid expression");

		int	right = _values.back();
		_values.pop_back();
		int	left = _values.back();
		_values.pop_back();

		int result;
		if (c == '+')
			result = left + right;
		else if (c == '-')
			result = left - right;
		else if (c == '*')
			result = left * right;
		else if (c == '/')
		{
			if (right == 0)
				throw std::runtime_error("Division by zero");
			result = left / right;
		}
		_values.push_back(result);
	}
	if (_values.size() != 1)
		throw std::runtime_error("Invalid expression");
	return _values.back();
}
