#pragma once

#include <cstdlib>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <print>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace aoc {

inline std::vector<std::string> fetch_input(int argc, char **argv) {
  std::vector<std::string> result;
  std::string line;
  if (argc >= 2) {
    while (!std::getline(std::cin, line).eof()) result.emplace_back(line);
    return result;
  }
  if (argc == 0) throw std::range_error{"No executable name argument provided"};
  std::stringstream path_stream{std::filesystem::path{argv[0]}.filename().string()};
  size_t value;
  path_stream >> value;
  const auto output_path{std::format("/tmp/aoc-input-{}", value)};

  if (!std::filesystem::exists(output_path)) {
    const auto input_path{std::format("https://adventofcode.com/2024/day/{}/input", value)};
    const auto session_cookie{std::getenv("AOC_SESSION")};
    if (session_cookie == nullptr) throw std::runtime_error{"Provide your session cookie in $AOC_SESSION"};

    const int result{
        std::system(std::format(R"(wget --quiet --header="Cookie: session={}" --output-document="{}" {})",
                                session_cookie, output_path, input_path)
                        .data())};
    if (result != 0) throw std::runtime_error{"wget returned non-zero exit code"};
  }

  std::ifstream file{output_path};
  if (!file) throw std::runtime_error{"Failed to open the input file"};

  while (std::getline(file, line)) result.emplace_back(line);
  return result;
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
