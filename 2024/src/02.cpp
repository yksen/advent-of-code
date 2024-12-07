#include <algorithm>
#include <aoc/input.hpp>
#include <aoc/utils.hpp>
#include <format>
#include <numeric>
#include <print>

bool is_valid(const auto& c) {
  const int max_difference{3};
  auto exceeds_limit{[](const auto val) { return std::abs(val) > max_difference || val == 0; }};
  auto diff{c};
  std::adjacent_difference(diff.begin(), diff.end(), diff.begin());
  if (!std::all_of(std::next(diff.begin()), diff.end(),
                   [&](auto val) { return aoc::sign(val) == aoc::sign(diff.back()); }))
    return false;
  if (std::any_of(std::next(diff.begin()), diff.end(), [&](auto val) { return exceeds_limit(val); }))
    return false;
  return true;
}

int main() {
  auto input{aoc::parse_rows<int>()};
  int safe_reports{0};
  int safe_reports_dampened{0};

  for (const auto& report : input) {
    if (is_valid(report)) {
      ++safe_reports;
      continue;
    };

    for (size_t i{0}; i < report.size(); ++i) {
      auto tmp{report};
      tmp.erase(std::next(tmp.begin(), i));
      if (is_valid(tmp)) {
        ++safe_reports_dampened;
        break;
      }
    }
  }

  safe_reports_dampened += safe_reports;
  std::print("{} {}\n", safe_reports, safe_reports_dampened);
}
