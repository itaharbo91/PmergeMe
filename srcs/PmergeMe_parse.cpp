/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe_parse.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 13:10:36 by itaharbo          #+#    #+#             */
/*   Updated: 2025/12/07 18:09:42 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <sstream>

std::vector<int>	PmergeMe::parseInput(int ac, char **av)
{
	std::vector<int>	vec;
	std::string		args;

	for (int i = 1; i < ac; i++)
	{
		args += av[i];
		args += ' ';
	}

	if (args.empty())
		throw std::invalid_argument("Error: No input provided.");

	std::istringstream	stream(args);
	std::string			token;

	while (stream >> token)
	{
		bool	is_digit = true;
		for (size_t i = 0; i < token.size(); i++)
		{
			if (!isdigit(token[i]))
			{
				is_digit = false;
				break ;
			}
		}

		if (!is_digit)
			throw std::invalid_argument("Error: Invalid input '" + token + "'. Only positive integers are allowed.");

		int	num = std::atoi(token.c_str());

		if (num < 0)
			throw std::out_of_range("Error: Number '" + token + "' is not allowed.");
		if (num > 2147483647)
			throw std::out_of_range("Error: Number '" + token + "' exceeds the maximum limit for a 32-bit signed integer.");
		if (std::find(vec.begin(), vec.end(), num) != vec.end())
			throw std::invalid_argument("Error: Duplicate number '" + token + "' is not allowed.");

		vec.push_back(num);
	}

	return vec;
}
