#include <aoc/input.hpp>
#include <aoc/utils.hpp>
#include <cstdint>
#include <map>
#include <print>
#include <string>

std::map<std::pair<int64_t, int>, int64_t> stone_blinks_to_res;

int64_t blink(int64_t stone, int blinks) {
  if (blinks == 0) return 1;
  if (stone_blinks_to_res.contains({stone, blinks})) return stone_blinks_to_res.at({stone, blinks});

  int64_t res;
  if (stone == 0)
    res = blink(1, blinks - 1);
  else if (auto str{std::to_string(stone)}; str.size() % 2 == 0) {
    res = blink(std::stoll(str.substr(0, str.size() / 2)), blinks - 1) +
          blink(std::stoll(str.substr(str.size() / 2, str.size() / 2)), blinks - 1);
  } else
    res = blink(stone * 2024, blinks - 1);

  stone_blinks_to_res.insert({{stone, blinks}, res});
  return res;
}

int main(int argc, char** argv) {
  auto input{aoc::fetch_input(argc, argv).front()};
  std::vector<int64_t> stones;
  std::int64_t val;
  std::stringstream stream{input};
  while (stream >> val) stones.emplace_back(val);

  const int blinks{75};
  int64_t count{0};
  for (auto stone : stones) count += blink(stone, blinks);
  std::println("{}\n", count);
}
