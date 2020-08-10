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
            bool t_arg
        >
    using   bool_constant = integral_constant
                                    <
                                        bool    ,
                                        t_arg
                                    >;

    using   false_type = bool_constant<false>;
    using   true_type  = bool_constant<true>;

    /// is_same
    template
        <
            class t_arg1    ,
            class t_arg2
        >
    struct is_same :
                false_type
    {};

    template
        <
            class t_arg
        >
    struct is_same<t_arg, t_arg> :
                true_type
    {};

    /// conditional
    template
        <
            bool  val   ,
            class T     ,
            class F
        >
    struct conditional
    {};

    template
        <
            class T ,
            class F
        >
    struct conditional<true, T, F>
    {
        using   type = T;
    };

    template
        <
            class T ,
            class F
        >
    struct conditional<false, T, F>
    {
        using   type = F;
    };

    template
        <
            bool  B ,
            class T ,
            class F
        >
    using conditional_t = typename conditional<B, T, F>::type;

} // namespace traits