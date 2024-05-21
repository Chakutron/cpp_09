#pragma once

#include <vector>
#include <deque>
#include <string>
#include <iostream>
#include <cstdlib>
#include <climits>
#include <ctime>

#define RED "\e[31m"
#define GREEN "\e[32m"
#define YELLOW "\e[33m"
#define BLUE "\e[34m"
#define VIOLET "\e[35m"
#define CYAN "\e[36m"
#define NC "\e[0m"

class PmergeMe
{
	public:
		PmergeMe();
		PmergeMe(PmergeMe const &other);
		PmergeMe &operator=(PmergeMe const &other);
		~PmergeMe();

        void    sortInput(char **input);
	private:
		std::vector<int> _vector;
		std::deque<int> _deque;
        int checkNumber(std::string const &str);
        void    sortVector();
        void    recursiveVectorSort(int left, int right);
        void    mergeVector(int left, int mid, int right);
        void    sortDeque();
        void    recursiveDequeSort(int left, int right);
        void    mergeDeque(int left, int mid, int right);
};