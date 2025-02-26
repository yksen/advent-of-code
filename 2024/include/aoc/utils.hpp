#pragma once

#include <algorithm>
#include <array>
#include <print>
#include <regex>
#include <string>
#include <string_view>
#include <vector>

template <typename T>
std::pair<T, T> operator+(const std::pair<T, T>& l, const std::pair<T, T>& r) {
  return {l.first + r.first, l.second + r.second};
}

template <typename T>
std::pair<T, T> operator-(const std::pair<T, T>& l, const std::pair<T, T>& r) {
  return {l.first - r.first, l.second - r.second};
}

namespace aoc {

inline std::vector<std::string> split(std::string s, const std::string& delimiter = " ") {
  std::vector<std::string> tokens;
  size_t pos{0};
  std::string token;
  while ((pos = s.find(delimiter)) != std::string::npos) {
    token = s.substr(0, pos);
    tokens.push_back(token);
    s.erase(0, pos + delimiter.length());
  }
  tokens.push_back(s);

  return tokens;
}

inline auto get_numbers(std::string input) {
  std::vector<int64_t> numbers;
  std::regex pattern{R"(-?\d+)"};
  for (std::sregex_iterator it{input.begin(), input.end(), pattern}, end{}; it != end; ++it)
    numbers.emplace_back(std::stoll(it->str()));
  return numbers;
}

const std::array<std::pair<int, int>, 4> directions{{{0, -1}, {1, 0}, {0, 1}, {-1, 0}}};

inline bool out_of_bounds(int x, int y, size_t w, size_t h) { return x < 0 || y < 0 || x >= w || y >= h; };

inline auto find_all_substr(const std::string_view input, const std::string_view substr) {
  std::vector<size_t> indices;
  size_t index{input.find(substr, 0)};
  while (index != std::string::npos) {
    indices.push_back(index);
    index = input.find(substr, index + 1);
  }
  return indices;
}

template <typename InputIterator, typename Predicate>
auto find_all(InputIterator first, InputIterator last, Predicate pred) {
  std::vector<InputIterator> result;
  while ((first = std::find_if(first, last, pred)) != last) {
    result.push_back(first);
    ++first;
  }
  return result;
}

template <typename Type>
auto sign(const Type val) {
  return (val > Type{0}) - (val < Type{0});
}

template <typename Type>
auto format_vector(const std::vector<Type>& v) {
  std::string res{};
  for (auto x : v) res += std::to_string(x) + " ";
  res.resize(res.size() - 1);
  return std::format("{}", res);
}

}  // namespace aoc
