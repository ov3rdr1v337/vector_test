#pragma once

#include <cstring>
#include <cstdint>
#include <cstdlib>

#include "type_traits/helper_traits.hpp"
#include "type_traits/type_properties.hpp"

namespace container
{
    template
        <
            class t_arg
        >
    class vector_t
    {
        static constexpr size_t grow_constant      =   2u;

    public:
        using type_t    = vector_t
                                <
                                    t_arg
                                >;
        
        vector_t() noexcept
        {
            m_begin     = static_cast<t_arg*> ( malloc( 32u * sizeof( t_arg ) ) );
            m_end       = m_begin;

            m_m_end     = m_begin + 32u;
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

        template
            <
                class u_arg = t_arg
            >
        traits::enable_if
            <
                traits::is_trivially_copyable<u_arg>::value, 
                void
            > ::type
        push_back( const t_arg& element )
        {
            if ( m_end == m_m_end )
            {
                const size_t old_size = reinterpret_cast<uint8_t*>( m_end ) - 
                                        reinterpret_cast<uint8_t*>( m_begin );

                const size_t new_size = old_size << grow_constant;

                uint8_t *m_begin_new  = reinterpret_cast<uint8_t*>( malloc( new_size ) );

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

            std::memcpy( m_end++, &element, sizeof( t_arg ) );
        }

        template
            <
                class u_arg = t_arg
            >
        traits::enable_if
            <
               !traits::is_trivially_copyable<u_arg>::value, 
                void
            > ::type
        push_back( const t_arg& element )
        {

        }

        // traits::enable_if
        //     <
        //         traits::is_trivially_copyable<t_arg>::value, 
        //         void
        //     > ::type
        // push( const t_arg& element )
        // {

        // }

    private:
        t_arg   *m_begin;
        t_arg   *m_end;
        t_arg   *m_m_end;
    }; 
};