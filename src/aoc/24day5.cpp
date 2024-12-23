#include <algorithm>

#include "common.h"
#include "io.h"


struct Rule {
    int first;
    int second;

    Rule(int first, int second) : first(first), second(second) {}
};

struct Update {
    std::vector<int> pages;

    Update(std::vector<int> pages) : pages(std::move(pages)) {}
};

/**
 * Given lines, parse the rules.
 * @param begin Iterator to start of vector of lines.
 * @param end Iterator to end of vector of lines.
 */
std::vector<Rule> get_rules(
    std::vector<std::string>::const_iterator begin, std::vector<std::string>::const_iterator end)
{
    std::vector<Rule> rules;
    rules.reserve(end - begin);

    for (auto it = begin; it != end; ++it) {
        const auto parts = aoc::split(*it, "|");
        assert(parts.size() == 2);
        rules.emplace_back(std::stoi(parts[0]), std::stoi(parts[1]));
    }

    return rules;
}

/**
 * Given lines, parse the updates.
 * @param begin Iterator to start of vector of lines.
 * @param end Iterator to end of vector of lines.
 */
std::vector<Update> get_updates(
    std::vector<std::string>::const_iterator begin, std::vector<std::string>::const_iterator end)
{
    std::vector<Update> updates;
    updates.reserve(end - begin);

    for (auto it = begin; it != end; ++it) {
        const auto parts = aoc::split(*it, ",");
        assert(parts.size() % 2 == 1);
        updates.emplace_back(aoc::stoi(parts));
    }

    return updates;
}

std::pair<std::vector<Rule>, std::vector<Update>> get_rules_and_updates(const char* filename)
{
    const auto lines = aoc::read_lines(filename);

    // find the empty line, which separates the rules from the updates
    const auto split = std::find(lines.begin(), lines.end(), "");
    assert(split != lines.end());

    const auto rules = get_rules(lines.begin(), split);
    const auto updates = get_updates(split + 1, lines.end());

    return std::make_pair(std::move(rules), std::move(updates));
}

int main(int argc, char** argv)
{
    assert(argc == 2);
    const char* filename = argv[1];

    get_rules_and_updates(filename);

    return 0;
}
