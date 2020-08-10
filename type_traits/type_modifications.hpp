#pragma once

namespace traits
{
    /// add_const
    template
        <
            class t_arg
        >
    struct add_const
    {
        using type = const t_arg;
    };

    template
        <
            class t_arg
        >
    using   add_const_t = typename add_const<t_arg>::type;

    /// add_volatile
    template
        <
            class t_arg
        >
    struct add_volatile
    {
        using type = volatile t_arg;
    };

    template
        <
            class t_arg
        >
    using   add_volatile_t = typename add_volatile<t_arg>::type;

    /// add_cv
    template
        <
            class t_arg
        >
    struct add_cv
    {
        using type = const volatile t_arg;
    };

    template
        <
            class t_arg
        >
    using   add_cv_t = typename add_cv<t_arg>::type;


    /// remove_const
    template
        <
            class t_arg
        >
    struct remove_const
    {
        using   type = t_arg;
    };

    template
        <
            class t_arg
        >
    struct remove_const<t_arg const>
    {
        using   type = t_arg;
    };

    template
        <
            class t_arg
        >
    using   remove_const_t = typename remove_const<t_arg>::type;

    /// remove_volatile
    template
        <
            class t_arg
        >
    struct remove_volatile
    {
        using   type = t_arg;
    };

    template
        <
            class t_arg
        >
    struct remove_volatile<t_arg volatile>
    {
        using   type = t_arg;
    };

    template
        <
            class t_arg
        >
    using   remove_volatile_t = typename remove_volatile<t_arg>::type;

    /// remove_cv
    template
        <
            class t_arg
        >
    struct remove_cv
    {
        using   type = t_arg;
    };

    template
        <
            class t_arg
        >
    struct remove_cv<const t_arg>
    {
        using   type = t_arg;
    };

    template
        <
            class t_arg
        >
    struct remove_cv<volatile t_arg>
    {
        using   type = t_arg;
    };

    template
        <
            class t_arg
        >
    struct remove_cv<const volatile t_arg>
    {
        using   type = t_arg;
    };

//    template
//        <
//            class t_arg
//        >
//    struct remove_cv
//    {
//        using   type = remove_const_t<remove_volatile_t<t_arg>>;
//    };

    template
        <
            class t_arg
        >
    using   remove_cv_t = typename remove_cv<t_arg>::type;

    /// remove_extent
    template
        <
            class t_arg
        >
    struct remove_extent
    {
        using   type = t_arg;
    };

    template
        <
            class t_arg
        >
    struct remove_extent<t_arg[]>
    {
        using   type = t_arg;
    };

    template
        <
            class t_arg ,
            std::size_t SIZE
        >
    struct remove_extent<t_arg[SIZE]>
    {
        using   type = t_arg;
    };

    template
        <
            class t_arg
        >
    using   remove_extent_t = typename remove_extent<t_arg>::type;

    /// remove_all_extents
    template
        <
            class t_arg
        >
    struct remove_all_extents
    {
        using   type = t_arg;
    };

    template
        <
            class t_arg
        >
    struct remove_all_extents<t_arg[]>
    {
        using   type = typename remove_all_extents<t_arg>::type ;
    };

    template
        <
            class t_arg ,
            std::size_t SIZE
        >
    struct remove_all_extents<t_arg[SIZE]>
    {
        using   type = typename remove_all_extents<t_arg>::type;
    };

    template
        <
            class t_arg
        >
    using   remove_all_extents_t = typename remove_all_extents<t_arg>::type;

} // namespace traits
