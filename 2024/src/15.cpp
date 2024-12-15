#include <aoc/input.hpp>
#include <aoc/utils.hpp>
#include <cstdint>
#include <print>
#include <queue>
#include <set>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

const char robot{'@'}, box{'O'}, wall{'#'}, empty{'.'};
const char l_box{'['}, r_box{']'};

auto parse_input(const std::vector<std::string>& input, bool big) {
  std::vector<std::string> map;
  std::vector<std::pair<int, int>> moves;
  bool parse_moves{false};
  std::pair<int, int> pos;
  for (int y{0}; y < input.size(); ++y) {
    const auto row{input[y]};
    if (row.empty()) {
      parse_moves = true;
      continue;
    }
    if (!parse_moves) {
      std::string nrow{(big) ? "" : row};
      if (big) {
        for (auto c : row)
          if (c == robot)
            nrow += "@.";
          else if (c == box)
            nrow += "[]";
          else
            nrow += std::string(2, c);
      }
      map.emplace_back(nrow);
      if (auto x{nrow.find(robot)}; x != std::string::npos) pos = {x, y};
    } else
      for (const auto c : row) {
        auto parse_move{[](const auto c) {
          switch (c) {
            case '^':
              return aoc::directions[0];
            case '>':
              return aoc::directions[1];
            case 'v':
              return aoc::directions[2];
            case '<':
              return aoc::directions[3];
            default:
              std::unreachable();
          }
        }};
        moves.emplace_back(parse_move(c));
      }
  }
  return std::make_tuple(map, moves, pos);
}

int main(int argc, char** argv) {
  auto input{aoc::fetch_input(argc, argv)};
  for (const bool big : {false, true}) {
    auto [map, moves, pos]{parse_input(input, big)};

    for (const auto move : moves) {
      const int nx{pos.first + move.first}, ny{pos.second + move.second};
      auto& nc{map[ny][nx]};
      bool vertical{pos.second != ny};
      bool can_move{false};
      if (nc == box) {
        int x{nx + move.first}, y{ny + move.second};
        while (map[y][x] != wall) {
          if (map[y][x] == empty) {
            can_move = true;
            map[y][x] = box;
            nc = empty;
            break;
          }
          x = x + move.first;
          y = y + move.second;
        }
      } else if (nc == l_box || nc == r_box) {
        if (!vertical) {
          int x{nx + move.first}, y{pos.second};
          while (map[y][x] != wall) {
            if (map[y][x] == empty) {
              bool alt{(move.first < 0) ? true : false};
              while (x != pos.first + move.first) {
                map[y][x] = (alt) ? '[' : ']';
                x = x - move.first;
                alt = !alt;
              }
              can_move = true;
              break;
            }
            x = x + move.first;
          }

        } else {
          can_move = true;
          std::set<std::pair<int, int>> boxes;
          std::queue<std::pair<int, int>> q;
          int offset{(nc == r_box) ? -1 : 0};
          q.emplace(nx + offset, ny);
          while (!q.empty()) {
            auto box{q.front()};
            q.pop();
            int x{box.first}, y{box.second + move.second};
            const auto l{map[y][x]}, r{map[y][x + 1]};
            if (l == wall || r == wall) {
              can_move = false;
              break;
            }
            boxes.emplace(box);
            if (l == l_box) q.emplace(x, y);
            if (l == r_box) q.emplace(x - 1, y);
            if (r == l_box) q.emplace(x + 1, y);
          }
          if (can_move) {
            for (auto box : boxes) {
              const int x{box.first}, y{box.second};
              map[y][x] = '.';
              map[y][x + 1] = '.';
            }
            for (auto box : boxes) {
              const int x{box.first}, y{box.second + move.second};
              map[y][x] = '[';
              map[y][x + 1] = ']';
            }
          }
        }
      } else if (nc != wall)
        can_move = true;
      if (can_move) {
        map[pos.second][pos.first] = empty;
        pos = {nx, ny};
        nc = robot;
      }
    }

    int64_t sum{0};
    for (int y{0}; y < map.size(); ++y)
      for (int x{0}; x < map.front().size(); ++x)
        if (map[y][x] == box || map[y][x] == l_box) sum += 100 * y + x;

    std::print("{} ", sum);
  }
}
