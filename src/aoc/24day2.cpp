#include "common.h"
#include "io.h"

/**
 * Get all reports.
 */
std::vector<std::vector<int>> get_reports(const char* filename)
{
    const auto lines = aoc::read_lines(filename);
    std::vector<std::vector<int>> reports(lines.size());

    for (int i = 0; i < lines.size(); ++i) {
        // first split each line by " " character
        const auto levels_as_strings = aoc::split(lines[i], " ");

        // then convert each level into integer
        reports[i].reserve(levels_as_strings.size());
        for (const auto& level_as_string : levels_as_strings) {
            reports[i].push_back(std::stoi(level_as_string));
        }
    }

    return reports;
}

/**
 * Returns whether a report is safe.
 */
bool is_safe(const std::vector<int>& report)
{
    const auto first_comparison = report[0] <=> report[1];

    for (int i = 0; i <= report.size() - 2; ++i) {
        // comparisons for neighboring levels must match the first one.
        const auto curr_comparison = report[i] <=> report[i + 1];
        if (curr_comparison != first_comparison) {
            return false;
        }
        // difference must be 1, 2, or 3.
        const int diff = abs(report[i] - report[i + 1]);
        if (diff == 0 || diff > 3) {
            return false;
        }
    }

    return true;
}

void part1(const std::vector<std::vector<int>>& reports)
{
    int count_safe = 0;
    for (const auto& report : reports) {
        if (is_safe(report)) {
            ++count_safe;
        }
    }

    printf("Day 2 Part 1: %d\n", count_safe);
}

int main(int argc, char** argv)
{
    assert(argc == 2);
    const char* filename = argv[1];

    const auto reports = get_reports(filename);

    part1(reports);

    return 0;
}
