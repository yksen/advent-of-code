#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

const size_t GROUP_SIZE = 3;

struct Rucksack
{
    std::string content;
    std::pair<std::string, std::string> compartments;
};

std::vector<Rucksack> parseRucksacksFromFile(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Could not open file " + filename);

    std::vector<Rucksack> rucksacks;
    for (std::string line; std::getline(file, line);)
    {
        Rucksack rucksack;
        size_t halfOfItems = line.size() / 2;
        rucksack.content = line;
        rucksack.compartments.first = line.substr(0, halfOfItems);
        rucksack.compartments.second = line.substr(halfOfItems, halfOfItems);
        rucksacks.push_back(rucksack);
    }
    return rucksacks;
}

char getItemAppearingInBothCompartments(const Rucksack &rucksack)
{
    for (char item : rucksack.compartments.first)
        if (rucksack.compartments.second.find(item) != std::string::npos)
            return item;
    return ' ';
}

std::vector<char> getItemsAppearingInTwoRucksacks(const std::pair<Rucksack, Rucksack> &rucksacks)
{
    std::vector<char> items;
    for (char item : rucksacks.first.content)
        if (rucksacks.second.content.find(item) != std::string::npos)
            items.push_back(item);
    return items;
}

uint64_t sumItemPriorities(const std::vector<char> &items)
{
    uint64_t sum = 0;
    for (char item : items)
        if (item >= 'a' && item <= 'z')
            sum += item - 'a' + 1;
        else if (item >= 'A' && item <= 'Z')
            sum += item - 'A' + 27;
    return sum;
}

uint64_t partOne(const std::vector<Rucksack> &rucksacks)
{
    std::vector<char> items;
    for (const Rucksack &rucksack : rucksacks)
        items.push_back(getItemAppearingInBothCompartments(rucksack));
    return sumItemPriorities(items);
}

uint64_t partTwo(const std::vector<Rucksack> &rucksacks)
{
    std::vector<char> items;
    for (size_t index = 0; index < rucksacks.size(); index += GROUP_SIZE)
    {
        auto sameItemsInTwoRucksacks = getItemsAppearingInTwoRucksacks({rucksacks[index], rucksacks[index + 1]});
        for (auto item : sameItemsInTwoRucksacks)
            if (rucksacks[index + 2].content.find(item) != std::string::npos)
            {
                items.push_back(item);
                break;
            }
    }
    return sumItemPriorities(items);
}

int main()
{
    auto rucksacks = parseRucksacksFromFile("input.txt");

    std::cout << partOne(rucksacks) << std::endl;
    std::cout << partTwo(rucksacks) << std::endl;

    return 0;
}