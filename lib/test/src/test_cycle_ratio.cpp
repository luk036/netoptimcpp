// -*- coding: utf-8 -*-
#include <catch.hpp>
#include <netoptim/min_cycle_ratio.hpp>
#include <py2cpp/nx2bgl.hpp>
#include <utility> // for std::pair
#include <xnetwork/classes/digraphs.hpp>
#include <array>
#include <py2cpp/fractions.hpp>        // import Fraction
#include <utility> // for std::pair
#include <vector>
// from fractions import Fraction

static auto create_test_case1()
{
    using Edge = std::pair<int, int>;
    auto num_nodes = 5;
    enum nodes { A, B, C, D, E };
    auto edges = std::array{Edge(A, B), Edge(B, C), Edge(C, D), Edge(D, E),
                            Edge(E, A)};
    auto indices = std::array{0, 1, 2, 3, 4};
    auto g = xn::DiGraphS(py::range<int>(num_nodes));
    g.add_edges_from(edges, indices);
    return g;
}

static auto create_test_case_timing()
{
    using Edge = std::pair<int, int>;
    auto num_nodes = 3;
    enum nodes { A, B, C };
    // char name[] = "ABCDE";
    auto edges = std::array{Edge(A, B), Edge(B, A), Edge(B, C), Edge(C, B),
                            Edge(C, A), Edge(A, C)};
    // make sure no parallel edges!!!

    auto indices = std::array{0, 1, 2, 3, 4, 5};
    auto g = xn::DiGraphS(py::range<int>(num_nodes));
    g.add_edges_from(edges, indices);
    return g;
}

TEST_CASE("Test Cycle Ratio", "[test_cycle_ratio]")
{
    using graph_t = decltype(create_test_case1());
    auto G = create_test_case1();
    auto cost = std::array{5, 1, 1, 1, 1};

    auto get_cost = [&](const graph_t &G,
                        const auto &e) -> int {
        auto [u, v] = e;
        return cost[G[u][v]];
    };
    auto get_time = [&](const graph_t &,
                        const auto &) -> int {
        return 1;
    };

    auto [r, c] = min_cycle_ratio(G, get_cost, get_time, fun::Fraction<int>{});
    CHECK(!c.empty());
    CHECK(c.size() == 5);
    CHECK(r == fun::Fraction<int>(9, 5));
    // print(r);
    // print(c);
    // print(dist.items());
}

TEST_CASE("Test Cycle Ratio of Timing Graph", "[test_cycle_ratio]")
{
    using graph_t = decltype(create_test_case_timing());
    auto G = create_test_case_timing();
    auto cost = std::array{7, -1, 3, 0, 2, 4};

    auto get_cost = [&](const graph_t &G,
                        const auto &e) -> int {
        auto [u, v] = e;
        return cost[G[u][v]];
    };
    auto get_time = [&](const graph_t &,
                        const auto &) -> int {
        return 1;
    };

    auto [r, c] = min_cycle_ratio(G, get_cost, get_time, fun::Fraction<int>{});
    CHECK(!c.empty());
    CHECK(r == fun::Fraction<int>(3, 2));
    CHECK(c.size() == 2);
    // print(r);
    // print(c);
    // print(dist.items());
}
