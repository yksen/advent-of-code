#include <iostream>
#include <fstream>
#include <map>
#include <vector>

enum class Result
{
    LOSS = 0,
    DRAW = 3,
    WIN = 6
};

std::map<char, uint64_t> shapeValues = {
    {'A', 1},
    {'B', 2},
    {'C', 3},
    {'X', 1},
    {'Y', 2},
    {'Z', 3}};

std::map<char, char> winningCombinations = {
    {'C', 'X'},
    {'A', 'Y'},
    {'B', 'Z'}};

std::vector<std::pair<char, char>> parseStrategyGuideFromFile(std::string filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Could not open file " + filename);

    std::vector<std::pair<char, char>> strategyGuide;
    while (!file.eof())
    {
        std::pair<char, char> playersDecisions;
        file >> playersDecisions.first >> playersDecisions.second;
        if (playersDecisions.first == 0 || playersDecisions.second == 0)
            break;
        strategyGuide.push_back(playersDecisions);
    }
    return strategyGuide;
}

Result calculateResult(std::pair<char, char> decisions)
{
    for (std::pair<char, char> winningCombination : winningCombinations)
        if (decisions == winningCombination)
            return Result::WIN;
        else if (shapeValues.at(decisions.first) == shapeValues.at(decisions.second))
            return Result::DRAW;
    return Result::LOSS;
}

uint64_t calculateTotalScore(std::vector<std::pair<char, char>> strategyGuide)
{
    uint64_t score = 0;
    for (auto playersDecisions : strategyGuide)
        score += uint64_t(calculateResult(playersDecisions)) + shapeValues[playersDecisions.second];
    return score;
}

int main()
{
    auto strategyGuide = parseStrategyGuideFromFile("input.txt");
    std::cout << calculateTotalScore(strategyGuide) << std::endl;

    return 0;
}