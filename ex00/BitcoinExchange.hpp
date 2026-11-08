/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuyu <kuyu@student.codam.nl>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 22:14:35 by kuyu              #+#    #+#             */
/*   Updated: 2026/11/08 19:58:27 by kuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
# include <string>
class BitcoinExchange
{
	private:
		std::map<std::string, float>	_rates;

		void	processLine(const std::string &line);
		bool	isValidDateFormat(const std::string &date) const;
		bool	isValidDate(const std::string &date) const;
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange &operator=(const BitcoinExchange &other);
		~BitcoinExchange();

		void	loadDatabase(const std::string &filename);
		void	processInputFile(const std::string &filename);
};

#endif
