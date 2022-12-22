#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>

std::vector<std::string> getInput(std::string file_path)
{
    std::ifstream file(file_path);
    std::vector<std::string> input;
    std::string line;
    while (std::getline(file, line))
        input.push_back(line);
    return input;
}

size_t getTailVisitedPositionsCount(std::vector<std::string> input)
{
    const int MAX_ROPE_RANGE = 1;
    std::map<char, std::pair<int, int>> movement{
        {'U', {0, 1}},
        {'D', {0, -1}},
        {'R', {1, 0}},
        {'L', {-1, 0}}};
    std::pair<int, int> head{0, 0}, tail{0, 0};
    std::set<std::pair<int, int>> visited_positions{tail};

    for (auto line : input)
    {
        std::stringstream ss(line);
        char direction;
        int distance;
        ss >> direction >> distance;

        for (size_t step = 0; step < distance; ++step)
        {
            head.first += movement[direction].first;
            head.second += movement[direction].second;

            if (std::abs(head.first - tail.first) > MAX_ROPE_RANGE ||
                std::abs(head.second - tail.second) > MAX_ROPE_RANGE)
            {
                tail.first += movement[direction].first;
                tail.second += movement[direction].second;
                if (direction == 'D' || direction == 'U')
                    tail.first = head.first;
                else
                    tail.second = head.second;
            }

            visited_positions.insert(tail);
        }
    }
    return visited_positions.size();
}

int main()
{
    auto input = getInput("input.txt");
    std::cout << getTailVisitedPositionsCount(input) << std::endl;
}