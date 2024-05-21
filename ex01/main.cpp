#include "RPN.hpp"

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        RPN rpn;
        try
        {
            rpn.calculator(argv[1]);
        }
        catch(const std::exception& e)
        {
            std::cout << RED << e.what() << NC << std::endl;
        }
    }
    else
        std::cout << "- Usage: " << GREEN << "./RPN" << CYAN << " <expression>" << NC << std::endl;
    return (0);
}