/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuyu <kuyu@student.codam.nl>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 22:14:52 by kuyu              #+#    #+#             */
/*   Updated: 2026/11/06 08:57:59 by kuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <string>
# include <list>

class RPN
{
	public:
		RPN();
		~RPN();
		int	evaluate(const std::string input);
		
	private:
		std::list<int> _values;
		RPN(const RPN &other);
		RPN &operator=(const RPN &other);
};

#endif