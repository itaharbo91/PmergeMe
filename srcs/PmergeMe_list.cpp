/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe_list.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 12:19:52 by itaharbo          #+#    #+#             */
/*   Updated: 2025/12/07 18:28:24 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

// Creates pairs of consecutive elements. Each pair is stored in a priority_queue (max-heap)
std::list<std::priority_queue<int> >	PmergeMe::createPairList(std::vector<int> vec)
{
	std::list<std::priority_queue<int> >	pairs;
	size_t								i = 0;

	while (i < vec.size())
	{
		std::priority_queue<int>	pair;

		pair.push(vec[i]);
		if (i + 1 < vec.size())
			pair.push(vec[i + 1]);
		pairs.push_back(pair);
		i += 2;
	}
	return pairs;
}

// Comparator to sort pairs by their maximum element
bool comparePairsList(const std::priority_queue<int> &a, const std::priority_queue<int> &b)
{
	return a.top() < b.top();
}

// Extracts the top elements from each pair and handles the straggler if present
std::list<int>	PmergeMe::sortTopList(std::list<std::priority_queue<int> > &pairs)
{
	std::list<int>	sortedTop;

	std::priority_queue<int> straggler;
	bool hasStraggler = false;
	if (!pairs.empty() && pairs.back().size() == 1)
	{
		hasStraggler = true;
		straggler = pairs.back();
		pairs.pop_back();
	}

	pairs.sort(comparePairsList);

	for (std::list<std::priority_queue<int> >::iterator it = pairs.begin();
		it != pairs.end(); ++it)
	{
		sortedTop.push_back(it->top());
	}
	
	if (hasStraggler)
	{
		pairs.push_back(straggler);
	}
	
	return sortedTop;
}

// Generates the Jacobsthal insertion sequence for optimal insertion order
std::vector<size_t>	PmergeMe::generateJacobsthalSequenceList(size_t n)
{
	std::vector<size_t>	jacobsthal;
	
	if (n == 0)
		return jacobsthal;
	
	std::vector<size_t>	jNumbers;
	jNumbers.push_back(0);
	jNumbers.push_back(1);
	
	while (jNumbers.back() < n)
	{
		size_t next = jNumbers[jNumbers.size() - 1] + 2 * jNumbers[jNumbers.size() - 2];
		jNumbers.push_back(next);
	}
	
	std::vector<bool> inserted(n, false);
	
	for (size_t i = 2; i < jNumbers.size() && jacobsthal.size() < n; i++)
	{
		size_t current = jNumbers[i];
		if (current > n)
			current = n;
			
		size_t prev = jNumbers[i - 1];
		
		for (size_t j = current; j > prev && jacobsthal.size() < n; j--)
		{
			size_t idx = j - 1;
			if (idx < n && !inserted[idx])
			{
				jacobsthal.push_back(idx);
				inserted[idx] = true;
			}
		}
	}
	
	for (size_t i = 0; i < n; i++)
	{
		if (!inserted[i])
			jacobsthal.push_back(i);
	}
	
	return jacobsthal;
}

// Inserts the smaller elements from pairs using Jacobsthal sequence for optimal insertion order
void	PmergeMe::insertWithJacobsthalList(std::list<int> &sorted,
			std::list<std::priority_queue<int> > &pairs)
{
	if (pairs.empty())
		return;
		
	int straggler = -1;
	bool hasStraggler = false;
	
	if (!pairs.empty() && pairs.back().size() == 1)
	{
		hasStraggler = true;
		straggler = pairs.back().top();
	}
	
	size_t pairCount = hasStraggler ? pairs.size() - 1 : pairs.size();
	
	if (pairCount == 0)
	{
		if (hasStraggler)
			sorted.push_back(straggler);
		return;
	}
	
	if (pairs.front().size() == 2)
	{
		std::priority_queue<int>	firstPair = pairs.front();
		firstPair.pop();
		int firstBottom = firstPair.top();
		
		std::list<int>::iterator pos = sorted.begin();
		while (pos != sorted.end() && *pos < firstBottom)
			++pos;
		sorted.insert(pos, firstBottom);
	}
	
	if (pairCount > 1)
	{
		std::vector<size_t>	insertOrder = generateJacobsthalSequenceList(pairCount - 1);
		
		for (size_t i = 0; i < insertOrder.size(); i++)
		{
			size_t idx = insertOrder[i] + 1;
			
			if (idx < pairCount)
			{
				std::list<std::priority_queue<int> >::iterator pairIt = pairs.begin();
				std::advance(pairIt, idx);
				
				if (pairIt != pairs.end() && pairIt->size() == 2)
				{
					std::priority_queue<int>	pair = *pairIt;
					pair.pop();
					int smaller = pair.top();
					
					std::list<int>::iterator pos = sorted.begin();
					while (pos != sorted.end() && *pos < smaller)
						++pos;
					
					sorted.insert(pos, smaller);
				}
			}
		}
	}
	
	if (hasStraggler)
	{
		std::list<int>::iterator pos = sorted.begin();
		while (pos != sorted.end() && *pos < straggler)
			++pos;
		sorted.insert(pos, straggler);
	}
}
