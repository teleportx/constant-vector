#include <benchmark/benchmark.h>
#include <vector>
#include <chrono>
#include "constant_vector.hpp"

const size_t START = 1 << 10, LIMIT = 1ll << 30;
const int WORST_INSERT_ITERATIONS = 100;

static void BM_ConstantVector_TotalInsert(benchmark::State& state) {
    const size_t N = state.range(0);

    for (auto _ : state) {
        constant_vector<int> v;
        for (size_t i = 0; i < N; ++i) {
            v.push_back(i);
        }
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_ConstantVector_TotalInsert)->Range(START, LIMIT)->RangeMultiplier(2);


static void BM_StdVector_TotalInsert(benchmark::State& state) {
    const size_t N = state.range(0);

    for (auto _ : state) {
        std::vector<int> v;
        v.reserve(N);
        for (size_t i = 0; i < N; ++i) {
            v.push_back(i);
        }
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_StdVector_TotalInsert)->Range(START, LIMIT)->RangeMultiplier(2);

static void BM_ConstantVector_WorstInsert(benchmark::State& state) {
    size_t cap = state.range(0);

    for (auto _ : state) {
        state.PauseTiming();
        constant_vector<int> v;
        for (size_t i = 0; i < cap; ++i)
            v.push_back(i);

        benchmark::DoNotOptimize(v);
        state.ResumeTiming();
        v.push_back(123456);
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_ConstantVector_WorstInsert)->Range(START, LIMIT)->RangeMultiplier(2)->Iterations(WORST_INSERT_ITERATIONS);


static void BM_StdVector_WorstInsert(benchmark::State& state) {
    size_t cap = state.range(0);

    for (auto _ : state) {
        state.PauseTiming();
        std::vector<int> v;
        v.reserve(cap);
        v.resize(cap);

        benchmark::DoNotOptimize(v);
        state.ResumeTiming();
        v.push_back(123456);
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_StdVector_WorstInsert)->Range(START, LIMIT)->RangeMultiplier(2)->Iterations(WORST_INSERT_ITERATIONS);

BENCHMARK_MAIN();
