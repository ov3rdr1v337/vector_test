#include <vector>
#include <benchmark/benchmark.h>

#include "include/vector_impl_1.hpp"
#include "include/vector_impl_2.hpp"

void test_vector_impl_1( benchmark::State& states ) 
{
    for ( auto state : states )
    {
        const size_t size = states.range( 0 );

        container::vector_impl_1_t<size_t> vector_impl_1;
        
        for ( size_t i = 0u; i < size; ++i )
            vector_impl_1.push( i );
    }
}
BENCHMARK(test_vector_impl_1)->Range( 0, 1 << 30 );

void test_vector_impl_2( benchmark::State& states ) 
{
    for ( auto state : states )
    {
        const size_t size = states.range( 0 );

        container::vector_impl_2_t<size_t> vector_impl_2;
        
        for ( size_t i = 0u; i < size; ++i )
            vector_impl_2.push( i );
    }
}
BENCHMARK(test_vector_impl_2)->Range( 0, 1 << 30 );

void test_vector_stl( benchmark::State& states ) 
{
    for ( auto state : states )
    {
        const size_t size = states.range( 0 );

        std::vector<size_t> vector_stl;
        
        for ( size_t i = 0u; i < size; ++i )
            vector_stl.push_back( i );
    }
}
BENCHMARK(test_vector_stl)->Range( 0, 1 << 30 );

BENCHMARK_MAIN();
