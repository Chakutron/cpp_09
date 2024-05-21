#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{}

PmergeMe::PmergeMe(PmergeMe const &other) : _vector(other._vector), _deque(other._deque)
{
    *this = other;
}

PmergeMe &PmergeMe::operator=(PmergeMe const &other)
{
    if (this != &other)
    {
        _vector = other._vector;
        _deque = other._deque;
    }
    return (*this);
}

PmergeMe::~PmergeMe()
{}

void    PmergeMe::sortInput(char **input)
{
    int i = 0;
    int num;

    while (input[i])
    {
        // checking if the input value is a valid number
        if (checkNumber(input[i]) == 1)
        	throw std::runtime_error("Negative number in the sequence 1");
        else if ((checkNumber(input[i]) == 2) || (std::atol(input[i]) > INT_MAX))
        	throw std::runtime_error("Number bigger than INT_MAX in the sequence");
        else if (checkNumber(input[i]) == 3)
        	throw std::runtime_error("Wrong value in the sequence");
        num = std::atoi(input[i]);
        _vector.push_back(num);
        _deque.push_back(num);
        i++;
    }
    // printing the array unsorted
    std::cout << "Before:" << CYAN;
    std::vector<int>::iterator it;
    for (it = _vector.begin(); it != _vector.end(); ++it)
    {
        std::cout << " " << *it;
    }
    std::cout << NC << std::endl;
    clock_t startVector = clock();
    sortVector();
    clock_t endVector = clock();
    // printing the vector array sorted
    std::cout << "After (vector container):" << GREEN;
    for (it = _vector.begin(); it != _vector.end(); ++it)
    {
        std::cout << " " << *it;
    }
    std::cout << NC << std::endl;
    clock_t startDeque = clock();
    sortDeque();
    clock_t endDeque = clock();
    // printing the deque array sorted
    std::cout << "After (deque container):" << YELLOW;
    std::deque<int>::iterator it2;
    for (it2 = _deque.begin(); it2 != _deque.end(); ++it2)
    {
        std::cout << " " << *it2;
    }
    std::cout << NC << std::endl;
    // printing the timing results
    double timeVector = static_cast<double>(endVector - startVector) / CLOCKS_PER_SEC * 1000000;
    std::cout << "Time to process a range of " << GREEN << _vector.size() << NC << " elements with " << GREEN << "std::vector<int>" << NC << " : " << GREEN << timeVector << " µs" << NC << std::endl;
    double timeDeque = static_cast<double>(endDeque - startDeque) / CLOCKS_PER_SEC * 1000000;
    std::cout << "Time to process a range of " << YELLOW << _deque.size() << NC << " elements with " << YELLOW << "std::deque<int>" << NC << " : " << YELLOW << timeDeque << " µs" << NC << std::endl;
    
}

int	PmergeMe::checkNumber(std::string const &str)
{
	int	i = 0;
	int	n = 0;
	int	d = 0;
    int s = 0;

    while (str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		n++;
		i++;
	}
	while (i < static_cast<int>(str.size()))
	{
        if (str[i] == ' ')
            s = 1;
        else if (str[i] == '0' && d == 0 && s == 0)
            (void)str;
        else if (str[i] == '0' && d > 0 && s == 0)
            d++;
		else if (str[i] >= '1' && str[i] <= '9' && s == 0)
			d++;
        else
            return (3);
		i++;
	}
	if (n == 1 && d > 0)
		return (1);
	if (n == 1 && d == 0)
		return (3);
    // INT_MAX = 2147483647
    else if (d > 10)
		return (2);
	return (0);
}

void    PmergeMe::sortVector()
{
    int n = _vector.size();

    if (n <= 1)
        return ;
    recursiveVectorSort(0, n - 1);
}

void    PmergeMe::recursiveVectorSort(int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        recursiveVectorSort(left, mid);
        recursiveVectorSort(mid + 1, right);

        mergeVector(left, mid, right);
    }
}

void    PmergeMe::mergeVector(int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = _vector[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = _vector[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            _vector[k++] = L[i++];
        else
            _vector[k++] = R[j++];
    }

    while (i < n1)
        _vector[k++] = L[i++];

    while (j < n2)
        _vector[k++] = R[j++];
}

void    PmergeMe::sortDeque()
{
    int n = _deque.size();

    if (n <= 1)
        return ;
    recursiveDequeSort(0, n - 1);
}

void    PmergeMe::recursiveDequeSort(int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        recursiveDequeSort(left, mid);
        recursiveDequeSort(mid + 1, right);

        mergeDeque(left, mid, right);
    }
}

void    PmergeMe::mergeDeque(int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    std::deque<int> L(_deque.begin() + left, _deque.begin() + left + n1);
    std::deque<int> R(_deque.begin() + mid + 1, _deque.begin() + mid + 1 + n2);
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            _deque[k++] = L[i++];
        else
            _deque[k++] = R[j++];
    }
    
    while (i < n1)
        _deque[k++] = L[i++];
    
    while (j < n2)
        _deque[k++] = R[j++];
}