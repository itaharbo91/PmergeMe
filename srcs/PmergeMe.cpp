/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:12:37 by itaharbo          #+#    #+#             */
/*   Updated: 2025/12/07 18:16:37 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iomanip>

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(PmergeMe const &cpy) : p_inputVector(cpy.p_inputVector)
{
}

PmergeMe::~PmergeMe()
{
}

PmergeMe&	PmergeMe::operator=(PmergeMe const &other)
{
	if (this != &other)
		p_inputVector = other.p_inputVector;
	return *this;
}

// Main execution: parses input and sorts using Ford-Johnson algorithm for both containers
void	PmergeMe::run(int ac, char **av)
{
	try
	{
		p_inputVector = parseInput(ac, av);
	}
	catch (std::exception &e)
	{
		throw;
	}

	clock_t	startList = clock();
	std::list<std::priority_queue<int> > listPairs = createPairList(p_inputVector);
	p_listContainer = sortTopList(listPairs);
	insertWithJacobsthalList(p_listContainer, listPairs);
	clock_t	endList = clock();
	double	listTime = double(endList - startList) / CLOCKS_PER_SEC * 1e6;

	clock_t	startVec = clock();
	std::vector<std::priority_queue<int> > vecPairs = createPairVec(p_inputVector);
	p_vecContainer = sortTopVec(vecPairs);
	insertWithJacobsthalVec(p_vecContainer, vecPairs);
	clock_t	endVec = clock();
	double	vecTime = double(endVec - startVec) / CLOCKS_PER_SEC * 1e6;

	if (p_listContainer != std::list<int>(p_vecContainer.begin(), p_vecContainer.end()))
		throw std::runtime_error("Error: Sorted containers do not match.");

	displayContainer(listTime, vecTime);
}

// Displays the unsorted and sorted arrays along with execution times
void	PmergeMe::displayContainer(double listTime, double vectorTime)
{
	std::cout << "Before:";
	for (std::vector<int>::iterator it = p_inputVector.begin();
		it != p_inputVector.end(); ++it)
		std::cout << " " << *it;
	std::cout << std::endl;

	std::cout << "After: ";
	for (std::vector<int>::iterator it = p_vecContainer.begin();
		it != p_vecContainer.end(); ++it)
		std::cout << " " << *it;
	std::cout << std::endl;

	std::cout << "Time to process a range of " << p_inputVector.size()
		<< " elements with std::list   : " << listTime << " us" << std::endl;

	std::cout << "Time to process a range of " << p_inputVector.size()
		<< " elements with std::vector : " << vectorTime << " us" << std::endl;
}
