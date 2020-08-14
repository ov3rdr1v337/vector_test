#pragma once

#include "primary_type_traits.hpp"

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


    /// is_arithmetic
    template
        <
            class t_arg
        >
    struct is_arithmetic :
                    bool_constant
                            <
                                is_integral<t_arg>::value       ||
                                is_floating_point<t_arg>::value
                            >
    {};

    /// is_scalar
    template
        <
            class t_arg
        >
    struct is_scalar :
                bool_constant
                        <
                            is_enum<t_arg>::value               ||
                            is_pointer<t_arg>::value            ||
                            is_arithmetic<t_arg>::value         ||
                            is_null_pointer<t_arg>::value       ||
                            is_member_pointer<t_arg>::value
                        >
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
    struct is_copy_constructible 
                : is_constructible
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

    // template
    //     <
    //         typename  t_arg,
    //         bool    = is_void<t_arg>::value                 ||
    //                   //is_array_unknown_bounds<t_arg>::value || 
    //                   is_function <t_arg>::value,
    //         bool    = is_reference<t_arg>::value || 
    //                   is_scalar   <t_arg>::value
    //     >
    // struct is_destructible_impl
    // {};
    
    // template
    //     <
    //         typename t_arg
    //     >
    // struct is_destructible_impl
    //                     <
    //                         t_arg,
    //                         false,
    //                         false
    //                     > 
    //                 : is_destructible_impl
    //                         <
    //                             typename remove_all_extents<_Tp>::type
    //                         >::type
    // {};

    // template
    //     <
    //         typename t_arg
    //     >
    // struct is_destructible_impl
    //                     <
    //                         t_arg,
    //                         true ,
    //                         false
    //                     > 
    //                 : false_type 
    // {};

    // template
    //     <
    //         typename t_arg
    //     >
    // struct is_destructible_impl
    //                     <
    //                         t_arg,
    //                         false, 
    //                         true
    //                     >
    //                 : true_type 
    // {};

    // /// is_destructible
    // template
    //     <
    //         typename t_arg
    //     >
    // struct is_destructible
    //             : is_destructible_safe<t_arg>::type
    // {
    //     // static_assert
    //     //         ( 
    //     //             std::__is_complete_or_unbounded( __type_identity<_Tp>{} ), 
    //     //             "template argument must be a complete class or an unbounded array"
    //     //         );
    // };    

    // template
    //     <
    //         typename t_arg,
    //         bool   = is_referenceable<t_arg>::value
    //     >
    // struct is_nothrow_move_constructible_impl
    // {};

    // template
    //     <
    //         typename t_arg
    //     >
    // struct is_nothrow_move_constructible_impl<t_arg, false>
    //             : public false_type 
    // {};

    // template
    //     <
    //         typename t_arg
    //     >
    // struct is_nothrow_move_constructible_impl<t_arg, true>
    //             : public __is_nothrow_constructible_impl<t_arg, t_arg&&>
    // {};

    // /// is_nothrow_move_constructible
    // template<typename t_arg>
    // struct is_nothrow_move_constructible
    //         : public is_nothrow_move_constructible_impl<t_arg>::type
    // {
    //     // static_assert
    //     //         ( 
    //     //             std::__is_complete_or_unbounded( __type_identity<_Tp>{} ),
    //     //            "template argument must be a complete class or an unbounded array"
    //     //         );
    // };
} // namespace traits
