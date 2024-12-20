#include <aoc/input.hpp>
#include <aoc/utils.hpp>
#include <cstdlib>
#include <print>
#include <queue>
#include <tuple>

using Vertex = std::tuple<std::pair<int, int>, int>;
using Path = std::tuple<std::pair<int, int>, std::pair<int, int>>;

const char start{'S'}, end{'E'}, track{'.'}, wall{'#'};
const int cheat_duration{20}, threshold{-100};

int main(int argc, char** argv) {
  auto input{aoc::fetch_input(argc, argv)};
  const auto w{input.front().size()}, h{input.size()};
  std::pair<int, int> start_pos, end_pos;
  for (int y{0}; y < input.size(); ++y)
    if (auto x{input[y].find(start)}; x != std::string::npos)
      start_pos = {x, y};
    else if (auto x{input[y].find(end)}; x != std::string::npos)
      end_pos = {x, y};

  std::map<std::pair<int, int>, int> dist;
  dist[start_pos] = 0;
  std::priority_queue<Vertex> q;
  q.emplace(start_pos, 0);

  while (!q.empty()) {
    auto [pos, weight]{q.top()};
    q.pop();

    for (auto dir : aoc::directions) {
      std::pair new_pos{pos.first + dir.first, pos.second + dir.second};
      if (aoc::out_of_bounds(new_pos.first, new_pos.second, w, h) ||
          input[new_pos.second][new_pos.first] == wall)
        continue;
      if (!dist.contains(new_pos) || dist[new_pos] > dist[pos] + 1) {
        dist[new_pos] = dist[pos] + 1;
        q.emplace(new_pos, dist[new_pos]);
      }
    }
  }

  std::map<Path, int> cheats;
  for (int y{1}; y < input.size() - 1; ++y)
    for (int x{1}; x < input[y].size() - 1; ++x) {
      if (input[y][x] == wall) continue;
      for (int i{y - cheat_duration}; i <= y + cheat_duration; ++i)
        for (int j{x - cheat_duration}; j <= x + cheat_duration; ++j) {
          const int man{std::abs(x - j) + std::abs(y - i)};
          if (man > cheat_duration) continue;
          if (aoc::out_of_bounds(j, i, w, h) || input[i][j] == wall) continue;
          const std::pair pos{x, y}, far{j, i};
          const int d{dist[pos] - dist[far] + man};
          if (d <= threshold)
            if (!cheats.contains({pos, far}) || cheats[{pos, far}] > d) cheats[{pos, far}] = d;
        }
    }

  std::println("{}", cheats.size());
}
