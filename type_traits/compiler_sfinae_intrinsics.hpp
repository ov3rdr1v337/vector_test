#pragma once


namespace traits
{
#ifdef __GNUC__
    #define COMPILER_INTRINS__IS_ENUM( TArg )                       __is_enum ( TArg )
    #define COMPILER_INTRINS__IS_UNION( TArg )                      __is_union( TArg )
    #define COMPILER_INTRINS__IS_CLASS( TArg )                      __is_class( TArg )

//    #define COMPILER_INTRINS__IS_CONSTRUCTIBLE( TArg, TArgs )       __is_constructible( TArg, TArgs... )
    #define COMPILER_INTRINS__IS_TRIVIALLY_COPYABLE( TArg )         __is_trivially_copyable( TArg )
    #define COMPILER_INTRINS__IS_TRIVIALLY_DESTRUCTIBLE( TArg )     __is_trivially_destructible( TArg )

#elif __clang__
    #define COMPILER_INTRINS__IS_ENUM ( TArg )                  __is_enum ( TArg )
    #define COMPILER_INTRINS__IS_UNION( TArg )                  __is_union( TArg )
    #define COMPILER_INTRINS__IS_CLASS( TArg )                  __is_class( TArg )
    #define COMPILER_INTRINS__IS_TRIVIALLY_COPYABLE( TArg )     __is_trivially_copyable( TArg )

#elif ( defined( _MSC_VER ) && defined( _MSC_FULL_VER ) && ( _MSC_FULL_VER >=140050215 ) )
    COMPILER_INTRINS__IS_ENUM( T )   __is_union( T )

#elif __MINGW32__

#elif _ARM_
g
#endif

} // namespace traits
