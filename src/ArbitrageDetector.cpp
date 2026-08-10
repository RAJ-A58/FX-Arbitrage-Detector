#include "ArbitrageDetector.hpp"
#include <cmath>
#include <iostream>
#include <algorithm>

int ArbitrageDetector::getorAddCurrency(const std::string& currency) {
    auto it = currToInt.find(currency);
    if (it != currToInt.end()) {
        return it->second;
    }
    
    int newId = intToCurr.size();
    currToInt[currency] = newId;
    intToCurr.push_back(currency);
    return newId;
}

void ArbitrageDetector::addExchangeRate(const std::string& source, const std::string& dest, double rate) {
    int u = getorAddCurrency(source);
    int v = getorAddCurrency(dest);
    
    double weight = -std::log(rate);
    
    edges.push_back({u, v, weight});
}

void ArbitrageDetector::executeSearch() {
    int V = intToCurr.size();
    if (V == 0) return;

    std::vector<double> distance(V, 0.0);
    std::vector<int> parent(V, -1);

    // V-1 Iterations to find standard shortest paths
    for (int i = 0; i < V - 1; ++i) {
        for (const auto& e : edges) {
            if (distance[e.source] + e.weight < distance[e.dest]) {
                distance[e.dest] = distance[e.source] + e.weight;
                parent[e.dest] = e.source;
            }
        }
    }

    // V-th iteration for Negative Cycle (Arbitrage) Detection
    int cycle_start = -1;
    for (const auto& e : edges) {
        // We use 1e-9 instead of just < to avoid floating point precision errors
        if (distance[e.source] + e.weight < distance[e.dest] - 1e-9) {
            cycle_start = e.dest;
            break;
        }
    }

    if (cycle_start != -1) {
        std::cout << "Arbitrage Opportunity Detected!\n";
        
        int curr = cycle_start;
        // Walk backwards V times to guarantee we are inside the cycle
        for (int i = 0; i < V; ++i) {
            curr = parent[curr];
        }

        std::vector<int> cycle;
        for (int v = curr;; v = parent[v]) {
            cycle.push_back(v);
            if (v == curr && cycle.size() > 1) {
                break;
            }
        }
        
        // The parent array builds the path backwards, so we reverse it
        std::reverse(cycle.begin(), cycle.end());
        
        std::cout << "Optimal Trading Path: ";
        for (size_t i = 0; i < cycle.size(); ++i) {
            std::cout << intToCurr[cycle[i]];
            if (i < cycle.size() - 1) std::cout << " -> ";
        }
        std::cout << "\n";
    } else {
        std::cout << "No arbitrage opportunities exist.\n";
    }
}
