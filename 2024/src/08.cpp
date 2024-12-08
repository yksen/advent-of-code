#include <algorithm>
#include <aoc/input.hpp>
#include <aoc/utils.hpp>
#include <map>
#include <print>
#include <set>

int main(int argc, char** argv) {
  auto input{aoc::fetch_input(argc, argv)};
  const auto [width, height]{std::pair{input.size(), input.front().size()}};
  std::vector<std::string> antinodes(width, std::string(height, '.'));

  std::map<char, std::set<std::pair<int, int>>> antennas;
  for (int y{0}; y < input.size(); ++y)
    for (int x{0}; x < input.at(y).size(); ++x) {
      char c{input[y][x]};
      if (c == '.' || c == '#') continue;
      if (antennas.contains(c))
        antennas.at(c).insert({x, y});
      else
        antennas[c] = {{x, y}};
    }

  for (auto [c, positions] : antennas) {
    for (auto start_pos : positions) {
      for (auto end_pos : positions) {
        if (start_pos == end_pos) continue;
        antinodes[start_pos.second][start_pos.first] = '#';
        antinodes[end_pos.second][end_pos.first] = '#';
        int x{2 * end_pos.first - start_pos.first};
        int y{2 * end_pos.second - start_pos.second};
        while (!aoc::out_of_bounds(x, y, width, height)) {
          antinodes[y][x] = '#';
          x += end_pos.first - start_pos.first;
          y += end_pos.second - start_pos.second;
        }
      }
    }
  }

  size_t antinode_count{0};
  for (auto row : antinodes) antinode_count += std::count(row.begin(), row.end(), '#');
  std::print("{}\n", antinode_count);
}
