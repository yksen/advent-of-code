#include <aoc/input.hpp>
#include <aoc/utils.hpp>
#include <print>
#include <queue>
#include <set>
#include <utility>

std::set<std::set<std::pair<int, int>>> get_gardens(const std::vector<std::string>& input) {
  size_t w{input.front().size()}, h{input.size()};
  std::set<std::pair<int, int>> visited;
  std::set<std::set<std::pair<int, int>>> gardens;

  for (int y{0}; y < input.size(); ++y) {
    for (int x{0}; x < input.at(y).size(); ++x) {
      if (visited.contains({x, y})) continue;
      decltype(gardens)::value_type garden;
      std::queue<std::pair<int, int>> q;
      garden.emplace(x, y);
      visited.emplace(x, y);
      q.emplace(x, y);
      while (!q.empty()) {
        const auto pos{q.front()};
        q.pop();
        for (const auto dir : aoc::directions) {
          int nx{pos.first + dir.first}, ny{pos.second + dir.second};
          if (aoc::out_of_bounds(nx, ny, w, h)) continue;
          if (!visited.contains({nx, ny}) && input[y][x] == input[ny][nx]) {
            garden.emplace(nx, ny);
            visited.emplace(nx, ny);
            q.push({nx, ny});
          }
        }
      }
      gardens.emplace(garden);
    }
  }
  return gardens;
}

void traverse(const std::vector<std::string>& input, const std::set<std::pair<int, int>>& garden,
              std::set<std::pair<std::pair<int, int>, std::pair<int, int>>>& checked, std::pair<int, int> dir,
              int x, int y, int nx, int ny) {
  const size_t w{input.front().size()}, h{input.size()};
  while (!aoc::out_of_bounds(x + dir.first, y + dir.second, w, h) && garden.contains({x, y}) &&
         (aoc::out_of_bounds(nx + dir.first, ny + dir.second, w, h) || !garden.contains({nx, ny}))) {
    x += dir.first;
    y += dir.second;
    nx += dir.first;
    ny += dir.second;
    checked.insert({{x, y}, {nx, ny}});
  }
}

int main(int argc, char** argv) {
  auto input{aoc::fetch_input(argc, argv)};
  const size_t w{input.front().size()}, h{input.size()};
  const auto gardens{get_gardens(input)};

  int64_t total_cost{0}, total_cost2{0};
  for (const auto garden : gardens) {
    std::set<std::pair<std::pair<int, int>, std::pair<int, int>>> checked;
    size_t area{garden.size()};
    size_t perimeter{0}, perimeter2{0};
    for (const auto plot : garden) {
      for (const auto dir : aoc::directions) {
        const int nx{plot.first + dir.first}, ny{plot.second + dir.second};
        bool oob{aoc::out_of_bounds(nx, ny, w, h)};
        bool within{garden.contains({nx, ny})};

        if ((oob || !within) && !checked.contains({{plot.first, plot.second}, {nx, ny}})) {
          checked.insert({{plot.first, plot.second}, {nx, ny}});
          ++perimeter2;
          for (const auto dir : aoc::directions)
            traverse(input, garden, checked, dir, plot.first, plot.second, nx, ny);
        }
        if (oob) {
          ++perimeter;
          continue;
        }
        if (!within) {
          ++perimeter;
        }
      }
    }
    total_cost += perimeter * area;
    total_cost2 += perimeter2 * area;
  }
  std::println("{}, {}", total_cost, total_cost2);
}
