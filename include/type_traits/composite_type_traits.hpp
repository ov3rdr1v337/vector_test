#pragma once

#include "primary_type_traits.hpp"

namespace traits
{
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

} // namespace traits
