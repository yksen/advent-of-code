#include <aoc/input.hpp>
#include <aoc/utils.hpp>
#include <print>

const int a_cost{3}, b_cost{1};
const int64_t conversion_error{10000000000000};

struct Machine {
  std::pair<int64_t, int64_t> a;
  std::pair<int64_t, int64_t> b;
  std::pair<int64_t, int64_t> p;

  std::pair<int64_t, int64_t> claw_position(int64_t a, int64_t b) const {
    return {a * this->a.first + b * this->b.first, a * this->a.second + b * this->b.second};
  }
};

int main(int argc, char** argv) {
  auto input{aoc::fetch_input(argc, argv)};
  std::vector<Machine> machines;
  for (size_t i{0}; i < input.size(); i += 4) {
    auto a{aoc::get_numbers(input.at(i))};
    auto b{aoc::get_numbers(input.at(i + 1))};
    auto p{aoc::get_numbers(input.at(i + 2))};
    machines.push_back({{a.front(), a.back()},
                        {b.front(), b.back()},
                        {p.front() + conversion_error, p.back() + conversion_error}});
  }

  int64_t min_tokens{0};
  for (const auto m : machines) {
    int64_t b{(m.p.first * m.a.second - m.p.second * m.a.first) /
              (m.b.first * m.a.second - m.b.second * m.a.first)};
    int64_t a{(m.p.second - b * m.b.second) / m.a.second};
    auto claw{m.claw_position(a, b)};
    if (claw.first == m.p.first && claw.second == m.p.second) min_tokens += a * a_cost + b * b_cost;
  }

  std::println("{}", min_tokens);
}
