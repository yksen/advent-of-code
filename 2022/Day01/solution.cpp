#include <fstream>
#include <iostream>
#include <sstream>

int main()
{
    std::string filename = "input.txt";
    std::ifstream file(filename);
    if (!file.is_open())
        return 1;

    uint64_t sum = 0, highestSum = 0;
    for (std::string line; std::getline(file, line);)
        if (line != "")
            sum += std::stoull(line);
        else
        {
            highestSum = std::max(highestSum, sum);
            sum = 0;
        }

    std::cout << highestSum << std::endl;
}