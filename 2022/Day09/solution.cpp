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

size_t getVisitedPositionsCount(std::vector<std::string> input)
{
    const int MAX_ROPE_RANGE = 1;
    const size_t KNOT_COUNT = 10;
    std::map<char, std::pair<int, int>> movement{
        {'U', {0, 1}},
        {'D', {0, -1}},
        {'R', {1, 0}},
        {'L', {-1, 0}}};
    std::vector<std::pair<int, int>> knots(KNOT_COUNT, {0, 0});
    std::set<std::pair<int, int>> visited_positions{knots.back()};

    for (auto line : input)
    {
        std::stringstream ss(line);
        char direction;
        int distance;
        ss >> direction >> distance;

        for (size_t step = 0; step < distance; ++step)
        {
            knots.front().first += movement[direction].first;
            knots.front().second += movement[direction].second;
            for (size_t index = 0; index < knots.size() - 1; ++index)
            {
                int x = knots[index].first - knots[index + 1].first;
                int y = knots[index].second - knots[index + 1].second;

                if (std::abs(x) > MAX_ROPE_RANGE ||
                    std::abs(y) > MAX_ROPE_RANGE)
                {
                    if (std::abs(x) == std::abs(y))
                    {
                        knots[index + 1].first += (x > 0 ? 1 : -1);
                        knots[index + 1].second += (y > 0 ? 1 : -1);
                    }
                    else if (std::abs(x) > 0 && std::abs(y) > 0)
                    {
                        if (std::abs(x) > MAX_ROPE_RANGE)
                        {
                            knots[index + 1].first += (x > 0 ? 1 : -1);
                            knots[index + 1].second = knots[index].second;
                        }
                        else if (std::abs(y) > MAX_ROPE_RANGE)
                        {
                            knots[index + 1].second += (y > 0 ? 1 : -1);
                            knots[index + 1].first = knots[index].first;
                        }
                    }
                    else
                    {
                        knots[index + 1].first += x / 2;
                        knots[index + 1].second += y / 2;
                    }
                }
            }
            visited_positions.insert(knots.back());
        }
    }
    return visited_positions.size();
}

int main()
{
    auto input = getInput("input.txt");
    std::cout << getVisitedPositionsCount(input) << std::endl;
}