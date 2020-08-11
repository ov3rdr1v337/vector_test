#include "include/vector_impl_2.hpp"

#include <iostream>
#include <vector>

struct A
{
    size_t a = 1337u;

    A() = default;

    A( const A& clone )
    {
        std::cout << 1234 << std::endl;
    }
};

int main()
{
    container::vector_impl_2_t<size_t> vector_impl_2;

    {
        auto begin_it   = vector_impl_2.begin();
        auto end_it     = vector_impl_2.end();

        for( size_t i = 0u; i < 2u; ++i  )
            vector_impl_2.push( 1337u );
    }

    {
        auto begin_it   = vector_impl_2.begin();
        auto end_it     = vector_impl_2.end();

        for( size_t i = 0u; i < 2u; ++i  )
            vector_impl_2.push( 1338u );
    }

    {
        auto begin_it   = vector_impl_2.begin();
        auto end_it     = vector_impl_2.end();

        for( size_t i = 0u; i < 2u; ++i  )
            vector_impl_2.push( 1339u );
    }

    for( auto it : vector_impl_2 )
        std::cout << it << std::endl;

    return 0;
}