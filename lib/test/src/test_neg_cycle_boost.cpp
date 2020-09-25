// -*- coding: utf-8 -*-
#include <doctest.h>
// #include <netoptim/min_cycle_ratio.hpp>
#include <netoptim/neg_cycle.hpp> // import negCycleFinder
#include <netoptim/test_cases_boost.hpp>

auto do_case(const xn::grAdaptor<graph_t>& G) -> bool
{
    using edge_t = decltype(*(std::begin(G.edges())));

    const auto get_weight = [&](const edge_t& e) -> int {
        return boost::get(boost::edge_weight, G)[e];
    };

    auto dist = std::vector<int>(G.number_of_nodes(), 0);
    auto N = negCycleFinder<xn::grAdaptor<graph_t>> {G};
    const auto cycle = N.find_neg_cycle(dist, get_weight);
    return !cycle.empty();
}

auto do_case_float(const xn::grAdaptor<graph_t>& G) -> bool
{
    using edge_t = decltype(*(std::begin(G.edges())));

    const auto get_weight = [&](const edge_t& e) -> double {
        return boost::get(boost::edge_weight, G)[e];
    };

    auto dist = std::vector<double>(G.number_of_nodes(), 0.0);
    auto N = negCycleFinder<xn::grAdaptor<graph_t>> {G};
    const auto cycle = N.find_neg_cycle(dist, get_weight);
    return !cycle.empty();
}

TEST_CASE("Test Negative Cycle (boost)")
{
    int weights[] = {-5, 1, 1, 1, 1};
    const auto G = create_test_case1(weights);
    const auto hasNeg = do_case(G);
    CHECK(hasNeg);
}

TEST_CASE("Test No Negative Cycle (boost)")
{
    int weights[] = {2, 1, 1, 1, 1};
    const auto G = create_test_case1(weights);
    const auto hasNeg = do_case(G);
    CHECK(!hasNeg);
}

TEST_CASE("Test Timing Graph (boost)")
{
    int weights[] = {7, 0, 3, 1, 6, 4, 2, 5};
    const auto G = create_test_case_timing(weights);
    const auto hasNeg = do_case(G);
    CHECK(!hasNeg);
}

TEST_CASE("Test Timing Graph 2 (boost)")
{
    int weights[] = {3, -4, -1, -3, 2, 0, -2, 1};
    const auto G = create_test_case_timing(weights);
    const auto hasNeg = do_case(G);
    CHECK(hasNeg);
}

TEST_CASE("Test Timing Graph float (boost)")
{
    int weights[] = {7, 0, 3, 1, 6, 4, 2, 5};
    const auto G = create_test_case_timing(weights);
    const auto hasNeg = do_case_float(G);
    CHECK(!hasNeg);
}

TEST_CASE("Test Timing Graph 2 (boost)")
{
    int weights[] = {3, -4, -1, -3, 2, 0, -2, 1};
    const auto G = create_test_case_timing(weights);
    const auto hasNeg = do_case_float(G);
    CHECK(hasNeg);
}
