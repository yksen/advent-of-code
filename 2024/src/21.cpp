#include <aoc/input.hpp>
#include <aoc/utils.hpp>
#include <map>
#include <numeric>
#include <print>
#include <string>

// clang-format off
std::map<char, std::pair<int, int>> npad{
    {'7', {0, 0}}, {'8', {1, 0}}, {'9', {2, 0}},
    {'4', {0, 1}}, {'5', {1, 1}}, {'6', {2, 1}},
    {'1', {0, 2}}, {'2', {1, 2}}, {'3', {2, 2}},
    {' ', {0, 3}}, {'0', {1, 3}}, {'A', {2, 3}},
};
std::map<char, std::pair<int, int>> dpad{
    {' ', {0, 0}}, {'^', {1, 0}}, {'A', {2, 0}},
    {'<', {0, 1}}, {'v', {1, 1}}, {'>', {2, 1}},
};
// clang-format on

std::map<std::tuple<std::string, int>, int64_t> lengths;

std::string get_path(char s, char e) {
  const auto& pad{(npad.contains(s) && npad.contains(e)) ? npad : dpad};
  const auto [dx, dy]{pad.at(e) - pad.at(s)};
  const auto h{(dx < 0) ? std::string(-dx, '<') : std::string(dx, '>')};
  const auto v{(dy < 0) ? std::string(-dy, '^') : std::string(dy, 'v')};
  const auto [ex, ey]{pad.at(' ') - pad.at(s)};
  const bool vertical_first{(dx > 0 || (dx == ex && ey == 0)) && !(ex == 0 && dy == ey)};
  auto res{((vertical_first) ? v + h : h + v) + 'A'};
  return res;
}

int64_t get_length(const std::string code, int depth) {
  if (lengths.contains({code, depth})) return lengths.at({code, depth});
  if (depth == 0) return code.size();
  int64_t res{0};
  for (int i{0}; i < code.size(); ++i)
    res += get_length(get_path(code[(code.size() + i - 1) % code.size()], code[i]), depth - 1);
  lengths[{code, depth}] = res;
  return res;
}

int main(int argc, char** argv) {
  const auto input{aoc::fetch_input(argc, argv)};
  const auto sum{[&](int depth) {
    return std::accumulate(input.begin(), input.end(), 0ll, [&](int64_t sum, auto code) {
      return sum + std::stoi(code) * get_length(code, depth);
    });
  }};

  std::println("{} {}", sum(4 - 1), sum(27 - 1));
}
