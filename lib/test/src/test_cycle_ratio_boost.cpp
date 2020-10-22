// -*- coding: utf-8 -*-
#include <doctest.h>
#include <netoptim/min_cycle_ratio.hpp> // import min_cycle_ratio, set_default
#include <netoptim/test_cases2_boost.hpp>
#include <py2cpp/fractions.hpp> // import Fraction
#include <vector>
// from fractions import Fraction

TEST_CASE("Test Cycle Ratio (boost)")
{
    using EdgeIndexMap =
        typename boost::property_map<graph_t, boost::edge_id_tag_t>::type;
    using IterMap = boost::iterator_property_map<int*, EdgeIndexMap, int, int&>;

    size_t indices[] = {0, 1, 2, 3, 4};
    auto G = create_test_case1(indices);

    int cost[] = {5, 1, 1, 1, 1};
    EdgeIndexMap edge_id = boost::get(boost::id_tag, G);
    IterMap cost_pa(cost, edge_id);

    auto get_cost = [&](const auto& e) -> int {
        return boost::get(cost_pa, e);
    };
    auto get_time = [&](const auto & /*unused*/) -> int { return 1; };

    auto dist = std::vector<fun::Fraction<int>>(
        G.number_of_nodes(), fun::Fraction<int>(0));
    auto r = fun::Fraction<int>(5);
    const auto c = min_cycle_ratio(G, r, get_cost, get_time, dist);
    CHECK(!c.empty());
    CHECK(c.size() == 5);
    CHECK(r == fun::Fraction<int>(9, 5));
    // print(r);
    // print(c);
    // print(dist.items());
}

TEST_CASE("Test Cycle Ratio of Timing Graph (boost)")
{
    using EdgeIndexMap =
        typename boost::property_map<graph_t, boost::edge_id_tag_t>::type;
    using IterMap = boost::iterator_property_map<int*, EdgeIndexMap, int, int&>;

    size_t indices[] = {0, 1, 2, 3, 4, 5, 6, 7};
    auto G = create_test_case_timing(indices);

    int cost[] = {7, -1, 5, 4, 3, 0, 2, 4};
    EdgeIndexMap edge_id = boost::get(boost::id_tag, G);
    IterMap cost_pa(cost, edge_id);

    const auto get_cost = [&](const auto& e) -> int {
        return boost::get(cost_pa, e);
    };
    const auto get_time = [&](const auto & /*e*/) -> int { return 1; };

    auto dist = std::vector<fun::Fraction<int>>(
        G.number_of_nodes(), fun::Fraction<int>(0));
    auto r = fun::Fraction<int>(7);
    const auto c = min_cycle_ratio(G, r, get_cost, get_time, dist);
    CHECK(!c.empty());
    CHECK(r == fun::Fraction<int>(1, 1));
    CHECK(c.size() == 3);
    // print(r);
    // print(c);
    // print(dist.items());
}
