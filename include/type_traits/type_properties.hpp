#pragma once

#include "helper_traits.hpp"
#include "type_modifications.hpp"
#include "primary_type_traits.hpp"
#include "composite_type_traits.hpp"
#include "compiler_sfinae_intrinsics.hpp"

namespace traits
{
    /// is_const
    template
        <
            class t_arg
        >
    struct is_const :
                false_type
    {};

    template
        <
            class t_arg
        >
    struct is_const<const t_arg> :
                true_type
    {};

    /// is_volatile
    template
        <
            class t_arg
        >
    struct is_volatile :
                false_type
    {};

    template
        <
            class t_arg
        >
    struct is_volatile<volatile t_arg> :
                true_type
    {};

    /// is_cv_qualified
    template
        <
            class t_arg
        >
    struct is_cv_qualified :
                false_type
    {};

    template
        <
            class t_arg
        >
    struct is_cv_qualified<t_arg volatile> :
                true_type
    {};

    template
        <
            class t_arg
        >
    struct is_cv_qualified<t_arg const> :
                true_type
    {};

    template
        <
            class t_arg
        >
    struct is_cv_qualified<t_arg const volatile> :
                true_type
    {};

    /// is_constructible
    template
        <
            class    t_class ,
            class... t_args
        >
    struct is_constructible :
                    integral_constant
                            <
                                bool,
                                COMPILER_INTRINSIC_IS_CONSTRUCTIBLE( t_class, t_args... )
                            >
    {};

    /// is_copy_constructible
    template
        <
            class t_arg
        >
    struct is_copy_constructible :
                    is_constructible
                            <
                                      t_arg ,
                                const t_arg&
                            >
    {};

    template
        <
            class t_arg
        >
    inline constexpr bool is_copy_constructible_v = is_copy_constructible<t_arg>::value;

    template
        <
            class t_arg,
            bool =  is_void<t_arg>::value       ||
                    is_reference<t_arg>::value
        >
    struct is_trivially_copyable_helper
    {};


    template
        <
            class t_arg
        >
    struct is_trivially_copyable_helper<t_arg, true> :
                false_type
    {};

    template
        <
            class t_arg
        >
    struct is_trivially_copyable_helper<t_arg, false> :
                bool_constant
                        <
                            is_scalar<t_arg>::value     ||
                            COMPILER_INTRINSIC_IS_TRIVIALLY_COPYABLE( t_arg )
                        >
    {};

    /// is_trivially_copyable
    template
        <
            class t_arg
        >
    struct is_trivially_copyable :
                    is_trivially_copyable_helper
                            <
                                remove_cv_t
                                        <
                                            remove_all_extents_t<t_arg>
                                        >
                            >
    {};

    template
        <
            class t_arg
        >
    inline constexpr bool is_trivially_copyable_v = is_trivially_copyable<t_arg>::value;

    /// is_trivially_destructible
    // template
    //     <
    //         class t_arg
    //     >
    // struct is_trivially_destructible :
    //                 integral_constant
    //                         <
    //                             bool,
    //                             COMPILER_INTRINSIC_IS_TRIVIALLY_DESTRUCTIBLE( t_arg )
    //                         >
    // {};

    // template
    //     <
    //         class t_arg
    //     >
    // inline constexpr bool is_trivially_destructible_v = is_trivially_destructible<t_arg>::value;

} // namespace traits
