#include <algorithm>
#include <aoc/input.hpp>
#include <iterator>
#include <print>
#include <set>
#include <sstream>

int64_t check(std::string d, const std::set<std::string>& patterns) {
  std::vector<int64_t> ways(d.size() + 1, 0);
  ways[0] = 1;

  for (int r{1}; r < d.size() + 1; ++r)
    for (int l{0}; l < r; ++l)
      if (patterns.contains(d.substr(l, r - l))) ways[r] += ways[l];
  return ways.back();
}

int main(int argc, char** argv) {
  auto input{aoc::fetch_input(argc, argv)};
  std::set<std::string> patterns, designs{std::next(input.begin(), 2), input.end()};
  std::replace(input[0].begin(), input[0].end(), ',', ' ');
  std::stringstream stream{input[0]};
  std::string s;
  while (stream >> s) patterns.emplace(s);

  int64_t possible_designs{0}, ways{0};
  for (auto d : designs)
    if (auto res{check(d, patterns)}) ++possible_designs, ways += res;

  std::println("{} {}", possible_designs, ways);
}
