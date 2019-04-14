// -*- coding: utf-8 -*-
#define CATCH_CONFIG_MAIN

// #include <boost/graph/adjacency_list.hpp>
// #include <boost/graph/graph_traits.hpp>
#include <catch.hpp>
#include <netoptim/min_cycle_ratio.hpp>
#include <netoptim/neg_cycle.hpp> // import negCycleFinder
#include <py2cpp/nx2bgl.hpp>
#include <utility> // for std::pair
#include <xnetwork/classes/digraphs.hpp>

// using graph_t = boost::adjacency_list<
//     boost::listS, boost::vecS, boost::directedS, boost::no_property,
//     boost::property<boost::edge_weight_t, int,
//                     boost::property<boost::edge_index_t, int>>>;
// using Vertex = boost::graph_traits<graph_t>::vertex_descriptor;
// using Edge_it = boost::graph_traits<graph_t>::edge_iterator;

// auto get_weight(const graph_t &G, const Edge_it &e) {
//     auto weightmap = boost::get(boost::edge_weight_t(), G);
//     return weightmap[*e];
//     //auto u = boost::source(e, G);
//     //auto v = boost::target(e, G);
//     //return G[u][v].get("weight", 1);
// }

// using graph_t = xn::DiGraphS;

static auto create_test_case1() {
    using Edge = std::pair<int, int>;
    int num_nodes = 5;
    enum nodes { A, B, C, D, E };
    // char name[] = "ABCDE";
    static Edge edge_array[] = {Edge(A, B), Edge(B, C), Edge(C, D), Edge(D, E),
                                Edge(E, A)};
    int weights[] = {-5, 1, 1, 1, 1};
    // int num_arcs = sizeof(edge_array) / sizeof(Edge);
    auto g = xn::DiGraphS(py::range<int>(num_nodes), py::range<int>(num_nodes));
    g.add_edge_from(edge_array, weights);
    return g;
}

static auto create_test_case2() {
    using Edge = std::pair<int, int>;
    int num_nodes = 5;
    enum nodes { A, B, C, D, E };
    // char name[] = "ABCDE";
    static Edge edge_array[] = {Edge(A, B), Edge(B, C), Edge(C, D), Edge(D, E),
                                Edge(E, A)};
    int weights[] = {2, 1, 1, 1, 1};
    // int num_arcs = sizeof(edge_array) / sizeof(Edge);
    auto g = xn::DiGraphS(py::range<int>(num_nodes), py::range<int>(num_nodes));
    g.add_edge_from(edge_array, weights);
    return g;
}

static auto create_test_case_timing() {
    using Edge = std::pair<int, int>;
    int num_nodes = 3;
    enum nodes { A, B, C };
    // char name[] = "ABCDE";
    static Edge edge_array[] = {Edge(A, B), Edge(B, A), Edge(B, C), Edge(C, B),
                                Edge(B, C), Edge(C, B), Edge(C, A), Edge(A, C)};
    int weights[] = {7, 0, 3, 1, 6, 4, 2, 5};
    // int num_arcs = sizeof(edge_array) / sizeof(Edge);
    auto g = xn::DiGraphS(py::range<int>(num_nodes), py::range<int>(num_nodes));
    g.add_edge_from(edge_array, weights);
    return g;
}

template <typename Graph>
auto do_case(const Graph &G) -> bool {
    using edge_t = decltype(*(std::begin(G.edges())));

    auto get_weight = [](const Graph &G,
                         const edge_t &e) -> int {
        auto [u, v] = G.end_points(e);
        return G[u][v];
    };

    auto N = negCycleFinder(G, get_weight);
    auto cycle = N.find_neg_cycle();
    return !cycle.empty();
}

TEST_CASE("Test Negative Cycle", "[test_neg_cycle]") {
    auto G = create_test_case1();
    auto hasNeg = do_case(G);
    CHECK(hasNeg);

    // G = xn::path_graph(5, create_using=xn::DiGraph());
    // hasNeg = do_case(G);
    // CHECK(!hasNeg);
}

TEST_CASE("Test No Negative Cycle", "[test_neg_cycle]") {
    auto G = create_test_case2();
    auto hasNeg = do_case(G);
    CHECK(!hasNeg);
}

TEST_CASE("Test Timing Graph", "[test_neg_cycle]") {
    auto G = create_test_case_timing();
    auto hasNeg = do_case(G);
    CHECK(!hasNeg);
}
