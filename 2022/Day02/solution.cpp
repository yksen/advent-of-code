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

std::map<char, Result> expectedResults = {
    {'X', Result::LOSS},
    {'Y', Result::DRAW},
    {'Z', Result::WIN}};

std::vector<std::pair<char, char>> parseStrategyGuideFromFile(std::string filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Could not open file " + filename);

    std::vector<std::pair<char, char>> strategyGuide;
    while (!file.eof())
    {
        std::pair<char, char> roundInputs;
        file >> roundInputs.first >> roundInputs.second;
        if (roundInputs.first == 0 || roundInputs.second == 0)
            break;
        strategyGuide.push_back(roundInputs);
    }
    return strategyGuide;
}

Result getResult(std::pair<char, char> roundInputs)
{
    char opponentDecision = roundInputs.first;
    char ownDecision = roundInputs.second;
    if (shapeValues.at(opponentDecision) == shapeValues.at(ownDecision))
        return Result::DRAW;
    else if (shapeValues.at(opponentDecision) % 3 + 1 == shapeValues.at(ownDecision))
        return Result::WIN;
    else
        return Result::LOSS;
}

char deduceOwnDecision(char opponentDecision, Result expectedResult)
{
    if (expectedResult == Result::DRAW)
        return opponentDecision;
    else if (expectedResult == Result::LOSS)
        return (opponentDecision % 3) + 'A';
    else
        return (opponentDecision + 2) % 3 + 'A';
}

uint64_t partOne(std::vector<std::pair<char, char>> strategyGuide)
{
    uint64_t score = 0;
    for (auto playersDecisions : strategyGuide)
        score += uint64_t(getResult(playersDecisions)) + shapeValues.at(playersDecisions.second);
    return score;
}

uint64_t partTwo(std::vector<std::pair<char, char>> strategyGuide)
{
    uint64_t score = 0;
    for (auto roundInputs : strategyGuide)
    {
        char opponentDecision = roundInputs.first;
        Result expectedResult = expectedResults.at(roundInputs.second);
        char ownDecision = deduceOwnDecision(opponentDecision, expectedResult);
        score += uint64_t(expectedResult) + shapeValues.at(ownDecision);
    }
    return score;
}

int main()
{
    auto strategyGuide = parseStrategyGuideFromFile("input.txt");

    std::cout << partOne(strategyGuide) << std::endl;
    std::cout << partTwo(strategyGuide) << std::endl;

    return 0;
}