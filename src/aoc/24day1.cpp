#include <algorithm>
#include <unordered_map>

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
std::pair<std::vector<int>, std::vector<int>> get_lists(const char* filename)
{
    const std::vector<std::string> lines = aoc::read_lines(filename);

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
    // NOTE: lists are deliberately copied so that the sort below doesn't change the original lists
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

void part2(const std::vector<int>& left_list, const std::vector<int>& right_list)
{
    // count all occurrences in `right_list`.

    std::unordered_map<int, int> occurrences;
    for (auto n : right_list) {
        if (occurrences.contains(n)) {
            ++occurrences[n];
        } else {
            occurrences[n] = 1;
        }
    }

    // compute total similarity.

    int similarity = 0;
    for (auto n : left_list) {
        if (occurrences.contains(n)) {
            similarity += n * occurrences[n];
        }
    }

    printf("Day 1 Part 2: %d\n", similarity);
}

int main(int argc, char** argv)
{
    assert(argc == 2);
    const char* filename = argv[1];

    const auto [left_list, right_list] = get_lists(filename);

    part1(left_list, right_list);
    part2(left_list, right_list);

    return 0;
}
