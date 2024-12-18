#include <algorithm>

#include "common.h"
#include "io.h"

namespace
{

/**
 * Parse line into the two integers.
 */
std::pair<int, int> parse_line(const std::string& line)
{
    // HACK: rely on fact that integers are always 5-digits.
    const int a = std::stoi(line.substr(0, 5));
    const int b = std::stoi(line.substr(8, 5));
    return {a, b};
}

void part1()
{
    const auto lines = aoc::read_lines("data/24day1.txt");

    // get the two lists of integers.

    std::vector<int> left_list(lines.size());
    std::vector<int> right_list(lines.size());

    for (int i = 0; i < lines.size(); ++i) {
        const auto [a, b] = parse_line(lines[i]);
        left_list[i] = a;
        right_list[i] = b;
    }

    // sort.

    std::sort(left_list.begin(), left_list.end());
    std::sort(right_list.begin(), right_list.end());

    // compute total distance.

    int distance = 0;
    for (int i = 0; i < lines.size(); ++i) {
        distance += std::abs(left_list[i] - right_list[i]);
    }

    printf("Day 1 Part 1: %d\n", distance);
}

}  // namespace

int main()
{
    part1();
}
