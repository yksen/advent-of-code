#include <aoc/input.hpp>
#include <print>

int main(int argc, char** argv) {
  auto input{aoc::fetch_input(argv[0])};
  std::string line{};
  while (input >> line) std::print("{}\n", line);
}
