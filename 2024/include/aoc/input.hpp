#pragma once

#include <cstdlib>
#include <filesystem>
#include <format>
#include <fstream>
#include <print>
#include <sstream>
#include <stdexcept>
#include <string>

namespace aoc {

inline std::stringstream fetch_input(const char* day) {
  std::stringstream path_stream{std::filesystem::path{day}.filename().string()};
  size_t value;
  path_stream >> value;
  const auto output_path{std::format("/tmp/aoc-input-{}", value)};

  if (!std::filesystem::exists(output_path)) {
    const auto input_path{std::format("https://adventofcode.com/2024/day/{}/input", value)};
    const auto session_cookie{std::getenv("AOC_SESSION")};
    if (session_cookie == nullptr) throw std::runtime_error{"Provide you AoC session cookie in $AOC_SESSION"};

    const int result{
        std::system(std::format(R"(wget --quiet --header="Cookie: session={}" --output-document="{}" {})",
                                session_cookie, output_path, input_path)
                        .data())};
    if (result != 0) throw std::runtime_error{"wget returned non-zero exit code"};
  }

  std::ifstream file{output_path};
  if (!file) throw std::runtime_error{"Failed to open the input file"};

  std::stringstream input;
  input << file.rdbuf();
  return input;
}

}  // namespace aoc
