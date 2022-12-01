#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>

std::vector<std::string> parseLinesFromFile(std::string filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Could not open file " + filename);

    std::vector<std::string> lines;
    for (std::string line; std::getline(file, line);)
        lines.push_back(line);

    return lines;
}

std::vector<uint64_t> sumChunksOfNumbers(std::vector<std::string> lines)
{
    uint64_t sum = 0;
    std::vector<uint64_t> sums;
    for (auto line : lines)
        if (line != "")
            sum += std::stoull(line);
        else
            sums.push_back(sum), sum = 0;

    return sums;
}

uint64_t partOne(std::string filename)
{
    auto lines = parseLinesFromFile(filename);
    auto sums = sumChunksOfNumbers(lines);
    std::sort(sums.begin(), sums.end());
    return sums.back();
}

uint64_t partTwo(std::string filename)
{
    auto lines = parseLinesFromFile(filename);
    auto sums = sumChunksOfNumbers(lines);
    std::sort(sums.begin(), sums.end());
    uint64_t sumOfThreeHighest = std::accumulate(sums.end() - 3, sums.end(), 0);
    return sumOfThreeHighest;
}

int main()
{
    std::string filename = "input.txt";

    std::cout << partOne(filename) << std::endl;
    std::cout << partTwo(filename) << std::endl;

    return 0;
}