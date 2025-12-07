/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:12:55 by itaharbo          #+#    #+#             */
/*   Updated: 2025/12/07 18:32:26 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <ctime>
# include <algorithm>
# include <vector>
# include <list>
# include <queue>

class PmergeMe
{
public:

	PmergeMe();
	PmergeMe(PmergeMe const &cpy);
	~PmergeMe();

	PmergeMe&	operator=(PmergeMe const &other);

	void		run(int ac, char **av);

private:

	std::vector<int>	p_inputVector;
	std::list<int>		p_listContainer;
	std::vector<int>	p_vecContainer;

	std::vector<int>						parseInput(int ac, char **av);

	std::list<std::priority_queue<int> >	createPairList(std::vector<int>);
	std::list<int>							sortTopList(std::list<std::priority_queue<int> > &pairs);
	std::vector<size_t>						generateJacobsthalSequenceList(size_t n);
	void									insertWithJacobsthalList(std::list<int> &sorted,
											std::list<std::priority_queue<int> > &pairs);
	std::vector<std::priority_queue<int> >	createPairVec(std::vector<int>);
	std::vector<int>						sortTopVec(std::vector<std::priority_queue<int> > &pairs);
	std::vector<size_t>						generateJacobsthalSequence(size_t n);

	void									insertWithJacobsthalVec(std::vector<int> &sorted,
											std::vector<std::priority_queue<int> > &pairs);

	void									displayContainer(double listTime, double vectorTime);
};

// Comparators for sorting pairs by their maximum element
bool comparePairs(const std::priority_queue<int> &a, const std::priority_queue<int> &b);
bool comparePairsList(const std::priority_queue<int> &a, const std::priority_queue<int> &b);

#endif
