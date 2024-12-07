#include <algorithm>
#include <aoc/input.hpp>
#include <aoc/utils.hpp>
#include <iostream>
#include <print>
#include <string>
#include <vector>

int main(int argc, char** argv) {
  auto raw_input{aoc::fetch_input(argc, argv)};
  std::vector<std::vector<int64_t>> input;
  for (auto line : raw_input) {
    std::replace(line.begin(), line.end(), ':', ' ');
    std::stringstream stream{line};
    input.emplace_back();
    int64_t val{0};
    while (stream >> val) input.back().emplace_back(val);
  }

  bool valid{false};
  int64_t sum{0};
  for (auto original_row : input) {
    const auto ops_size{original_row.size() - 2};
    for (int a{0}; a <= ops_size; ++a) {
      for (int b{0}; b <= ops_size - a; ++b) {
        int c = ops_size - a - b;
        std::vector<int> ops_dist{a, b, c};
        std::string ops{};
        for (int i{0}; i < 3; ++i)
          for (auto len{0}; len < ops_dist.at(i); ++len) ops += "*+|"[i];

        do {
          auto row{original_row};
          int64_t total{row.at(1)};
          for (int j{0}; j < ops.size(); ++j) {
            if (total > row.front()) break;
            switch (ops.at(j)) {
              case '+':
                total += row.at(j + 2);
                break;
              case '*':
                total *= row.at(j + 2);
                break;
              case '|':
                total = std::stoll(std::to_string(total) + std::to_string(row.at(j + 2)));
                break;
            }
          }
          if (total == row.front()) {
            valid = true;
            sum += total;
            break;
          }
        } while (std::next_permutation(ops.begin(), ops.end()));
        if (valid) break;
      }
      if (valid) {
        valid = false;
        break;
      }
    }
  }

  std::print("{}\n", sum);
}
