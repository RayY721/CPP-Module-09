/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuyu <kuyu@student.codam.nl>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 22:35:48 by kuyu              #+#    #+#             */
/*   Updated: 2026/11/08 22:40:38 by kuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cctype>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _rates(other._rates) {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
		this->_rates = other._rates;
	return (*this);
}

BitcoinExchange::~BitcoinExchange() {}

void	BitcoinExchange::loadDatabase(const std::string &filename)
{
	std::ifstream	file(filename);		// or filename.c_str()
	if (!file)
		throw std::runtime_error("could not open csv file");

	std::string	line;
	std::getline(file, line);	// assuming the first line is a header and skip it

	while (std::getline(file, line))
	{
		std::istringstream	row(line);
		std::string	date;
		float	rate;

		if (std::getline(row, date, ',') && row >> rate)
			_rates[date] = rate;
	}
}

void	BitcoinExchange::processInputFile(const std::string &filename)
{
	std::ifstream	file(filename);
	if (!file)
		throw std::runtime_error("could not open input file");

	std::string	line;
	std::getline(file, line);

	while (std::getline(file, line))
		processLine(line);
}

void	BitcoinExchange::processLine(const std::string &line)
{
	std::istringstream	row(line);
	std::string	date;
	float	amount;

	if (std::getline(row, date, '|') && row >> amount)
	{
		char	extra;
		// Check if there are any extra characters after the amount
		if (row >> extra)
		{
			std::cout << "Error: bad input => " << line << std::endl;
			return;
		}
		if (amount < 0 || amount > 1000)
		{
			if (amount < 0)
				std::cout << "Error: not a positive number." << std::endl;
			else
				std::cout << "Error: too large a number." << std::endl;
			return;
		}
		while (date.size() > 0 && (date.back() == ' ' || date.back() == '\t'))
			date.pop_back();
		if (!isValidDate(date))
		{
			std::cout << "Error: bad input => " << line << std::endl;
			return;
		}
		std::map<std::string, float>::const_iterator	it = _rates.upper_bound(date);

		if (it == _rates.begin())
		{
			std::cout << "Error: No earlier exchange rate for " << date << std::endl;
			return;
		}
		it--;
		std::cout << date << " => " << amount << " = " << amount * it->second << std::endl;
	}
	else
	{
		std::cout << "Error: bad input => " << line << std::endl;
	}
}

bool	BitcoinExchange::isValidDateFormat(const std::string &date) const
{
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return (false);

	for (std::size_t i = 0; i < date.size(); i++)
	{
		if (i == 4 || i == 7)
			continue;
		if (!std::isdigit(date[i]))
			return (false);

	}
	return (true);
}

bool	BitcoinExchange::isValidDate(const std::string &date) const
{
	if(!isValidDateFormat(date))
		return (false);

	int	year = std::stoi(date.substr(0, 4));
	int	month = std::stoi(date.substr(5, 2));
	int	day = std::stoi(date.substr(8, 2));

	if (year < 1 || month < 1 || month > 12)
		return (false);
	int	daysInMonth[] = {31, 28, 31, 30, 31, 30,
						31, 31, 30, 31, 30, 31};
	bool	leapYear = (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
	if (leapYear)
		daysInMonth[1] = 29;
	return day >= 1 && day <= daysInMonth[month - 1];
}