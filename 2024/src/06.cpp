#include <algorithm>
#include <aoc/utils.hpp>
#include <array>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <print>
#include <set>
#include <string>
#include <utility>
#include <vector>

struct Position {
  int x, y;
  std::array<std::pair<int, int>, 4>::const_iterator dir;
  auto operator<=>(const Position&) const = default;
};

const std::array<std::pair<int, int>, 4> directions{{{0, -1}, {1, 0}, {0, 1}, {-1, 0}}};

bool out_of_bounds(int x, int y, const std::vector<std::string>& input) {
  const size_t w{input.front().size()}, h{input.size()};
  return x < 0 || y < 0 || x == w || y == h;
};
void cycle_dir(auto& dir) {
  dir = (dir == std::prev(directions.end()) ? directions.begin() : std::next(dir));
};

bool is_loop(int x, int y, const std::vector<std::string>& input) {
  Position pos{x, y, directions.begin()};
  std::set<Position> path{pos};

  while (true) {
    const int nx{pos.x + pos.dir->first}, ny{pos.y + pos.dir->second};
    if (out_of_bounds(nx, ny, input)) break;
    if (input.at(ny).at(nx) == '#') {
      cycle_dir(pos.dir);
      continue;
    }

    pos.x = nx;
    pos.y = ny;

    if (std::find(path.begin(), path.end(), pos) != path.end()) return true;

    path.emplace(nx, ny, pos.dir);
  }

  return false;
}

int main() {
  std::vector<std::string> input;
  std::string line;
  while (std::getline(std::cin, line) && !line.empty()) input.push_back(line);

  int x, y;
  for (int i{0}; i < input.size(); ++i) {
    auto row{input.at(i)};
    auto it{std::find(row.begin(), row.end(), '^')};
    if (it != row.end()) {
      x = std::distance(row.begin(), it);
      y = i;
      *it = '.';
      break;
    }
  }

  const int start_x{x}, start_y{y};
  std::set<std::pair<int, int>> path{{x, y}};
  auto dir{directions.begin()};

  while (true) {
    const int nx{x + dir->first}, ny{y + dir->second};
    if (out_of_bounds(nx, ny, input)) break;
    if (input.at(ny).at(nx) == '#') {
      cycle_dir(dir);
      continue;
    }
    x = nx;
    y = ny;
    path.emplace(nx, ny);
  }

  const auto length{path.size()};
  int sum{0};
  path.erase(std::find(path.begin(), path.end(), std::make_pair(start_x, start_y)));
  for (auto& [x, y] : path) {
    input.at(y).at(x) = '#';
    sum += (is_loop(start_x, start_y, input) ? 1 : 0);
    input.at(y).at(x) = '.';
  }

  std::print("{}, {}\n", length, sum);
}
