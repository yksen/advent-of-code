#include <algorithm>
#include <aoc/input.hpp>
#include <aoc/utils.hpp>
#include <map>
#include <print>
#include <queue>
#include <set>
#include <vector>

using Vertex = std::tuple<std::pair<int, int>, std::pair<int, int>, int>;

const char start{'S'}, end{'E'}, wall{'#'};
const int step_cost{1}, rotation_cost{1000};

int main(int argc, char** argv) {
  auto input{aoc::fetch_input(argc, argv)};
  std::pair<int, int> start_pos;
  for (int y{0}; y < input.size(); ++y) {
    auto x{input[y].find(start)};
    if (x != std::string::npos) start_pos = {x, y};
  }

  auto cmp{[](Vertex l, Vertex r) { return std::get<int>(l) > std::get<int>(r); }};
  std::priority_queue<Vertex, std::vector<Vertex>, decltype(cmp)> q;
  q.emplace(std::make_pair(start_pos.first, start_pos.second), aoc::directions[1], 0);

  std::map<std::pair<int, int>, int> distance;
  distance[start_pos] = 0;
  std::pair<int, int> end_pos;
  std::map<std::pair<int, int>, std::set<std::pair<int, int>>> parents;

  while (!q.empty()) {
    auto [pos, rot, weight]{q.top()};
    q.pop();

    for (auto dir : aoc::directions) {
      std::pair<int, int> new_pos{pos.first + dir.first, pos.second + dir.second};
      if (input[new_pos.second][new_pos.first] == wall) continue;
      int new_weight{step_cost + ((rot != dir) ? rotation_cost : 0)};
      if (!distance.contains(new_pos) || distance[new_pos] >= distance[pos] + new_weight ||
          distance[new_pos] == distance[pos] - rotation_cost + step_cost)
        parents[new_pos].emplace(pos);
      if (!distance.contains(new_pos) || distance[new_pos] > distance[pos] + new_weight) {
        distance[new_pos] = distance[pos] + new_weight;
        q.emplace(new_pos, dir, distance[new_pos]);
      }
      if (input[new_pos.second][new_pos.first] == end) {
        end_pos = new_pos;
        q = {};
        break;
      }
    }
  }

  std::vector<std::pair<int, int>> best_tiles;
  std::queue<std::pair<int, int>> s;
  s.emplace(end_pos);
  while (!s.empty()) {
    auto pos{s.front()};
    s.pop();
    if (std::find(best_tiles.begin(), best_tiles.end(), pos) == best_tiles.end())
      best_tiles.emplace_back(pos);
    for (auto parent : parents[pos])
      if (std::find(best_tiles.begin(), best_tiles.end(), parent) == best_tiles.end() &&
          (distance[parent] < distance[pos] || distance[parent] - distance[pos] == rotation_cost - step_cost))
        s.emplace(parent);
  }

  std::println("{} {}", distance[end_pos], best_tiles.size());
}
