#include <algorithm>
#include <numeric>

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
std::vector<Rule> parse_rules(
    std::vector<std::string>::const_iterator begin, std::vector<std::string>::const_iterator end)
{
    std::vector<Rule> rules;
    rules.reserve(end - begin);

    for (auto it = begin; it != end; ++it) {
        const auto parts = aoc::split(*it, "|");
        assert(parts.size() == 2);  // rule must contain two integers
        rules.emplace_back(std::stoi(parts[0]), std::stoi(parts[1]));
    }

    return rules;
}

/**
 * Given lines, parse the updates.
 * @param begin Iterator to start of vector of lines.
 * @param end Iterator to end of vector of lines.
 */
std::vector<Update> parse_updates(
    std::vector<std::string>::const_iterator begin, std::vector<std::string>::const_iterator end)
{
    std::vector<Update> updates;
    updates.reserve(end - begin);

    for (auto it = begin; it != end; ++it) {
        const auto parts = aoc::split(*it, ",");
        assert(parts.size() % 2 == 1);  // update should have odd number of pages
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

    const auto rules = parse_rules(lines.begin(), split);
    const auto updates = parse_updates(split + 1, lines.end());

    return std::make_pair(std::move(rules), std::move(updates));
}

// ----------------------------------------------------------------------------

/**
 * Check that the update satisfies the given rule.
 */
bool check_rule(const Update& update, const Rule& rule)
{
    const auto rule_first_ptr = std::find(update.begin(), update.end(), rule.first);
    const auto rule_second_ptr = std::find(update.begin(), update.end(), rule.second);

    // if either number cannot be found, then return `true` since the rule is vacuously satisfied
    if (rule_first_ptr == update.end() || rule_second_ptr == update.end()) {
        return true;
    }

    // check rule is satisfied
    return rule_first_ptr < rule_second_ptr;
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

// ----------------------------------------------------------------------------

Update order_update(const Update& update, const std::vector<Rule>& rules)
{
    // First, we encode the relevant rules as a graph: the relation A < B is
    // encoded as a directed edge A -> B. We represent this graph as an
    // adjacency matrix, where M[A][B] is non-zero iff A -> B is an edge in the
    // graph.

    std::vector<std::vector<bool>> rule_graph;
    {
        // initialize
        rule_graph.reserve(update.size());
        for (int i = 0; i < update.size(); ++i) {
            rule_graph.emplace_back(update.size(), false);
        }

        // fill in edges
        for (const auto& rule : rules) {
            const auto rule_first_ptr = std::find(update.begin(), update.end(), rule.first);
            const auto rule_second_ptr = std::find(update.begin(), update.end(), rule.second);
            if (rule_first_ptr != update.end() && rule_second_ptr != update.end()) {
                const int a = rule_first_ptr - update.begin();
                const int b = rule_second_ptr - update.begin();
                rule_graph[a][b] = true;
            }
        }
    }

    // Second, we find a path in the graph that connects all nodes. Such a path
    // will correspond to the ordered update.

    Update ordered_update;
    {
        // HACK: if we assume the rules are complete, i.e. our graph is a total
        // ordering, then we can find such a path by just sorting the nodes by
        // the number of outgoing edges.

        // list of {num_outgoing_edges, number} pairs
        std::vector<std::pair<int, int>> edge_counts;

        edge_counts.reserve(update.size());
        for (int i = 0; i < update.size(); ++i) {
            const int num_outgoing_edges = std::accumulate(rule_graph[i].begin(), rule_graph[i].end(), 0);
            edge_counts.emplace_back(num_outgoing_edges, update[i]);
        }

        // sort by first key in decreasing order, i.e. largest first key at front
        auto cmp = [](const std::pair<int, int>& x, const std::pair<int, int>& y) -> bool { return x.first > y.first; };
        std::sort(edge_counts.begin(), edge_counts.end(), cmp);

        // check our HACK assumption was correct
        for (int i = 0; i < edge_counts.size(); ++i) {
            assert(edge_counts[i].first == edge_counts.size() - i - 1);
            ordered_update.emplace_back(edge_counts[i].second);
        }
    }

    return ordered_update;
}

void part2(const std::vector<Update>& updates, const std::vector<Rule>& rules)
{
    int sum_of_middle = 0;

    for (const auto& update : updates) {
        if (!check_rules(update, rules)) {
            const auto ordered_update = order_update(update, rules);
            const int size = ordered_update.size();
            sum_of_middle += ordered_update[(size - 1) / 2];
        }
    }

    printf("Day 5 Part 2: %d\n", sum_of_middle);
}

// ----------------------------------------------------------------------------

int main(int argc, char** argv)
{
    assert(argc == 2);
    const char* filename = argv[1];

    const auto [rules, updates] = get_rules_and_updates(filename);

    part1(updates, rules);
    part2(updates, rules);

    return 0;
}
