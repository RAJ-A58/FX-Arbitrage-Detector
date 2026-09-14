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

        double fee_percentage;
        int getorAddCurrency(const std::string& currency);

    public:
        ArbitrageDetector(double fee = 0.0) : fee_percentage(fee) {}

        void addQuote(const std::string& base, const std::string& quote, double bid, double ask);        
        void executeSearch();
};