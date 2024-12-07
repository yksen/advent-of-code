#include <algorithm>
#include <aoc/input.hpp>
#include <aoc/utils.hpp>
#include <cstdio>
#include <map>

int main() {
  auto [a, b]{aoc::parse_columns<int, int>()};
  std::sort(a.begin(), a.end());
  std::sort(b.begin(), b.end());

  int64_t sum{0};
  for (int i{0}; i < a.size(); ++i) {
    sum += (a[i] > b[i]) ? a[i] - b[i] : b[i] - a[i];
  }

  std::map<int64_t, int64_t> scores;
  int64_t total_score{0};
  for (int i{0}; i < a.size(); ++i) {
    scores.insert_or_assign(a[i], a[i] * std::count(b.begin(), b.end(), a[i]));
  }

  for (const auto x : a) {
    total_score += scores.at(x);
  }

  printf("%ld %ld\n", sum, total_score);
}
