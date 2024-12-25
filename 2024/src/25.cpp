#include <aoc/input.hpp>
#include <array>
#include <print>
#include <set>

const char empty{'.'}, full{'#'};

int main(int argc, char** argv) {
  auto input{aoc::fetch_input(argc, argv)};
  input.emplace_back("");
  std::set<std::array<int, 5>> locks, keys;
  std::vector<std::string> schema;
  for (auto line : input)
    if (!line.empty())
      schema.emplace_back(line);
    else {
      std::array cols{-1, -1, -1, -1, -1};
      for (auto row : schema)
        for (int i{0}; i < row.size(); ++i)
          if (row[i] == full) ++cols[i];
      auto& container{(schema[0].contains(empty)) ? keys : locks};
      container.emplace(cols);
      schema.clear();
    }

  int pairs{0};
  bool valid{true};
  for (auto l : locks)
    for (auto k : keys) {
      for (int i{0}; i < k.size(); ++i)
        if (l[i] + k[i] > 5) {
          valid = false;
          break;
        }
      if (valid) ++pairs;
      valid = true;
    }

  std::println("{}", pairs);
}
