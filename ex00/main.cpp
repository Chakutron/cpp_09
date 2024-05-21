#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        BitcoinExchange btc;
        btc.parseInputDB(argv[1]);
    }
    else
        std::cout << "- Usage: " << GREEN << "./btc" << CYAN << " <input db>" << NC << std::endl;
    return (0);
}