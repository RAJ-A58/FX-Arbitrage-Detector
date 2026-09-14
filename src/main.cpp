#include "ArbitrageDetector.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>

int main() {
    // Initialize with a 0.2% trading fee per hop (0.001)
    ArbitrageDetector detector(0.001);
    std::string filename = "data/rates.csv";
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open " << filename << std::endl;
        return 1;
    }

    std::string line;
    // skip header
    std::getline(file, line);

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        std::stringstream ss(line);
        std::string base, quote, bid_str, ask_str;

        if (std::getline(ss, base, ',') &&
            std::getline(ss, quote, ',') &&
            std::getline(ss, bid_str, ',') &&
            std::getline(ss, ask_str, ',')) {
            
            try {
                double bid = std::stod(bid_str);
                double ask = std::stod(ask_str);
                detector.addQuote(base, quote, bid, ask);
            } catch (const std::exception& e) {
                std::cerr << "Error parsing rates: " << bid_str << ", " << ask_str << std::endl;
            }
        }
    }

    auto start_time = std::chrono::high_resolution_clock::now();
    detector.executeSearch();
    auto end_time = std::chrono::high_resolution_clock::now();

    auto duration_us = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
    std::cout << "Execution time: " << duration_us.count() << " nanoseconds\n";

    return 0;
}
