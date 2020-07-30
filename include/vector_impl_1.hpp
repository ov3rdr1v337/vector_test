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
    class vector_t
    {
        static constexpr size_t     header_size = ( sizeof( t_arg* ) << 1u );

    public:
        using type_t    = vector_t
                            <
                                t_arg
                            >;
        
        vector_t() noexcept
        {
            t_arg  **mem      = reinterpret_cast<t_arg**> ( malloc( 4u * sizeof( t_arg ) + header_size ) );
            uint8_t *temp_mem = reinterpret_cast<uint8_t*>( mem ) + header_size;

            mem[0u]     = reinterpret_cast<t_arg* >( temp_mem + 4u * sizeof( t_arg ) );
            mem[1u]     = reinterpret_cast<t_arg* >( temp_mem );
            m_begin     = reinterpret_cast<t_arg* >( temp_mem );
        }

        vector_t( const type_t&  clone ) noexcept 
        {

        }

        vector_t(       type_t&& move  ) noexcept 
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

       ~vector_t()
        {
            clear();
        }

        t_arg  *begin()
        {
            return reinterpret_cast<t_arg* >( m_begin );
        }

        t_arg  *end()
        {
            return reinterpret_cast<t_arg**>( m_begin )[-1];
        }

        t_arg  *begin() const
        {
            return reinterpret_cast<t_arg* >( m_begin );
        }

        t_arg  *end()   const
        {
            return reinterpret_cast<t_arg**>( m_begin )[-1];
        }

        size_t  size() const
        {
            return end() - begin();
        }

        void    clear()
        {
            free( reinterpret_cast<t_arg**>( m_begin ) - 2u );
        }

        void    push( const t_arg& element )
        {
            if ( reinterpret_cast<t_arg**>( m_begin )[-1] == reinterpret_cast<t_arg**>( m_begin )[-2] )
            {
                const size_t old_size = reinterpret_cast<uint8_t**>( m_begin )[-1] - 
                                        reinterpret_cast<uint8_t* >( m_begin );

                const size_t new_size = old_size << 1u;

                t_arg  **mem        = reinterpret_cast<t_arg** >( malloc( new_size + header_size ) );
                uint8_t *temp_mem   = reinterpret_cast<uint8_t*>( mem ) + header_size;

                mem[0u]     = reinterpret_cast<t_arg* >( temp_mem + new_size );
                mem[1u]     = reinterpret_cast<t_arg* >( temp_mem + old_size );

                std::memcpy
                        ( 
                            mem + 2u, 
                            m_begin ,
                            old_size + header_size
                        );                

                clear();

                m_begin     = reinterpret_cast<t_arg* >( temp_mem );                
            }

            reinterpret_cast<t_arg**>( m_begin )[-1]++[0] = element;
        }
        
    private:
        t_arg   *m_begin;
    }; 
};