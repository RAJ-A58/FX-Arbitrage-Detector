# FX Arbitrage Detector

A high-performance, low-latency C++ engine designed to identify risk-free arbitrage opportunities in foreign exchange (FX) markets. The system models currency exchange rates as a directed graph and efficiently detects market inefficiencies (arbitrage loops) where a sequence of trades results in a net positive return.

## Algorithm & Architecture

This project utilizes the **Bellman-Ford algorithm** for negative-weight cycle detection. 

To map the financial problem into a graph theory domain with real-world **Bid/Ask spreads and Transaction Fees**:
1. **Vertices** represent currencies.
2. **Edges** represent the directed exchange flow. Each quote (Base/Quote) creates two directed edges. A proportional **transaction fee** (`fee_percentage`) is deducted from the rate before applying the logarithm:
   - Selling Base for Quote uses the **Bid** price. Weight = `-log(Bid * (1 - fee_percentage))`.
   - Buying Base with Quote uses the **Ask** price. Weight = `-log((1 / Ask) * (1 - fee_percentage))`.
3. **Edge Weights** are transformed using logarithms to convert multiplicative rates into additive paths.

By doing this transformation, finding an arbitrage opportunity is mathematically equivalent to finding a negative-weight cycle in the graph. The inclusion of spreads and fees ensures that detected loops are genuinely profitable, overcoming all market friction.

### Algorithmic Complexity
- **Time Complexity:** $\mathcal{O}(V \times E)$ where $V$ is the number of currencies and $E$ is the number of exchange rate pairs.
- **Space Complexity:** $\mathcal{O}(V + E)$ for maintaining the adjacency list representation, distance arrays, and parent tracking.

## Scale & Performance Metrics

Designed with high-frequency trading (HFT) principles, the engine is optimized for extremely low latency.

- **Current Dataset:** The `rates.csv` file currently models a micro-market of **10 currency pairs** across 4 major fiat currencies (USD, EUR, GBP, JPY).
- **Execution Speed:** On a standard workstation, processing the 10-pair graph and extracting the optimal trading path executes in **sub-microsecond (< 1 µs)** latency (effectively 0 nanoseconds on standard high-resolution clocks).
- **Optimization:** Compiled with C++17 and `-O3` optimization flags to ensure minimal overhead, making it well-suited for scaling up to hundreds of real-time market feeds.

## Build and Execute

The project uses CMake for cross-platform builds.

```bash
mkdir build
cd build
cmake ..
cmake --build .
./detector
```

*Alternatively, compile directly with g++:*
```bash
g++ -std=c++17 -O3 -Wall -Wextra -I./include src/main.cpp src/ArbitrageDetector.cpp -o detector
./detector
```

## Example Output
```
Arbitrage Opportunity Detected!
Optimal Trading Path: JPY -> USD -> GBP -> JPY
Execution time: < 1 microseconds
```
