#include <algorithm>

#include "common.h"
#include "io.h"


struct Rule {
    int first;
    int second;

    Rule(int first, int second) : first(first), second(second) {}
};

using Update = std::vector<int>;

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

/**
 * Get rules and updates from text file.
 */
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

/**
 * Check that the update satisfies the given rule.
 */
bool check_rule(const Update& update, const Rule& rule)
{
    // if one of the two numbers in `rule` cannot be found, then default to `true`
    const auto rule_first = std::find(update.begin(), update.end(), rule.first);
    if (rule_first == update.end()) {
        return true;
    }

    const auto rule_second = std::find(update.begin(), update.end(), rule.second);
    if (rule_second == update.end()) {
        return true;
    }

    return rule_first < rule_second;
}

/**
 * Check that the update satisfies all given rules.
 */
bool check_rules(const Update& update, const std::vector<Rule>& rules)
{
    for (const auto& rule : rules) {
        if (!check_rule(update, rule)) {
            return false;
        }
    }
    return true;
}

void part1(const std::vector<Update>& updates, const std::vector<Rule>& rules)
{
    int sum_of_middle = 0;

    for (const auto& update : updates) {
        if (check_rules(update, rules)) {
            const int size = update.size();
            sum_of_middle += update[(size - 1) / 2];
        }
    }

    printf("Day 5 Part 1: %d\n", sum_of_middle);
}
int main(int argc, char** argv)
{
    assert(argc == 2);
    const char* filename = argv[1];

    const auto [rules, updates] = get_rules_and_updates(filename);

    part1(updates, rules);

    return 0;
}
