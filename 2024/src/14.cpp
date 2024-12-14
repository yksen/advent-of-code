#include <aoc/input.hpp>
#include <aoc/utils.hpp>
#include <array>
#include <cmath>
#include <functional>
#include <iostream>
#include <numeric>
#include <print>
#include <string>
#include <vector>

const int seconds{100};
const int w{101}, h{103};

int main(int argc, char** argv) {
  auto input{aoc::fetch_input(argc, argv)};
  std::vector<std::pair<int, int>> pos;
  std::vector<std::pair<int, int>> vel;

  for (auto line : input) {
    auto n{aoc::get_numbers(line)};
    pos.emplace_back(n[0], n[1]);
    vel.emplace_back(n[2], n[3]);
  }

  for (int sec{0}; true; ++sec) {
    double var{0.0};
    for (int i{0}; i < pos.size(); ++i) {
      auto &p{pos[i]}, v{vel[i]};
      p = {(w + p.first + v.first) % w, (h + p.second + v.second) % h};
      var += std::pow(p.first - w / 2, 2) + std::pow(p.second - h / 2, 2);
    }
    var /= pos.size();
    if (var > 1000.0) continue;
    std::string line{};
    std::getline(std::cin, line);
    std::println("{}, {}", sec + 1, var);
    std::vector<std::vector<int>> map(h, std::vector<int>(w, 0));
    for (auto p : pos) map[p.second][p.first]++;
    for (auto line : map) {
      for (auto n : line) std::print("{}", (n == 0) ? " " : "█");
      std::println();
    }
  }

  std::vector<std::vector<int>> map(h, std::vector<int>(w, 0));
  for (auto p : pos) map[p.second][p.first]++;

  std::array<int, 4> quadrants{0, 0, 0, 0};
  for (int i : {0, 1})
    for (int j : {0, 1})
      for (int y{i * (h / 2 + 1)}; y < h / (2 - i); ++y)
        for (int x{j * (w / 2 + 1)}; x < w / (2 - j); ++x) {
          quadrants[i * 2 + j] += map[y][x];
        }

  int safety_factor{std::accumulate(quadrants.begin(), quadrants.end(), 1, std::multiplies<int>{})};
  std::println("{}", safety_factor);
}
