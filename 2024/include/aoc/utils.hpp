#pragma once

#include <algorithm>
#include <iostream>
#include <print>
#include <sstream>
#include <string>
#include <string_view>
#include <tuple>
#include <utility>
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

template <typename Type>
std::vector<std::vector<Type>> parse_rows() {
  std::vector<std::vector<Type>> result;
  std::string line;
  while (std::getline(std::cin, line) && !line.empty()) {
    result.emplace_back();
    std::stringstream stream{line};
    Type var;
    while (stream >> var) {
      result.back().emplace_back(var);
    }
  }
  return result;
}

template <typename Tuple, size_t... Indices>
void parse_vectors_tuple(Tuple &result, std::stringstream &stream, std::index_sequence<Indices...>) {
  (([&]() {
     using ElementType = typename std::tuple_element<Indices, Tuple>::type::value_type;
     ElementType value;
     if (stream >> value) {
       std::get<Indices>(result).push_back(value);
     }
   }()),
   ...);
}

template <typename... Args>
std::tuple<std::vector<Args>...> parse_columns() {
  std::tuple<std::vector<Args>...> result;
  std::string line;
  while (std::getline(std::cin, line) && !line.empty()) {
    std::stringstream stream{line};
    parse_vectors_tuple(result, stream, std::index_sequence_for<Args...>{});
  }
  return result;
}

}  // namespace aoc
