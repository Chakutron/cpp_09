#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    if (argc >= 2)
    {
        PmergeMe merge;
        try
        {
            merge.sortInput(&argv[1]);
        }
        catch(const std::exception& e)
        {
            std::cout << NC << "- Error: (" << RED << e.what() << NC << ")" << std::endl;
        }
    }
    else
        std::cout << "- Usage: " << GREEN << "./PmergeMe" << CYAN << " <positive integer sequence>" << NC << std::endl;
    return (0);
}