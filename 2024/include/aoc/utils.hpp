#pragma once

#include <algorithm>
#include <print>
#include <string>
#include <string_view>
#include <vector>

namespace aoc {

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
auto format_vector(const std::vector<Type> &v) {
  std::string res{};
  for (auto x : v) res += std::to_string(x) + " ";
  res.resize(res.size() - 1);
  return std::format("{}", res);
}

}  // namespace aoc
