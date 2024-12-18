#include <aoc/input.hpp>
#include <aoc/utils.hpp>
#include <print>
#include <queue>
#include <tuple>

using Vertex = std::tuple<std::pair<int, int>, int>;

const int w{71}, h{71}, n_bytes{1024};
const std::pair<int, int> start_pos{0, 0}, end_pos{w - 1, h - 1};

int main(int argc, char** argv) {
  auto input{aoc::fetch_input(argc, argv)};
  std::vector<std::pair<int, int>> bytes;
  for (auto line : input) {
    auto n{aoc::get_numbers(line)};
    bytes.emplace_back(n[0], n[1]);
  }
  std::vector<std::vector<bool>> map(h, std::vector<bool>(w));
  for (int i{0}; i < n_bytes; ++i) {
    auto b{bytes[i]};
    map[b.second][b.first] = true;
  }
  std::map<std::pair<int, int>, int> dist;
  int id{n_bytes - 1};

  do {
    ++id;
    auto b{bytes[id]};
    map[b.second][b.first] = true;
    dist.clear();
    dist[start_pos] = 0;
    std::priority_queue<Vertex> q;
    q.emplace(start_pos, 0);

    while (!q.empty()) {
      auto [pos, weight]{q.top()};
      q.pop();

      for (auto dir : aoc::directions) {
        std::pair new_pos{pos.first + dir.first, pos.second + dir.second};
        if (aoc::out_of_bounds(new_pos.first, new_pos.second, w, h) || map[new_pos.second][new_pos.first])
          continue;
        if (!dist.contains(new_pos) || dist[new_pos] > dist[pos] + 1) {
          dist[new_pos] = dist[pos] + 1;
          q.emplace(new_pos, dist[new_pos]);
        }
      }
    }

  } while (dist.contains(end_pos));

  auto b{bytes[id]};
  std::println("{},{}", b.first, b.second);
}
