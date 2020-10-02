#pragma once
#include <array>
#include <xnetwork/classes/digraphs.hpp>


template <typename Container>
inline auto create_test_case1(const Container& weights)
{
    using Edge = std::pair<int, int>;
    constexpr int num_nodes = 5;
    enum nodes
    {
        A,
        B,
        C,
        D,
        E
    };
    const auto edges = std::array<Edge, 5> {
        Edge {A, B}, Edge {B, C}, Edge {C, D}, Edge {D, E}, Edge {E, A}};
    // constexpr auto weights = std::array<int, 5> {-5, 1, 1, 1, 1};
    auto G = xn::SimpleDiGraphS {py::range<int>(num_nodes)};
    G.add_edges_from(edges, weights);
    return G;
}

template <typename Container>
inline auto create_test_case2(const Container& weights)
{
    using Edge = std::pair<int, int>;
    constexpr auto num_nodes = 3;
    enum nodes
    {
        A,
        B,
        C
    };
    const auto edges = std::array<Edge, 6> {Edge {A, B}, Edge {B, A}, Edge {B, C},
        Edge {C, B}, Edge {C, A}, Edge {A, C}};
    auto G = xn::SimpleDiGraphS {py::range<int>(num_nodes)};
    G.add_edges_from(edges, weights);
    return G;
}

template <typename Container>
inline auto create_test_case_timing(const Container& weights)
{
    using Edge = std::pair<int, int>;
    constexpr auto num_nodes = 3;
    enum nodes
    {
        A,
        B,
        C
    };
    const auto edges = std::array<Edge, 8> {Edge {A, B}, Edge {B, A}, Edge {B, C},
        Edge {C, B}, Edge {B, C}, Edge {C, B}, Edge {C, A}, Edge {A, C}};
    auto G = xn::SimpleDiGraphS {py::range<int>(num_nodes)};
    G.add_edges_from(edges, weights);
    return G;
}