#pragma once

#include "Edge.hpp"
#include <vector>
#include <string>
#include <unordered_map>

class ArbitrageDetector {
    private:
        std::vector<edge> edges;
        std::unordered_map<std::string,int> currToInt;
        std::vector<std::string> intToCurr;

        int getorAddCurrency(const std::string& currency);

    public:
        ArbitrageDetector() = default;

        void addExchangeRate(const std::string& source, const std::string& dest, double rate);
        
        void executeSearch();
};