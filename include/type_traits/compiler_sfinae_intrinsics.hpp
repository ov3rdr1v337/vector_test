#pragma once

namespace traits
{
#ifdef __GNUC__
    #define COMPILER_INTRINSIC_IS_ENUM( TArg )                       __is_enum ( TArg )
    #define COMPILER_INTRINSIC_IS_UNION( TArg )                      __is_union( TArg )
    #define COMPILER_INTRINSIC_IS_CLASS( TArg )                      __is_class( TArg )

    #define COMPILER_INTRINSIC_IS_CONSTRUCTIBLE( TArg, ... )         __is_constructible         ( TArg, __VA_ARGS__ )
    #define COMPILER_INTRINSIC_IS_TRIVIALLY_COPYABLE( TArg )         __is_trivially_copyable    ( TArg )
    //#define COMPILER_INTRINSIC_IS_TRIVIALLY_DESTRUCTIBLE( TArg )     __is_trivially_destructible( TArg )

#elif __clang__
    #define COMPILER_INTRINSIC_IS_ENUM ( TArg )                  __is_enum ( TArg )
    #define COMPILER_INTRINSIC_IS_UNION( TArg )                  __is_union( TArg )
    #define COMPILER_INTRINSIC_IS_CLASS( TArg )                  __is_class( TArg )
    #define COMPILER_INTRINSIC_IS_TRIVIALLY_COPYABLE( TArg )     __is_trivially_copyable( TArg )

#elif ( defined( _MSC_VER )      && 
        defined( _MSC_FULL_VER ) &&
       _MSC_FULL_VER >=140050215 )
    #define COMPILER_INTRINSIC_IS_ENUM ( TArg )                  __is_enum ( TArg )
    #define COMPILER_INTRINSIC_IS_UNION( TArg )                  __is_union( TArg )
    #define COMPILER_INTRINSIC_IS_CLASS( TArg )                  __is_class( TArg )
    #define COMPILER_INTRINSIC_IS_TRIVIALLY_COPYABLE( TArg )     __is_trivially_copyable( TArg )

#elif __MINGW32__

#elif _ARM_

#endif

} // namespace traits
