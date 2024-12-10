#include <aoc/input.hpp>
#include <aoc/utils.hpp>
#include <print>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

int64_t traverse(const std::vector<std::string>& input, int x, int y, bool distinct = false) {
  std::queue<std::pair<int, int>> q;
  std::set<std::pair<int, int>> visited;
  int64_t score{0}, distinct_paths{0};
  size_t width{input.front().size()}, height{input.size()};

  q.emplace(x, y);
  visited.insert({x, y});

  while (!q.empty()) {
    auto pos{q.front()};
    q.pop();
    if (input[pos.second][pos.first] == '9') ++score;
    for (auto dir : aoc::directions) {
      std::pair<int, int> n{pos.first + dir.first, pos.second + dir.second};
      if (aoc::out_of_bounds(n.first, n.second, width, height)) continue;
      if (visited.contains(n) && input[n.second][n.first] == '9') ++distinct_paths;
      if (!visited.contains(n) && input[n.second][n.first] - input[pos.second][pos.first] == 1) {
        if (!distinct) visited.insert(n);
        q.push(n);
      }
    }
  }

  return score;
}

int main(int argc, char** argv) {
  auto input{aoc::fetch_input(argc, argv)};

  int64_t sum{0}, distinct_score{0};
  for (int y{0}; y < input.size(); ++y)
    for (int x{0}; x < input.at(y).size(); ++x) {
      if (input[y][x] == '0') {
        sum += traverse(input, x, y);
        distinct_score += traverse(input, x, y, true);
      }
    }

  std::print("{}, {}\n", sum, distinct_score);
}
