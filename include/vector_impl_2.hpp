#pragma once

template
    <
        class t_arg,
        class t_alloc
    >
class vector_t
{
pivate:
    t_arg   *m_begin;

public:
    vector_t() noexcept
    {

    }

    vector_t( const vector_t<t_arg, t_alloc>&  clone ) noexcept 
    {

    }

    vector_t( const vector_t<t_arg, t_alloc>&& move  ) noexcept 
    {

    }

    vector_t<t_arg, t_alloc>& operator=( const vector_t<t_arg, t_alloc>&  clone ) noexcept
    {

    }

    vector_t<t_arg, t_alloc>& operator=( const vector_t<t_arg, t_alloc>&& move  ) noexcept
    {

    }

   ~vector_t()
    {

    }
}; 