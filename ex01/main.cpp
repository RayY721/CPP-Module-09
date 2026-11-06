/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuyu <kuyu@student.codam.nl>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 00:50:47 by kuyu              #+#    #+#             */
/*   Updated: 2026/11/06 09:33:56 by kuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>

int	main (int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cerr << "Error: Invalid number of arguments" << std::endl;
		return (1);
	}
	// 3 4 + → 7
	try
	{
		RPN rpn;
		int result = rpn.evaluate(argv[1]);
		std::cout << result << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return (1);
	}
	return (0);
}
