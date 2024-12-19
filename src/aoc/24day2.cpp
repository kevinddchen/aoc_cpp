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

int main(int argc, char** argv)
{
    assert(argc == 2);
    const char* filename = argv[1];

    const auto reports = get_reports(filename);

    for (auto report : reports) {
        for (int x : report) {
            printf("%d ", x);
        }
        printf("\n");
    }

    return 0;
}
