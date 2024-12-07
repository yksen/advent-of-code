#include <aoc/input.hpp>
#include <print>

int main(int argc, char** argv) {
  auto input{aoc::fetch_input(argc, argv)};
  std::string line{};
  while (input >> line) std::print("{}\n", line);
}
