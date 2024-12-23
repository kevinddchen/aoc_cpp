#include "common.h"
#include "io.h"

/**
 * Get all reports from file.
 */
std::vector<std::vector<int>> get_reports(const char* filename)
{
    const auto lines = aoc::read_lines(filename);

    std::vector<std::vector<int>> reports;
    reports.reserve(lines.size());

    for (const auto& line : lines) {
        // first split each line by " " character
        const auto levels_as_strings = aoc::split(line, " ");

        // then convert each level into integer
        reports.emplace_back(aoc::stoi(levels_as_strings));
    }

    return reports;
}

/**
 * Copy a report with ith level removed.
 */
std::vector<int> copy_exclude_ith(const std::vector<int>& report, int i)
{
    std::vector<int> new_report = report;
    new_report.erase(new_report.begin() + i);
    return new_report;
}

/**
 * Returns whether a report is safe.
 * @param report Report, containing list of levels
 * @param can_tolerate If true, can remove a single level from the report
 */
bool is_safe(const std::vector<int>& report, bool can_tolerate = false)
{
    // first, compute all comparisons and differences
    std::vector<std::strong_ordering> comparisons(report.size() - 1, std::strong_ordering::equal);
    std::vector<int> differences(report.size() - 1);
    for (int i = 0; i <= report.size() - 2; ++i) {
        comparisons[i] = report[i] <=> report[i + 1];
        differences[i] = abs(report[i] - report[i + 1]);
    }

    // check that all differences are 1, 2, or 3
    for (int i = 0; i < differences.size(); ++i) {
        if (differences[i] == 0 || differences[i] > 3) {
            // there is an issue...
            if (can_tolerate) {
                // we can try removing level i or i+1...
                return is_safe(copy_exclude_ith(report, i)) || is_safe(copy_exclude_ith(report, i + 1));
            } else {
                return false;
            }
        }
    }

    // check that all comparisons are equal to the previous one
    for (int i = 1; i < differences.size(); ++i) {
        if (comparisons[i] != comparisons[i - 1]) {
            // there is an issue...
            if (can_tolerate) {
                // we can try removing level i-1, i, or i+1...
                return is_safe(copy_exclude_ith(report, i - 1)) || is_safe(copy_exclude_ith(report, i)) ||
                       is_safe(copy_exclude_ith(report, i + 1));
            } else {
                return false;
            }
        }
    }

    return true;
}

/**
 * Count the number of safe reports.
 * @param reports List of reports
 * @param can_tolerate If true, can remove a single level from a report
 */
int count_safe(const std::vector<std::vector<int>>& reports, bool can_tolerate)
{
    int num_safe = 0;
    for (const auto& report : reports) {
        if (is_safe(report, can_tolerate)) {
            ++num_safe;
        }
    }
    return num_safe;
}

void part1(const std::vector<std::vector<int>>& reports)
{
    const int num_safe = count_safe(reports, false);
    printf("Day 2 Part 1: %d\n", num_safe);
}

void part2(const std::vector<std::vector<int>>& reports)
{
    const int num_safe = count_safe(reports, true);
    printf("Day 2 Part 2: %d\n", num_safe);
}

int main(int argc, char** argv)
{
    assert(argc == 2);
    const char* filename = argv[1];

    const auto reports = get_reports(filename);

    part1(reports);
    part2(reports);

    return 0;
}
