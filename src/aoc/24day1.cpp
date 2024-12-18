#include <algorithm>

#include "common.h"
#include "io.h"

/**
 * Parse line of text into the two integers.
 */
std::pair<int, int> parse_line(const std::string& line)
{
    // HACK: rely on fact that integers are always 5-digits.
    const int a = std::stoi(line.substr(0, 5));
    const int b = std::stoi(line.substr(8, 5));
    return {a, b};
}

/**
 * Get the left and right lists of numbers.
 */
std::pair<std::vector<int>, std::vector<int>> get_lists()
{
    const std::vector<std::string> lines = aoc::read_lines("data/24day1.txt");

    std::vector<int> left_list(lines.size());
    std::vector<int> right_list(lines.size());

    for (int i = 0; i < lines.size(); ++i) {
        const auto [a, b] = parse_line(lines[i]);
        left_list[i] = a;
        right_list[i] = b;
    }

    return std::make_pair(std::move(left_list), std::move(right_list));
}

void part1(std::vector<int> left_list, std::vector<int> right_list)
{
    assert(left_list.size() == right_list.size());

    // sort.

    std::sort(left_list.begin(), left_list.end());
    std::sort(right_list.begin(), right_list.end());

    // compute total distance.

    int distance = 0;
    for (int i = 0; i < left_list.size(); ++i) {
        distance += std::abs(left_list[i] - right_list[i]);
    }

    printf("Day 1 Part 1: %d\n", distance);
}

int main()
{
    const auto [left_list, right_list] = get_lists();

    part1(left_list, right_list);

    printf("%d\n", left_list[0]);
}
