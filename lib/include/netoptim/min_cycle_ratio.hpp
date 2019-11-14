// -*- coding: utf-8 -*-
#pragma once

#include "parametric.hpp" // import max_parametric
#include <algorithm>
#include <numeric>
#include <py2cpp/py2cpp.hpp>

/*!
 * @brief minimum cost-to-time cycle ratio problem
 *
 *    max  r
 *    s.t. dist[v] - dist[u] <= cost(u, v) - r * time(u, v)
 *         for all (u, v) : G
 *
 * @tparam Graph
 * @tparam Fn1
 * @tparam Fn2
 * @tparam Container
 * @param G
 * @param get_cost
 * @param get_time
 * @param dist
 * @return auto
 */
template <typename Graph, typename Fn1, typename Fn2, typename Container>
auto min_cycle_ratio(Graph& G, Fn1 get_cost, Fn2 get_time, Container& dist, size_t max_iter=1000)
{
    using edge_t = typename Graph::edge_t;
    using T = typename Container::value_type;

    edge_t e0;
    for (auto e : G.edges())
    {
        e0 = e; // get the first edge (better idea???)
        break;
    }

    // auto& edges = G.edges();
    // auto max_c = *std::max_element(edges.begin(), edges.end(),
    //                 [](const edge_t& e) { return get_cost(G, e); });

    // auto max_cost = *std::max_element(cost.begin(), cost.end());
    // auto min_time = *std::min_element(time.begin(), time.end());
    auto max_cost = get_cost(e0);
    auto min_time = get_time(e0);
    for (auto e : G.edges())
    {
        const auto c = get_cost(e);
        const auto t = get_time(e);
        if (max_cost < c)
            max_cost = c;
        if (min_time > t)
            min_time = t;
    }
    auto r0 = T(max_cost * G.number_of_edges()) / min_time;

    using cost_T = decltype(get_cost(e0));
    using time_T = decltype(get_time(e0));

    auto calc_ratio = [&](auto& C) {
        auto total_cost = cost_T(0);
        auto total_time = time_T(0);
        for (auto e : C)
        {
            total_cost += get_cost(e);
            total_time += get_time(e);
        }
        return T(total_cost) / total_time;
    };

    auto calc_weight = [&](T r, const auto& e) {
        return get_cost(e) - r * get_time(e);
    };
    return max_parametric(G, r0, calc_weight, calc_ratio, dist, max_iter);
}
