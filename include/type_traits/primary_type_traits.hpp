#pragma once

#include "helper_traits.hpp"
#include "type_modifications.hpp"
#include "compiler_sfinae_intrinsics.hpp"

#include <cstddef> 

namespace traits
{
    template
        <
            class t_arg
        >
    struct is_void_helper :
                false_type
    {};

    template<>
    struct is_void_helper<void> :
                true_type
    {};

    /// is_void
    template
        <
            class t_arg
        >
    struct is_void :
                is_void_helper
                        <
                            remove_cv_t<t_arg>
                        >
    {};

    /// is_null_pointer
    template
        <
            class t_arg
        >
    struct is_null_pointer :
                is_same
                        <
                            std::nullptr_t,
                            remove_cv_t<t_arg>
                        >
    {};

    template
        <
            class t_arg
        >
    struct is_integral_helper :
                false_type
    {};

    template<>
    struct is_integral_helper<bool> :
                true_type
    {};

    template<>
    struct is_integral_helper<char> :
                true_type
    {};

    template<>
    struct is_integral_helper<signed char> :
                true_type
    {};

    template<>
    struct is_integral_helper<unsigned char> :
                true_type
    {};

    template<>
    struct is_integral_helper<wchar_t> :
                true_type
    {};

    template<>
    struct is_integral_helper<char8_t> :
                true_type
    {};

    template<>
    struct is_integral_helper<char16_t> :
                true_type
    {};

    template<>
    struct is_integral_helper<char32_t> :
                true_type
    {};

    template<>
    struct is_integral_helper<short> :
                true_type
    {};

    template<>
    struct is_integral_helper<unsigned short> :
                true_type
    {};

    template<>
    struct is_integral_helper<int> :
                true_type
    {};

    template<>
    struct is_integral_helper<unsigned int> :
                true_type
    {};

    template<>
    struct is_integral_helper<long> :
                true_type
    {};

    template<>
    struct is_integral_helper<unsigned long> :
                true_type
    {};

    template<>
    struct is_integral_helper<long long> :
                true_type
    {};

    template<>
    struct is_integral_helper<unsigned long long> :
                true_type
    {};

    /// is_integral
    template
        <
            class t_arg
        >
    struct is_integral :
                is_integral_helper
                        <
                            remove_cv_t<t_arg>
                        >
    {};


    template
        <
            class t_arg
        >
    struct is_floating_point_helper :
                false_type
    {};

    template<>
    struct is_floating_point_helper<float> :
                true_type
    {};

    template<>
    struct is_floating_point_helper<double> :
                true_type
    {};

    template<>
    struct is_floating_point_helper<long double> :
                true_type
    {};

    /// is_floating_point
    template
        <
            class t_arg
        >
    struct is_floating_point :
                is_floating_point_helper
                        <
                            remove_cv_t<t_arg>
                        >
    {};

    /// is_array
    template
        <
            class t_arg
        >
    struct is_array :
                false_type
    {};

    template
        <
            class       t_arg,
            std::size_t size
        >
    struct is_array<t_arg[size]> :
                true_type
    {};

    template
        <
            class t_arg
        >
    struct is_array<t_arg[]> :
                true_type
    {};

    /// is_enum
    template
        <
            class t_arg
        >
    struct is_enum :
                bool_constant
                        <
                            COMPILER_INTRINSIC_IS_ENUM( t_arg )
                        >
    {};

    /// is_union
    template
        <
            class t_arg
        >
    struct is_union :
                bool_constant
                        <
                            COMPILER_INTRINSIC_IS_UNION( t_arg )
                        >
    {};

    /// is_class
    template
        <
            class t_arg
        >
    struct is_class :
                bool_constant
                        <
                            COMPILER_INTRINSIC_IS_CLASS( t_arg )
                        >
    {};

    /// is_function
    template
        <
            class t_arg
        >
    struct is_function :
                false_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args... )> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args... ) const> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args... ) volatile> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args... ) const volatile> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args... , ... ) > :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args... , ... ) const> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args... , ... ) volatile> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args... , ... ) const volatile> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args...) &> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args...) const &> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args...) volatile &> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args...) const volatile &> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args... , ... ) &> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args... , ... ) const &> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args... , ... ) volatile &> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args... , ... ) const volatile &> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args...) &&> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args...) const &&> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args...) volatile &&> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args...) const volatile &&> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args... , ... ) &&> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args... , ... ) const &&> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args... , ... ) volatile &&> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args... , ... ) const volatile &&> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args...) noexcept> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args...) const noexcept> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args...) volatile noexcept> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args...) const volatile noexcept> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args... , ... ) noexcept> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args... , ... ) const noexcept> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args... , ... ) volatile noexcept> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args... , ... ) const volatile noexcept> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args...) & noexcept> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args...) const & noexcept> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args...) volatile & noexcept> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args...) const volatile & noexcept> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args... , ... ) & noexcept> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args... , ... ) const & noexcept> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args... , ... ) volatile & noexcept> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args... , ... ) const volatile & noexcept> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args...) && noexcept> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args...) const && noexcept> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args...) volatile && noexcept> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args...) const volatile && noexcept> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args... , ... ) && noexcept> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args... , ... ) const && noexcept> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args... , ... ) volatile && noexcept> :
                true_type
    {};

    template
        <
            class    t_type ,
            class... t_args
        >
    struct is_function<t_type( t_args... , ... ) const volatile && noexcept> :
                true_type
    {};


    template
        <
            class t_arg
        >
    struct is_pointer_helper :
                false_type
    {};

    template
        <
            class t_arg
        >
    struct is_pointer_helper<t_arg*> :
                true_type
    {};

    /// is_pointer
    template
        <
            class t_arg
        >
    struct is_pointer :
                is_pointer_helper
                        <
                            remove_cv_t<t_arg>
                        >
    {};

    /// is_member_object_pointer
    template
        <
            class t_arg
        >
    struct is_member_object_pointer :
                false_type
    {};

    template
        <
            class t_ret ,
            class t_func
        >
    struct is_member_object_pointer<t_ret t_func::*> :
                bool_constant
                        <
                            !is_function
                                    <
                                        remove_cv_t<t_ret>
                                    >::value
                        >
    {};

    /// is_member_function_pointer
    template
        <
            class t_arg
        >
    struct is_member_function_pointer :
                false_type
    {};

    template
        <
            class t_ret ,
            class t_func
        >
    struct is_member_function_pointer<t_ret t_func::*> :
                is_function
                        <
                            remove_cv_t<t_ret>
                        >
    {};

    /// is_member_pointer
    template
        <
            class t_arg
        >
    struct is_member_pointer :
                bool_constant
                        <
                            is_member_function_pointer<t_arg>::value    ||
                            is_member_object_pointer  <t_arg>::value
                        >
    {};

    /// is_lvalue_reference
    template
        <
            class t_arg
        >
    struct is_lvalue_reference :
                false_type
    {};

    template
        <
            class t_arg
        >
    struct is_lvalue_reference<t_arg&> :
                true_type
    {};

    /// is_rvalue_reference
    template
        <
            class t_arg
        >
    struct is_rvalue_reference :
                false_type
    {};

    template
        <
            class t_arg
        >
    struct is_rvalue_reference<t_arg&&> :
                true_type
    {};

    /// is_reference
    template
        <
            class t_arg
        >
    struct is_reference :
                bool_constant
                        <
                            is_lvalue_reference<t_arg>::value   ||
                            is_rvalue_reference<t_arg>::value
                        >
    {};

} // namespace traits

