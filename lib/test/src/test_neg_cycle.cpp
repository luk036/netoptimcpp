// -*- coding: utf-8 -*-
#define CATCH_CONFIG_MAIN

#include <array>
#include <catch.hpp>
#include <netoptim/neg_cycle.hpp> // import negCycleFinder
#include <xnetwork/classes/digraphs.hpp>

/*!
 * @brief Create a test case1 object
 *
 * @return auto
 */
static auto create_test_case1()
{
    using Edge = std::pair<int, int>;
    auto num_nodes = 5;
    enum nodes
    {
        A,
        B,
        C,
        D,
        E
    };
    auto edges = std::array<Edge, 5> {
        Edge(A, B), Edge(B, C), Edge(C, D), Edge(D, E), Edge(E, A)};
    auto weights = std::array<int, 5> {-5, 1, 1, 1, 1};
    auto g = xn::DiGraphS(py::range<int>(num_nodes));
    g.add_edges_from(edges, weights);
    return g;
}

/*!
 * @brief Create a test case2 object
 *
 * @return auto
 */
static auto create_test_case2()
{
    using Edge = std::pair<int, int>;
    auto num_nodes = 5;
    enum nodes
    {
        A,
        B,
        C,
        D,
        E
    };
    auto edges = std::array<Edge, 5> {
        Edge(A, B), Edge(B, C), Edge(C, D), Edge(D, E), Edge(E, A)};
    auto weights = std::array<int, 5> {2, 1, 1, 1, 1};
    auto g = xn::DiGraphS(py::range<int>(num_nodes));
    g.add_edges_from(edges, weights);
    return g;
}

/*!
 * @brief Create a test case timing object
 *
 * @return auto
 */
static auto create_test_case_timing()
{
    using Edge = std::pair<int, int>;
    auto num_nodes = 3;
    enum nodes
    {
        A,
        B,
        C
    };
    auto edges = std::array<Edge, 8> {Edge(A, B), Edge(B, A), Edge(B, C),
        Edge(C, B), Edge(B, C), Edge(C, B), Edge(C, A), Edge(A, C)};
    auto weights = std::array<int, 8> {7, 0, 3, 1, 6, 4, 2, 5};
    auto g = xn::DiGraphS(py::range<int>(num_nodes));
    g.add_edges_from(edges, weights);
    return g;
}

/*!
 * @brief
 *
 * @tparam Graph
 * @param G
 * @return true
 * @return false
 */
template <typename Graph>
auto do_case(const Graph& G) -> bool
{
    auto get_weight = [](const Graph& G2, const auto& e) -> int {
        auto [u, v] = G2.end_points(e);
        return G2[u][v];
    };

    auto N = negCycleFinder(G, get_weight);
    auto cycle = N.find_neg_cycle();
    return !cycle.empty();
}

/*!
 * @brief
 *
 */
TEST_CASE("Test Negative Cycle", "[test_neg_cycle]")
{
    auto G = create_test_case1();
    auto hasNeg = do_case(G);
    CHECK(hasNeg);
}

/*!
 * @brief
 *
 */
TEST_CASE("Test No Negative Cycle", "[test_neg_cycle]")
{
    auto G = create_test_case2();
    auto hasNeg = do_case(G);
    CHECK(!hasNeg);
}

/*!
 * @brief
 *
 */
TEST_CASE("Test Timing Graph", "[test_neg_cycle]")
{
    auto G = create_test_case_timing();
    auto hasNeg = do_case(G);
    CHECK(!hasNeg);
}
