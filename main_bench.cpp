#include <vector>
#include <benchmark/benchmark.h>

#include "include/vector_impl_2.hpp"

#include "include/type_traits/type_traits.hpp"

void test_vector_impl( benchmark::State& states ) 
{
    for ( auto state : states )
    {
        const size_t size = states.range( 0 );

        container::vector_t<size_t> vector_impl;
        
        for ( size_t i = 0u; i < size; ++i )
            vector_impl.push_back( i );
    }
}
BENCHMARK(test_vector_impl)->Range( 0, 1 << 30 );

void test_vector_stl( benchmark::State& states ) 
{
    for ( auto state : states )
    {
        const size_t size = states.range( 0 );

        std::vector<size_t> vector_stl;
        
        vector_stl.reserve( 32u );

        for ( size_t i = 0u; i < size; ++i )
            vector_stl.push_back( i );
    }
}
BENCHMARK(test_vector_stl)->Range( 0, 1 << 30 );

BENCHMARK_MAIN();
