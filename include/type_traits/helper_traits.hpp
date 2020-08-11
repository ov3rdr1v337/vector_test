#pragma once

namespace traits
{
    /// integral_constant
    template
        <
            class t_arg,
            t_arg val
        >
    struct integral_constant
    {
        using   value_t = t_arg;
        using   type_t  = integral_constant
                                <
                                    value_t,
                                    val
                                >;

        static constexpr t_arg value = val;

        constexpr operator value_t()   const noexcept
        {
            return value;
        }

        constexpr value_t operator()() const noexcept
        {
            return value;
        }
    };

    /// bool_constant
    template
        <
            bool bool_value
        >
    using   bool_constant = integral_constant
                                    <
                                        bool ,
                                        bool_value
                                    >;

    using   false_type = bool_constant<false>;
    using   true_type  = bool_constant<true>;

    /// is_same
    template
        <
            class t_arg_1,
            class t_arg_2
        >
    struct is_same :
                false_type
    {};

    template
        <
            class t_arg
        >
    struct is_same
                <
                    t_arg,
                    t_arg
                > : 
            true_type
    {};

    /// conditional
    template
        <
            bool  bool_value ,
            class t_true_arg ,
            class t_false_arg            
        >
    struct conditional
    {};

    template
        <
            class t_true_arg ,
            class t_false_arg
        >
    struct conditional
                <
                    true,
                    t_true_arg,
                    t_false_arg
                >
    {
        using   type = t_true_arg;
    };

    template
        <
            class t_true_arg,
            class t_false_arg
        >
    struct conditional
                <
                    false, 
                    t_true_arg, 
                    t_false_arg
                >
    {
        using   type = t_false_arg;
    };

    template
        <
            bool  bool_value ,
            class t_true_arg ,
            class t_false_arg
        >
    using conditional_t = typename conditional
                                        <
                                            bool_value,
                                            t_true_arg,
                                            t_false_arg
                                        >::type;

    template
        <
            bool  bool_value,
            class t_arg     = void
        >
    struct enable_if 
    {};
    
    template
        <
            class t_arg
        >
    struct enable_if<true, t_arg>
    {
        using   type = t_arg;
    };                                        

} // namespace traits