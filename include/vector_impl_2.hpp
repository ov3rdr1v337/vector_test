#pragma once

#include <cstring>
#include <cstdint>
#include <cstdlib>

namespace container
{
    template
        <
            class t_arg
        >
    class vector_impl_2_t
    {
    public:
        using type_t    = vector_impl_2_t
                            <
                                t_arg
                            >;
        
        vector_impl_2_t() noexcept
        {
            m_begin     = static_cast<t_arg*> ( malloc( 32u * sizeof( t_arg ) ) );
            m_end       = m_begin;

            m_m_end     = m_begin + 32u;
        }

        vector_impl_2_t( const type_t&  clone ) noexcept 
        {

        }

        vector_impl_2_t(       type_t&& move  ) noexcept 
        {
            m_begin = move.m_begin;
        }

        type_t& operator=( const type_t&  clone ) noexcept
        {

        }

        type_t& operator=(       type_t&& move  ) noexcept
        {
            m_begin = move.m_begin;
        }

       ~vector_impl_2_t()
        {
            clear();
        }

        t_arg  *begin()
        {
            return m_begin;
        }

        t_arg  *end()
        {
            return m_end;
        }

        t_arg  *begin() const
        {
            return m_begin;
        }

        t_arg  *end()   const
        {
            return m_end;
        }

        size_t  size() const
        {
            return end() - begin();
        }

        void    clear()
        {
            free( m_begin );
        }

        void    push( const t_arg& element )
        {
            if ( m_end == m_m_end )
            {
                const size_t old_size = reinterpret_cast<uint8_t*>( m_end ) - 
                                        reinterpret_cast<uint8_t*>( m_begin );

                const size_t new_size = old_size << 2u;

                uint8_t *m_begin_new  = static_cast<uint8_t*> ( malloc( new_size ) );

                m_end                 = reinterpret_cast<t_arg*>( m_begin_new + old_size );
                m_m_end               = reinterpret_cast<t_arg*>( m_begin_new + new_size );

                std::memcpy
                        ( 
                            m_begin_new , 
                            m_begin     ,
                            old_size
                        );

                clear();

                m_begin     = reinterpret_cast<t_arg*>( m_begin_new );
            }

            m_end++[0] = element;
        }
        
    private:
        t_arg   *m_begin;
        t_arg   *m_end;
        t_arg   *m_m_end;
    }; 
};