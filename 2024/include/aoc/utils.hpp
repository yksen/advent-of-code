#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

namespace aoc {

template <size_t Index = 0, typename... Args>
void parse_tuple(std::stringstream &stream, std::tuple<Args...> &tuple) {
  if constexpr (Index < sizeof...(Args)) {
    stream >> std::get<Index>(tuple);
    parse_tuple<Index + 1, Args...>(stream, tuple);
  }
}

template <typename... Args>
std::vector<std::tuple<Args...>> parse_input_vector() {
  std::vector<std::tuple<Args...>> result;
  std::string line;
  while (std::getline(std::cin, line) && !line.empty()) {
    std::stringstream stream{line};
    std::tuple<Args...> item;
    parse_tuple(stream, item);
    result.push_back(item);
  }
  return result;
}

template <typename Tuple, size_t... Indices>
void parse_vectors_tuple(Tuple &result, std::stringstream &stream,
                         std::index_sequence<Indices...>) {
  (([&]() {
     using ElementType =
         typename std::tuple_element<Indices, Tuple>::type::value_type;
     ElementType value;
     if (stream >> value) {
       std::get<Indices>(result).push_back(value);
     }
   }()),
   ...);
}

template <typename... Args>
std::tuple<std::vector<Args>...> parse_input_tuple() {
  std::tuple<std::vector<Args>...> result;
  std::string line;
  while (std::getline(std::cin, line) && !line.empty()) {
    std::stringstream stream{line};
    parse_vectors_tuple(result, stream, std::index_sequence_for<Args...>{});
  }
  return result;
}

} // namespace aoc
